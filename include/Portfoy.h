#ifndef PORTFOY_H
#define PORTFOY_H

#include <stdio.h>
#include <stdlib.h>

struct PORTFOY
{
	char* id;
	char* sembol;
	double maliyet;
	double adet;
	
	void (*ToString)(struct PORTFOY*);
	void (*Yoket)(struct PORTFOY*);
	
};
typedef struct PORTFOY* Portfoy;

Portfoy PortfoyOlustur(char*,char*,double,double);
void PortfoyToString(const Portfoy);
void PortfoyYoket(Portfoy);

#endif