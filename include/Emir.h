#ifndef EMIR_H
#define EMIR_H

#include <stdio.h>
#include <stdlib.h>

struct EMIR
{
	char* id;
	char* sembol;
	char* islem;
	double adet;
	
	void (*ToString)(struct EMIR*);
	void (*Yoket)(struct EMIR*);
	
};
typedef struct EMIR* Emir;

Emir EmirOlustur(char*,char*,char*,double);
void EmirToString(const Emir);
void EmirYoket(Emir);

#endif