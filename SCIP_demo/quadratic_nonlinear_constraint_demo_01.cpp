/**
	����һ��ʾ������SCIP�����ɵ��ÿ�ʱ��ʹ�ñ��ʽ��SCIP�����ö��η�����Լ��;
	����Դ�������ӣ�������΢�е㸴�ӣ�������һ���򻯰������;
	�ο����ӣ�scipoptsuite-8.0.3\scip\examples\CallableLibrary\src\brachistochrone.c
	Ŀ�꺯��˵����
	obj max (x + y)
	s.t.
		x^2 + 2*x*y + y^2 <= 9
		0 =< x <= 10
		0 =< y <= 10
*/

#include <iostream>
#include <scip/scipdefplugins.h>


// _quadratic_nonlinear_constraint_demo_01
int main_quadratic_nonlinear_constraint_demo_01(void) {
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

	//--��ӱ��� (create and add variables to the problem)
	// ������Ŀ�꺯���ı���ʱ��ͬʱ�����˱�����ϵ����ͬʱ�����˱��������½緶Χ    
	SCIP_VAR* xVar = nullptr;
	SCIPcreateVarBasic(_scip, &xVar, "_x", 0.0, 10, 1.0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, xVar);

	SCIP_VAR* yVar = nullptr;
	SCIPcreateVarBasic(_scip, &yVar, "_y", 0.0, 10, 1.0, SCIP_VARTYPE_CONTINUOUS);
	SCIPaddVar(_scip, yVar);

	//--���Լ�� (add the constraint): x^2 + 2*x*y + y^2 <= 9
	SCIP_CONS* cons;
	SCIP_VAR* quadvars1[3];
	SCIP_VAR* quadvars2[3];
	SCIP_Real quadcoefs[3];

	quadvars1[0] = xVar;
	quadvars2[0] = xVar;
	quadcoefs[0] = 1.0;

	quadvars1[1] = xVar;
	quadvars2[1] = yVar;
	quadcoefs[1] = 2.0;

	quadvars1[2] = yVar;
	quadvars2[2] = yVar;
	quadcoefs[2] = 1.0;

	SCIPcreateConsQuadraticNonlinear(_scip, &cons, "cons_01", 0, NULL, NULL, 3,
		quadvars1, quadvars2, quadcoefs, -SCIPinfinity(_scip), 9.0, TRUE, TRUE,
		TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE);

	// add the constraint to the problem and forget it
	SCIPaddCons(_scip, cons);
	SCIPreleaseCons(_scip, &cons);

	// ��ӡģ�� (write model to disk)
	// ���޸������·��Ϊ����Եı���·�� (please modify here to your local file path)
	SCIPwriteOrigProblem(_scip, "D:/zhusc/work/op/quadratic_nonlinear_constraint_demo.lp", "cip", FALSE);

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