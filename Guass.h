#ifndef _GUASS_H
#define _GUASS_H

void GaussCal(int flag, double Latitude, double Longitude, double *X, double *Y);
void GuassInvCal(int flag, double X, double Y, double *Latitude, double *Longitude);

#endif