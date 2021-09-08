#ifndef BANKA_H
#define BANKA_H

#include "Hisse.h"
#include "Portfoy.h"
#include "Emir.h"
#include "cJSON.h"
#include <string.h>

struct BANKA
{
	int size_hisse;
	int size_portfoy;
	int size_emir;
	
	Hisse* hisseler; 
	Portfoy* portfoyler;
	Emir* emirler;
	
	char* (*oku)(char* yol);
	int (*findSize)(char* yol);
	void (*hisseOku)(struct BANKA*);
	int (*hisseBul)(char* sembol,struct BANKA*);
	void (*portfoyOku)(struct BANKA*);
	int (*portfoyBul)(char* sembol,struct BANKA*);
	void (*emirOku)(struct BANKA*);
	int (*emirBul)(char* sembol,struct BANKA*);
	void (*karZararYazdir)(struct BANKA*);
	void (*guncelPortfoyYazdir)(struct BANKA*);
	void (*calistir)(struct BANKA*);
	void (*Yoket)(struct BANKA*);
	
};
typedef struct BANKA* Banka;

Banka BankaOlustur();
char* Oku(char*);
int FindSize(char*);
void HisseOku(const Banka);
int HisseBul(char*, const Banka);
void PortfoyOku(const Banka);
int PortfoyBul(char*, const Banka);
void EmirOku(const Banka);
int EmirBul(char*, const Banka);
void KarZararYazdir(const Banka);
void GuncelPortfoyYazdir(const Banka);
void Calistir(const Banka);
void BankaYoket(Banka);

#endif
