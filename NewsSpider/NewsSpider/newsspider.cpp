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
	Py_Initialize(); // 初始化python虚拟机
	PyObject* pyMod  = PyImport_ImportModule("testpy"); //  加载testpy.py文件

	// <added by jianm>
	/*PyObject* pfunc = PyObject_GetAttrString(pyMod, "read_str");
	char *cstr;
	if (PyArg_Parse(pfunc, "s", &cstr))
	{
		ui.lineEdit->setText(cstr);
	}*/

	//PyObject* pyDict = PyModule_GetDict(pyMod); //  获取test模块中的字典
	//PyObject* pyCls = PyDict_GetItemString(pyDict, "tester"); // 从字典中查找tester类
	//PyObject* PyIns = PyInstance_New(pyCls, NULL, NULL); // 创建tester类
	//PyObject* pyRet = PyObject_CallMethod(PyIns, "add", "ii", 5, 6); // 调用tester.add方法，传入2个int型参数

	PyObject* pFunc = PyObject_GetAttrString( pyMod, "getHtml");
	char* cstr = "http://tieba.baidu.com/p/2738151262";
	PyObject* pargs = Py_BuildValue("(s)", cstr);
	PyObject* pstr = PyEval_CallObject(pFunc, pargs);
	char* result_str;
	if (PyArg_Parse(pFunc, "s", &result_str))
	{
		ui.lineEdit->setText(result_str);
	}

	//// 从返回值从取出int型返回值
	//int retValue = 0;
	//if (PyArg_Parse(pyRet, "i", &retValue))
	//{
	//	ui.lineEdit->setText(QString::number(retValue));
	//}
	
	Py_Finalize();
}
