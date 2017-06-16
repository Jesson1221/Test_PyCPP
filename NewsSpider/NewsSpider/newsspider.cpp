#include "newsspider.h"
#include <Python.h>

NewsSpider::NewsSpider(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	testPy();
}

NewsSpider::~NewsSpider()
{

}

void NewsSpider::testPy()
{
	Py_Initialize(); // ��ʼ��python�����
	PyObject* pyMod  = PyImport_ImportModule("testpy"); //  ����testpy.py�ļ�

	// <added by jianm>
	/*PyObject* pfunc = PyObject_GetAttrString(pyMod, "read_str");
	char *cstr;
	if (PyArg_Parse(pfunc, "s", &cstr))
	{
		ui.lineEdit->setText(cstr);
	}*/

	//PyObject* pyDict = PyModule_GetDict(pyMod); //  ��ȡtestģ���е��ֵ�
	//PyObject* pyCls = PyDict_GetItemString(pyDict, "tester"); // ���ֵ��в���tester��
	//PyObject* PyIns = PyInstance_New(pyCls, NULL, NULL); // ����tester��
	//PyObject* pyRet = PyObject_CallMethod(PyIns, "add", "ii", 5, 6); // ����tester.add����������2��int�Ͳ���

	PyObject* pFunc = PyObject_GetAttrString( pyMod, "getHtml");
	char* cstr = "http://tieba.baidu.com/p/2738151262";
	PyObject* pargs = Py_BuildValue("(s)", cstr);
	PyObject* pstr = PyEval_CallObject(pFunc, pargs);
	char* result_str;
	if (PyArg_Parse(pFunc, "s", &result_str))
	{
		ui.lineEdit->setText(result_str);
	}

	//// �ӷ���ֵ��ȡ��int�ͷ���ֵ
	//int retValue = 0;
	//if (PyArg_Parse(pyRet, "i", &retValue))
	//{
	//	ui.lineEdit->setText(QString::number(retValue));
	//}
	
	Py_Finalize();
}
