/**
	这是一个示例，把SCIP用作可调用库时，使用表达式在SCIP中设置二次非线性约束;
	本例子演示了，当二次项只有一个时，不用额外定义数组的简单写法;

	目标函数说明：
	obj max (x + y)
	s.t.
		x*y <= 9
		0 =< x <= 10
		0 =< y <= 10
*/

#include <iostream>
#include <scip/scipdefplugins.h>


// _quadratic_nonlinear_constraint_demo_02
int main_quadratic_nonlinear_constraint_demo_02(void) {
	// creates and initializes SCIP data structures
	SCIP* _scip;
	SCIPcreate(&_scip);

	// include default plugins
	SCIPincludeDefaultPlugins(_scip);

	// creates empty problem and initializes all solving data structures
	SCIPcreateProbBasic(_scip, "test");

	//sets objective sense of problem
	SCIPsetObjsense(_scip, SCIP_OBJSENSE_MAXIMIZE);

	// changes the value of an existing SCIP_Real parameter
	SCIPsetRealParam(_scip, "limits/gap", 0.00001);
	SCIPsetRealParam(_scip, "limits/time", 10);

	//--添加变量 (create and add variables to the problem)
	// 在设置目标函数的变量时，同时设置了变量的系数，同时设置了变量的上下界范围    
	SCIP_VAR* xVar = nullptr;
	SCIPcreateVarBasic(_scip, &xVar, "_x", 0.0, 10, 1.0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, xVar);

	SCIP_VAR* yVar = nullptr;
	SCIPcreateVarBasic(_scip, &yVar, "_y", 0.0, 10, 1.0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, yVar);

	//--添加约束 (add the constraint): x*y <= 9
	{
		// constraint's description: simple way
		std::cout << "constraint's description: simple way" << std::endl;
		SCIP_CONS* cons;
		SCIP_Real coef = 1.0;

		SCIPcreateConsQuadraticNonlinear(_scip, &cons, "cons_01", 0, NULL, NULL, 1,
			&xVar, &yVar, &coef, -SCIPinfinity(_scip), 9.0, TRUE, TRUE,
			TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE);

		// add the constraint to the problem and forget it
		SCIPaddCons(_scip, cons);
		SCIPreleaseCons(_scip, &cons);
	}

	{
		// constraint's description: define array's way
		// std::cout << "constraint's description: define array's way" << std::endl;
		//SCIP_CONS* cons;
		//SCIP_VAR* quadvars1[1];
		//SCIP_VAR* quadvars2[1];
		//SCIP_Real quadcoefs[1];
		// 
		//quadvars1[0] = xVar;
		//quadvars2[0] = yVar;
		//quadcoefs[0] = 1.0;
		// 
		//SCIPcreateConsQuadraticNonlinear(_scip, &cons, "cons_01", 0, NULL, NULL, 1,
		//    quadvars1, quadvars2, quadcoefs, -SCIPinfinity(_scip), 9.0, TRUE, TRUE,
		//    TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE);
	}

	// 打印模型 (write model to disk)
	// 请修改下面的路径为你电脑的本地路径 (please modify here to your local file path)
	SCIPwriteOrigProblem(_scip, "D:/zhusc/work/op/quadratic_nonlinear_constraint_demo_02.lp", "cip", FALSE);

	SCIPsolve(_scip);

	// get best solution
	SCIP_Real x_value = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), xVar);
	SCIP_Real y_value = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), yVar);
	std::cout << "x_value: " << x_value << std::endl;
	std::cout << "y_value: " << y_value << std::endl;

	//--release resource
	SCIPreleaseVar(_scip, &xVar);
	SCIPreleaseVar(_scip, &yVar);
	SCIPfree(&_scip);

	system("pause");
	return 0;
}