// GaussTranseorm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Guass.h"


int _tmain(int argc, _TCHAR* argv[])
{
	double B, L,X,Y,B1,L1;
	B = 34.742409053;
	L = 114.475167334;
	GaussCal(1, B, L, &X, &Y);
	GuassInvCal(1, X, Y, &B1, &L1);
	return 0;
}

