/**
	这是一个示例，把SCIP用作可调用库时，演示了约束条件中带有根号，对应的API调用的例子
	例子来源：
	目标函数说明：
	obj min t
	s.t. t * [(1 - y_{i+1})^0.5 + (1 - y_{i})^0.5] >= 5
*/

//tex:
// $$ min\ t $$
// $$ s.t.\ t \times[\sqrt{ 1 - y_{i + 1} } +\sqrt{ 1 - y_{i} }] \ge 5 $$
#include <iostream>

#include <scip/scipdefplugins.h>

// _cons_with_sqrt_and_sum
int main(void) {
	// creates and initializes SCIP data structures
	SCIP* _scip;
	SCIPcreate(&_scip);

	// include default plugins
	SCIPincludeDefaultPlugins(_scip);

	// creates empty problem and initializes all solving data structures
	SCIPcreateProbBasic(_scip, "test");

	//sets objective sense of problem
	SCIPsetObjsense(_scip, SCIP_OBJSENSE_MINIMIZE);

	// changes the value of an existing SCIP_Real parameter
	SCIPsetRealParam(_scip, "limits/gap", 0.00001);
	SCIPsetRealParam(_scip, "limits/time", 10);

	//--添加变量(（create and add variables to the problem, create obj function at the same time)
	// 在设置目标函数的变量时，同时设置了变量的系数，同时设置了变量的上下界范围 
	SCIP_VAR* t_var = nullptr;
	SCIPcreateVarBasic(_scip, &t_var, "_t", 0, SCIPinfinity(_scip), 1.0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, t_var);

	SCIP_VAR* y_ip1_var = nullptr;
	SCIPcreateVarBasic(_scip, &y_ip1_var, "_y_ip1", 0, 1, 0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, y_ip1_var);

	SCIP_VAR* y_i_var = nullptr;
	SCIPcreateVarBasic(_scip, &y_i_var, "_y_i", 0, 1, 0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, y_i_var);

	//--添加约束(add the constraint)
	SCIP_EXPR* yplusexpr;
	SCIP_EXPR* yexpr;
	SCIP_EXPR* texpr;

	/* create expressions for variables that are used in nonlinear constraint */
	SCIPcreateExprVar(_scip, &yplusexpr, y_ip1_var, NULL, NULL);
	SCIPcreateExprVar(_scip, &yexpr, y_i_var, NULL, NULL);
	SCIPcreateExprVar(_scip, &texpr, t_var, NULL, NULL);

	// intermediary expressions 
	// expr1: 1 - y[i+1]
	SCIP_EXPR* expr1;
	SCIP_Real minusone = -1.0;
	SCIPcreateExprSum(_scip, &expr1, 1, &yplusexpr, &minusone, 1.0, NULL, NULL);
	
	// expr3: sqrt(1 - y[i + 1])
	SCIP_EXPR* expr3;
	SCIPcreateExprPow(_scip, &expr3, expr1, 0.5, NULL, NULL);

	// expr2: 1 - y[i]
	SCIP_EXPR* expr2;
	SCIPcreateExprSum(_scip, &expr2, 1, &yexpr, &minusone, 1.0, NULL, NULL);

	// expr4: sqrt(1 - y[i])
	SCIP_EXPR* expr4;
	SCIPcreateExprPow(_scip, &expr4, expr2, 0.5, NULL, NULL);

	SCIP_EXPR* exprs[2];
	SCIP_Real coeffs[2];

	// expr5: t[i] * sqrt(1 - y[i+1])
	SCIP_EXPR* expr5;
	exprs[0] = texpr;
	exprs[1] = expr3;
	SCIPcreateExprProduct(_scip, &expr5, 2, exprs, 1, NULL, NULL);

	// expr6: t[i] * sqrt(1 - y[i])
	SCIP_EXPR* expr6;
	exprs[0] = texpr;
	exprs[1] = expr4;
	SCIPcreateExprProduct(_scip, &expr6, 2, exprs, 1, NULL, NULL);

	// expr7: t[i] * sqrt(1 - y[i+1]) + t[i] * sqrt(1 - y[i])
	SCIP_EXPR* expr7;
	exprs[0] = expr5; coeffs[0] = 1.0;
	exprs[1] = expr6; coeffs[1] = 1.0;
	SCIPcreateExprSum(_scip, &expr7, 2, exprs, coeffs, 0.0, NULL, NULL);

	/* create the constraint expr7 >= 0, add to the problem, and release it */
	SCIP_CONS* cons;
	SCIPcreateConsBasicNonlinear(_scip, &cons, "cons_name", expr7, 5, SCIPinfinity(_scip));
	SCIPaddCons(_scip, cons);
	SCIPreleaseCons(_scip, &cons);

	/* release exprs */
	SCIPreleaseExpr(_scip, &expr7);
	SCIPreleaseExpr(_scip, &expr6);
	SCIPreleaseExpr(_scip, &expr5);
	SCIPreleaseExpr(_scip, &expr4);
	SCIPreleaseExpr(_scip, &expr3);
	SCIPreleaseExpr(_scip, &expr2);
	SCIPreleaseExpr(_scip, &expr1);
	SCIPreleaseExpr(_scip, &texpr);
	SCIPreleaseExpr(_scip, &yexpr);
	SCIPreleaseExpr(_scip, &yplusexpr);

	// 打印模型  (write model to disk)
	SCIPwriteOrigProblem(_scip, "D:/test0.lp", "cip", FALSE);

	SCIPsolve(_scip);

	//--取最优解(get best solution)
	double t_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), t_var);
	double y_ip1_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), y_ip1_var);
	double y_i_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), y_i_var);

	std::cout << "find best solution, t_val: " << t_val << std::endl;
	std::cout << "find best solution, y_ip1_val: " << y_ip1_val << std::endl;
	std::cout << "find best solution, y_i_val: " << y_i_val << std::endl;

	//--release resource
	SCIPreleaseVar(_scip, &t_var);
	SCIPreleaseVar(_scip, &y_ip1_var);
	SCIPreleaseVar(_scip, &y_i_var);
	SCIPfree(&_scip);

	system("pause");
	return 0;
}