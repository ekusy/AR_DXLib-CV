#pragma once
#include <Python.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE -1
class py
{

	PyObject *pName, *pModule, *pFunc1, *pFunc2, *pFunc3, *pFunc4;


public:
	py();
	~py();
	void pyFinalize(void);
	bool pySerialOpen();
	bool pySerialOpen(const char* _PORT,const int _BAUDRATE);
	char** pySerialRead(void);
	void pySerialClose(void);
	bool pySerialIsOpen(void);
};

