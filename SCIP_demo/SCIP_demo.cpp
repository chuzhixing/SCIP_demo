#include <iostream>
#include <scip/scipdefplugins.h>


//目标函数: 2x+3y
//con 2x+3y >= 7
int main(void) {
	// creates and initializes SCIP data structures
	SCIP * _scip;
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

	//--添加变量
	SCIP_VAR *xVar = nullptr;
	SCIPcreateVarBasic(_scip, &xVar, "_x", 0, SCIPinfinity(_scip), 2.0, SCIP_VARTYPE_INTEGER);
	SCIPaddVar(_scip, xVar);

	SCIP_VAR *yVar = nullptr;
	SCIPcreateVarBasic(_scip, &yVar, "_y", 0, SCIPinfinity(_scip), 3.0, SCIP_VARTYPE_INTEGER);
	SCIPaddVar(_scip, yVar);

	//--添加约束
	SCIP_CONS* zCons;
	SCIPcreateConsBasicLinear(_scip, &zCons, "z_cons", 0, NULL, NULL, 7, SCIPinfinity(_scip));
	SCIPaddCoefLinear(_scip, zCons, xVar, 2);
	SCIPaddCoefLinear(_scip, zCons, yVar, 3);
	SCIPaddCons(_scip, zCons);

	SCIPsolve(_scip);

	SCIPwriteOrigProblem(_scip, "C:\\Users\\Administrator\\Desktop\\SCIP\\scip_demo.lp", "cip", FALSE);

	//--取最优解
	SCIP_Real x_value = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), xVar);
	SCIP_Real y_value = SCIPgetSolVal(_scip, SCIPgetBestSol(_scip), yVar);

	//--释放资源
	SCIPreleaseVar(_scip, &xVar);
	SCIPreleaseVar(_scip, &yVar);

	SCIPreleaseCons(_scip, &zCons);

	SCIPfree(&_scip);

	std::cout << "x_value: " << x_value << std::endl;
	std::cout << "y_value: " << y_value << std::endl;

	system("pause");
	return 0;
}