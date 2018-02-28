/**********************************************************
function:定义参考椭球基准
***********************************************************/
#ifndef _DEFINETION_H
#define _DEFINETION_H
#include<math.h>

#define PI 3.1415926535897932
#define rad PI/180
#define deg 180/PI

//WGS84椭球基准参数
#define WGS84_a  6378137.0                            
#define WGS84_f  1/298.257223565;                    


//BJ54椭球基准
#define BJ54_a   6378245
#define BJ54_f   1/298.3


//XIAN80椭球基准
#define XIAN80_a   6378140.0
#define XIAN80_f   1/298.257

#endif
