/**
	这是一个示例，把SCIP用作可调用库时，演示了约束条件中带有根号，对应的API调用的例子
	例子来源：
	目标函数说明：
*/

//tex:
// $$\ obj\quad min\ t_i $$
// $$ s.t.\ t_i * [\sqrt{(1 - y_{i+1})} + \sqrt{(1 - y_{i})}] - \sqrt{(x_{i+1} - x_{i})^2 + (y_{i+1} - y_{i})^2} >= 0 $$
// $$\qquad  0 = < t_i $$ 
// $$\qquad  0 = < y_{ i + 1 } <= 1 $$
// $$\qquad  0 = < y_{ i } <= 1 $$ 
// $$\qquad  0 = < x_{ i + 1 } <= 1 $$ 
// $$\qquad  0 = < x_{ i } <= 1 $$ 


// 等价转换
//tex:
// $$\ obj\quad min\ t_i $$
// $$ s.t.\ t_i * [\sqrt{(1 - y_{i+1})} + \sqrt{(1 - y_{i})}] - v_i >= 0 $$
// $$\qquad v_i^2 = (x_{i+1} - x_{i})^2 + (y_{i+1} - y_{i})^2 $$
// $$\qquad  0 = < t_i $$ 
// $$\qquad  0 = < y_{ i + 1 } <= 1 $$
// $$\qquad  0 = < y_{ i } <= 1 $$ 
// $$\qquad  0 = < x_{ i + 1 } <= 1 $$ 
// $$\qquad  0 = < x_{ i } <= 1 $$ 
// $$\qquad  0 = < v_{ i } <= 1 $$ 

#include <iostream>
#include <scip/scipdefplugins.h>

// _cons_with_sqrt_and_sum_and_quadratic_nonlinear_demo
int main_cons_with_sqrt_and_sum_and_quadratic_nonlinear_demo(void) {
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
	SCIP_VAR* t_i_var = nullptr;
	SCIPcreateVarBasic(_scip, &t_i_var, "_t_i", 0, SCIPinfinity(_scip), 1.0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, t_i_var);

	SCIP_VAR* y_ip1_var = nullptr;
	SCIPcreateVarBasic(_scip, &y_ip1_var, "_y_ip1", 0, 1.0, 0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, y_ip1_var);

	SCIP_VAR* y_i_var = nullptr;
	SCIPcreateVarBasic(_scip, &y_i_var, "_y_i", 0, 1.0, 0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, y_i_var);

	SCIP_VAR* v_i_var = nullptr;
	SCIPcreateVarBasic(_scip, &v_i_var, "_v_i", 0, SCIPinfinity(_scip), 0.0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, v_i_var);

	SCIP_VAR* x_ip1_var = nullptr;
	SCIPcreateVarBasic(_scip, &x_ip1_var, "_x_ip1", 0, 1, 0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, x_ip1_var);

	SCIP_VAR* x_i_var = nullptr;
	SCIPcreateVarBasic(_scip, &x_i_var, "_x_i", 0, 1, 0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, x_i_var);

	//--添加约束(add the constraint)
	SCIP_EXPR* yplusexpr;
	SCIP_EXPR* yexpr;
	SCIP_EXPR* texpr;
	SCIP_EXPR* vexpr;

	/* create expressions for variables that are used in nonlinear constraint */
	SCIPcreateExprVar(_scip, &yplusexpr, y_ip1_var, NULL, NULL);
	SCIPcreateExprVar(_scip, &yexpr, y_i_var, NULL, NULL);
	SCIPcreateExprVar(_scip, &texpr, t_i_var, NULL, NULL);
	SCIPcreateExprVar(_scip, &vexpr, v_i_var, NULL, NULL);

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

	SCIP_EXPR* exprs[3];
	SCIP_Real coeffs[3];

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

	// expr7: t[i] * sqrt(1 - y[i+1]) + t[i] * sqrt(1 - y[i]) - v[i]
	SCIP_EXPR* expr7;
	exprs[0] = expr5; coeffs[0] = 1.0;
	exprs[1] = expr6; coeffs[1] = 1.0;
	exprs[2] = vexpr; coeffs[2] = 1.0;
	SCIPcreateExprSum(_scip, &expr7, 3, exprs, coeffs, 0.0, NULL, NULL);
	// SCIPcreateExprSum、SCIPcreateExprProduct、SCIPcreateExprPow、SCIPcreateExprAbs、SCIPcreateExprSin、SCIPcreateExprCos、SCIPcreateExprLog、SCIPcreateExprSignpower、SCIPcreateExprQuadratic、SCIPcreateExprMonomial

	
	
	


	/* create the constraint expr7 >= 0, add to the problem, and release it */
	SCIP_CONS* cons;
	SCIPcreateConsBasicNonlinear(_scip, &cons, "cons_01", expr7, 0, SCIPinfinity(_scip));
	SCIPaddCons(_scip, cons);
	SCIPreleaseCons(_scip, &cons);

	/**
	[(x_{i+1} - x_{i})^2 + (y_{i+1} - y_{i})^2] - v_i^2 = 0
	<==>
	(y[i+1]^2 - 2 * y[i+1] * y[i] + y[i]^2) + (x[i+1]^2 - 2 * x[i+1] * x[i] + x[i]^2) +  - v[i]^2 = 0
	*/
	SCIP_CONS* cons_02;
	SCIP_VAR* quadvars1[7];
	SCIP_VAR* quadvars2[7];
	SCIP_Real quadcoefs[7];

	quadvars1[0] = y_ip1_var; quadvars2[0] = y_ip1_var; quadcoefs[0] = 1.0;
	quadvars1[1] = y_ip1_var; quadvars2[1] = y_i_var; quadcoefs[1] = -2.0;
	quadvars1[2] = y_i_var; quadvars2[2] = y_i_var; quadcoefs[2] = 1.0;
	quadvars1[3] = x_ip1_var; quadvars2[3] = x_ip1_var; quadcoefs[3] = 1.0;
	quadvars1[4] = x_ip1_var; quadvars2[4] = x_i_var; quadcoefs[4] = -2.0;
	quadvars1[5] = x_i_var; quadvars2[5] = x_i_var; quadcoefs[5] = 1.0;
	quadvars1[6] = v_i_var; quadvars2[6] = v_i_var; quadcoefs[6] = 1.0;

	SCIPcreateConsQuadraticNonlinear(_scip, &cons_02, "cons_02", 0, NULL, NULL, 7,
		quadvars1, quadvars2, quadcoefs, 0.0, 0.0, TRUE, TRUE,
		TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE);

	// add the constraint to the problem and forget it
	SCIPaddCons(_scip, cons_02);
	SCIPreleaseCons(_scip, &cons_02);

	// 打印模型  (write model to disk)
	SCIPwriteOrigProblem(_scip, "D:/test0.lp", "cip", FALSE);
	SCIPsolve(_scip);

	//--取最优解(get best solution)
	double t_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), t_i_var);
	double y_ip1_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), y_ip1_var);
	double y_i_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), y_i_var);
	double x_ip1_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), x_ip1_var);
	double x_i_val = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), x_i_var);

	std::cout << "find best solution, t_val: " << t_val << std::endl;
	std::cout << "find best solution, y_ip1_val: " << y_ip1_val << std::endl;
	std::cout << "find best solution, y_i_val: " << y_i_val << std::endl;
	std::cout << "find best solution, x_ip1_val: " << x_ip1_val << std::endl;
	std::cout << "find best solution, x_i_val: " << x_i_val << std::endl;

	/* release exprs */
	SCIPreleaseExpr(_scip, &expr7);
	SCIPreleaseExpr(_scip, &expr6);
	SCIPreleaseExpr(_scip, &expr5);
	SCIPreleaseExpr(_scip, &expr4);
	SCIPreleaseExpr(_scip, &expr3);
	SCIPreleaseExpr(_scip, &expr2);
	SCIPreleaseExpr(_scip, &expr1);

	SCIPreleaseExpr(_scip, &texpr);
	SCIPreleaseExpr(_scip, &yplusexpr);
	SCIPreleaseExpr(_scip, &yexpr);
	SCIPreleaseExpr(_scip, &vexpr);

	//--release resource
	SCIPreleaseVar(_scip, &t_i_var);
	SCIPreleaseVar(_scip, &y_ip1_var);
	SCIPreleaseVar(_scip, &y_i_var);
	SCIPreleaseVar(_scip, &x_ip1_var);
	SCIPreleaseVar(_scip, &x_i_var);
	SCIPreleaseVar(_scip, &v_i_var);

	SCIPfree(&_scip);

	system("pause");
	return 0;
}