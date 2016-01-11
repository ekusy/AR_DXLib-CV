#include "py.h"


py::py()
{

	Py_Initialize();
	pName = PyUnicode_FromString("ser");
	pModule = PyImport_Import(pName);
	pFunc1 = PyObject_GetAttrString(pModule, "serialOpen");
	pFunc2 = PyObject_GetAttrString(pModule, "serialReadLine");
	pFunc3 = PyObject_GetAttrString(pModule, "serialClose");
	pFunc4 = PyObject_GetAttrString(pModule, "serialIsOpen");
	//pFunc4 = PyObject_GetAttrString(pModule, "testFunc");

}


py::~py()
{
	pyFinalize();
}

void py::pyFinalize(){
	Py_Finalize();
}

bool py::pySerialOpen(){
	return pySerialOpen("COM3",9600);
}

bool py::pySerialOpen(const char* _PORT,const int _BOARDRATE){
	PyObject *result = PyObject_CallObject(pFunc1, NULL);
	return _PyInt_AsInt(result);
}

char** py::pySerialRead(){
	PyObject *rec;
	rec = PyObject_CallObject(pFunc2, NULL);
	char* str = PyString_AsString(rec);
	char *rot[2] = { "", "" };
	rot[0] = strtok(str, ",");
	rot[1] = strtok(NULL, ",");
	return rot;

}

void py::pySerialClose(){
	PyObject_CallObject(pFunc3, NULL);
}

bool py::pySerialIsOpen(){
	PyObject *rec;
	rec = PyObject_CallObject(pFunc4, NULL);
	return _PyInt_AsInt(rec);
}






