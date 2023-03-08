/**
	����һ��ʾ������SCIP�����ɵ��ÿ�ʱ��һ�����ż��ĳ���
	������Դ��
	Ŀ�꺯��˵����
	obj min (2*x + 3*y)
	s.t. 2*x+3*y >= 7
*/
#include <iostream>
#include <scip/scipdefplugins.h>

// _hello_world
int main_hello_world(void) {
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

	//--��ӱ���(��create and add variables to the problem, create obj function at the same time)
	// ������Ŀ�꺯���ı���ʱ��ͬʱ�����˱�����ϵ����ͬʱ�����˱��������½緶Χ 
	SCIP_VAR* xVar = nullptr;
	SCIPcreateVarBasic(_scip, &xVar, "_x", 0, SCIPinfinity(_scip), 2.0, SCIP_VARTYPE_INTEGER);
	SCIPaddVar(_scip, xVar);

	SCIP_VAR* yVar = nullptr;
	SCIPcreateVarBasic(_scip, &yVar, "_y", 0, SCIPinfinity(_scip), 3.0, SCIP_VARTYPE_INTEGER);
	SCIPaddVar(_scip, yVar);

	// ����ʹ������ĺ����޸ı�����Ŀ�꺯���е�ϵ��
	// SCIPchgVarObj(_scip, xVar, 1);

	//--���Լ��(add the constraint)
	SCIP_CONS* zCons;
	SCIPcreateConsBasicLinear(_scip, &zCons, "z_cons", 0, NULL, NULL, 7, SCIPinfinity(_scip));
	SCIPaddCoefLinear(_scip, zCons, xVar, 2);
	SCIPaddCoefLinear(_scip, zCons, yVar, 3);
	SCIPaddCons(_scip, zCons);
	SCIPreleaseCons(_scip, &zCons);

	// ��ӡģ��  (write model to disk)
	SCIPwriteOrigProblem(_scip, "D:/zhusc/work/op/test0.lp", "cip", FALSE);

	SCIPsolve(_scip);

	//--ȡ���Ž�(get best solution)
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