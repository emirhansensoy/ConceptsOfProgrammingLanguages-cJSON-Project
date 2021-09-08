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

#include <windows.h>
#include "Banka.h"

int main()
{
	SetConsoleOutputCP(65001);
	
	Banka banka = BankaOlustur();
	banka->calistir(banka);
	banka->Yoket(banka);
	return 0;
}

