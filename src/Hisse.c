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

#include "Hisse.h"

Hisse HisseOlustur(char* id,char* sembol,char* ad,double fiyat)
{
	Hisse this;
	this = (Hisse)malloc(sizeof(struct HISSE));
	this->id = id;
	this->sembol = sembol;
	this->ad = ad;
	this->fiyat = fiyat;
	this->ToString = &HisseToString;
	this->Yoket = &HisseYoket;
	return this;
}

void HisseToString(const Hisse this)
{
	printf("Hisse ( Id = '%s' Sembol = '%s' Ad = '%s' Fiyat = '%0.2f' )\n", this->id, this->sembol, this->ad, this->fiyat);
}

void HisseYoket(Hisse this)
{
	if(this == NULL) return;
	free(this);
}