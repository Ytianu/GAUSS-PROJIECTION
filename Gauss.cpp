#include"stdafx.h"
#include<stdio.h>
#include<math.h>
#include"definetion.h"


void GaussCal( int flag,double Latitude, double Longitude, double *X, double *Y)
{
	//以赤道为X轴，零度子午线为Y轴建系
	double a, f, ee, et; //引入椭球参数
	double Latitude0, Longitude0, Latitude1, Longitude1,X0,Y0;
	double N, T, C, A, M;

	int BeltNumber = 0;                       //经度带带号
	int Beltwidth = 6;                        //定义经度带带宽
	BeltNumber = (int)(Longitude / Beltwidth);

	Longitude0 = (BeltNumber*Beltwidth + Beltwidth / 2)*rad;                       //以0度子午线为Y
	Latitude0 = 0*rad;                                                             //以0度纬线（赤道）为X轴
	Latitude1 = Latitude*rad;
	Longitude1 = Longitude*rad;

	X0 = 500000 + (BeltNumber + 1) * 1000000;
	Y0 = 0;

	switch (flag)
	{
	case 1:
	{
			  a = WGS84_a;
			  f = WGS84_f;
	}
		break;
	case 2:
	{
			  a = BJ54_a;
			  f = BJ54_f;
	}
		break;
	case 3:
		{
			a = XIAN80_a;
			f = XIAN80_f;
		}
		break;
	default:
		break;
	}
	ee = 2 * f - f*f;
	et = ee * (1.0 - ee);

	N = a / sqrt(1.0-ee*sin(Latitude1)*sin(Latitude1));
	T = tan(Latitude1)*tan(Latitude1);
	C = et*cos(Latitude1)*cos(Latitude1);
	A = (Longitude1 - Longitude0)*cos(Latitude1);
	M = a*((1 - ee / 4 - 3 * ee*ee / 64 - 5 * ee*ee*ee / 256)*Latitude1 - (3 * ee / 8 + 3 * ee*ee / 32 + 45 * ee*ee*ee / 1024)*sin(2 * Latitude1)
		+ (15 * ee*ee / 256 + 45 * ee*ee*ee / 1024)*sin(4 * Latitude1) - (35 * ee*ee*ee / 3072)*sin(6 * Latitude1));
	*X = X0 + N*(A + (1 - T + C)*A*A*A / 6 + (5 - 18 * T + T*T + 72 * C - 58 * et)*pow(A, 5) / 120);
	*Y = Y0+M + N*tan(Latitude1)*(A*A / 2 + (5 - T + 9 * C + 4 * C*C)*A*A*A*A / 24 
		+ (61 - 58 * T + T*T + 600 * C - 330 * et)*pow(A, 6) / 720);	
}
//270* C - 330 * T*C  14 * C - 58 * T*C
//600* C - 330 * ee   72 * C - 58 * ee

void GuassInvCal(int flag, double X, double Y, double *Latitude, double *Longitude)
{
	double a, f, ee, et,e1;
	double Latitude0, Longitude0,Latitude1,Longitude1,X0,Y0,dx,dy;
	double N, T, C, D, M,R,FAI,u;
	int BeltNumber;
	int Beltwidth = 6;
	switch (flag)
	{
	case 1:
	{
			  a = WGS84_a;
			  f = WGS84_f;

	}
		break;
	case 2:
	{
			  a = BJ54_a;
			  f = BJ54_f;
	}
		break;
	case 3:
	{
			  a = XIAN80_a;
			  f = XIAN80_f;
	}
		break;
	default:
		break;
	}
	ee = 2 * f - f*f;
	et = ee/(1.0 - ee);
	e1 = (1.0 - sqrt(1 - ee)) / (1.0 + sqrt(1 - ee));
	BeltNumber = (int)(X / 1000000);                                         //求取经度带带号
	Longitude0 = (Beltwidth*(BeltNumber-1)+Beltwidth/2)*rad;                //求取中央经度
	Latitude0 = 0 * rad;
	X0 = 1000000 * BeltNumber + 500000;                              //中央经线横坐标
	Y0 = 0;    
	dx = X - X0;
	dy = Y - Y0;
	M = dy;
	u = M / (a*(1 - ee / 4 - 3 * ee*ee / 64 - 5 * ee*ee*ee / 256));
	FAI = u + (3 * e1 / 2 - 27 * e1*e1*e1 / 32)*sin(2 * u) + (21 * e1*e1 / 16 - 55 * e1*e1*e1*e1 / 32)*sin(4 * u)
		+ (151 * e1*e1*e1 / 96)*sin(6 * u) + (1097 * e1*e1*e1*e1 / 512)*sin(8 * u);
	C = et*cos(FAI)*cos(FAI);
	T = tan(FAI)*tan(FAI);
	N= a / sqrt(1.0 - ee*sin(FAI)*sin(FAI));
	R = a*(1 - ee) / sqrt((1 - ee*sin(FAI)*sin(FAI))*(1 - ee*sin(FAI)*sin(FAI))*(1 - ee*sin(FAI)*sin(FAI)));
	D = dx / N;
	//计算经度(Longitude) 纬度(Latitude)
	Longitude1 = Longitude0 + (D - (1 + 2 * T + C)*D*D*D / 6 + (5 - 2 * C + 28 * T - 3 * C*C + 8 * et + 24 * T*T)*D*D*D*D*D / 120) / cos(FAI);
	Latitude1 = FAI - (N*tan(FAI) / R)*(D*D / 2 - (5 + 3 * T + 10 * C - 4 * C*C - 9 * et)*D*D*D*D / 24
		+ (61 + 90 * T + 298 * C + 45 * T*T - 256 * et - 3 * C*C)*D*D*D*D*D*D / 720);
	//转换为度
	*Latitude = Latitude1*deg;
	*Longitude = Longitude1*deg;
}