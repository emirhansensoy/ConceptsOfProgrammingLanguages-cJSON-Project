/**
*
* @author Emirhan ŞENSOY - emirhan.sensoy@ogr.sakarya.edu.tr
* @since 4 ‎Mayıs ‎2021 ‎Salı, ‏‎15:15:40
* <p>
* Program açıldığında,
* -hisseler.json isimli dosyadan bütün hisseler ve güncel değerleri okunur
* -portfoy.json isimli dosyadan kişinin satın almışolduğu hisseler ve kaç adet oldukları okunur
* -emirler.json isimli dosyadan kişinin verdiği emirler okunur.
* -okuma bittikten sonra emirlerden alınan işlemler yapılır.
* -işlemler sonrası kişinin toplam kar/zararı ve güncel portföyü ekrana yazdırılır.
* </p>
*/

#include "Emir.h"

Emir EmirOlustur(char* id,char* sembol,char* islem,double adet)
{
	Emir this;
	this = (Emir)malloc(sizeof(struct EMIR));
	this->id = id;
	this->sembol = sembol;
	this->islem = islem;
	this->adet = adet;
	this->ToString = &EmirToString;
	this->Yoket = &EmirYoket;
	return this;
}

void EmirToString(const Emir this)
{
	printf("Emir ( Id = '%s' Sembol = '%s' Islem = '%s' Adet = '%0.2f' )\n", this->id, this->sembol, this->islem, this->adet);
}

void EmirYoket(Emir this)
{
	if(this == NULL) return;
	free(this);
}