/**********************************************************
function:宏定义、结构体定义
***********************************************************/
#ifndef _DEFINETION_H
#define _DEFINETION_H
#include<math.h>

#define PI 3.1415926535897932
#define rad PI/180
#define deg 180/PI

//定义WGS84参考椭球基准
#define WGS84_a  6378137.0                              //长半轴
#define WGS84_f  1/298.257223565;                     //扁率


//BJ54参考椭球基准
#define BJ54_a   6378245
#define BJ54_f   1/298.3


//XIAN80参考椭球基准
#define XIAN80_a   6378140.0
#define XIAN80_f   1/298.257

#endif