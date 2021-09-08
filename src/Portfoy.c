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

#include "Portfoy.h"

Portfoy PortfoyOlustur(char* id,char* sembol,double maliyet,double adet)
{
	Portfoy this;
	this = (Portfoy)malloc(sizeof(struct PORTFOY));
	this->id = id;
	this->sembol = sembol;
	this->maliyet = maliyet;
	this->adet = adet;
	this->ToString = &PortfoyToString;
	this->Yoket = &PortfoyYoket;
	return this;
}

void PortfoyToString(const Portfoy this)
{
	printf("Portfoy ( Id = '%s' Sembol = '%s' Maliyet = '%0.2f' Adet = '%0.2f' )\n", this->id, this->sembol, this->maliyet, this->adet);
}

void PortfoyYoket(Portfoy this)
{
	if(this == NULL) return;
	free(this);
}