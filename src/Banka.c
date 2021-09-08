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

#include "Banka.h"

Banka BankaOlustur()
{
	Banka this;
	this = (Banka)malloc(sizeof(struct BANKA));
	this->oku = &Oku;
	this->findSize = &FindSize;
	this->hisseOku = &HisseOku;
	this->hisseBul = &HisseBul;
	this->portfoyOku = &PortfoyOku;
	this->portfoyBul = &PortfoyBul;
	this->emirOku = &EmirOku;
	this->emirBul = &EmirBul;
	this->karZararYazdir = &KarZararYazdir;
	this->guncelPortfoyYazdir = &GuncelPortfoyYazdir;
	this->Yoket = &BankaYoket;
	this->calistir = &Calistir;
	
	this->size_hisse = this->findSize("./doc/hisseler.json");
	this->size_portfoy = this->findSize("./doc/portfoy.json");
	this->size_emir = this->findSize("./doc/emirler.json");
	
	this->hisseler = calloc(this->size_hisse , sizeof(Hisse)); 
	this->portfoyler = calloc(this->size_portfoy , sizeof(Portfoy));
	this->emirler = calloc(this->size_emir , sizeof(Emir));
	int i;
	for(i = 0; i < this->size_hisse; i++)
	{
		this->hisseler[i] = HisseOlustur(NULL,NULL,NULL,0);
	}
	for(i = 0; i < this->size_portfoy; i++)
	{
		this->portfoyler[i] = PortfoyOlustur(NULL,NULL,0,0);
	}
	for(i = 0; i < this->size_emir; i++)
	{
		this->emirler[i] = EmirOlustur(NULL,NULL,0,0);
	}
	return this;
}

void Calistir(Banka this)
{
	this->hisseOku(this);
	this->portfoyOku(this);
	this->emirOku(this);
	
	this->karZararYazdir(this);
	this->guncelPortfoyYazdir(this);
}

char* Oku(char* yol)
{
	char* icerik=NULL;
	int boyut=0;
	FILE *fp;
	fp = fopen(yol,"r");
	if(!fp) return NULL;
	fseek(fp,0,SEEK_END);
	boyut = ftell(fp);
	rewind(fp);
	icerik = (char*)malloc(sizeof(char)*(boyut+1));
	size_t toplamUzunluk = fread(icerik, 1, boyut, fp);
	icerik[toplamUzunluk]='\0';
	fclose(fp);
	return icerik;	
}

int FindSize(char* yol)
{
	int size = 0;
	FILE *fp = fopen(yol, "r");
	char buffer[30];
	int sayac = 0;
	while((fgets(buffer, sizeof(buffer), fp)) != NULL)
	{
		if(strstr(buffer, "]}") != NULL)
		{
			break;
		}
		if(strstr(buffer, ":[") != NULL)
		{
			size -= sayac;
		}
		if(strstr(buffer, "\n") != NULL)
		{
			size++;
		}
		sayac++;
	}
	fclose(fp);	
	
	return size-1;
}

void HisseOku(const Banka this)
{
	char* icerik = this->oku("./doc/hisseler.json");

	const cJSON* jsonHisse = NULL;
	const cJSON* jsonHisseler = NULL;
	cJSON* root = cJSON_Parse(icerik);
	if(root == NULL)
	{
		printf("root is null");
	}
	
	int i = 0;
	jsonHisseler = cJSON_GetObjectItemCaseSensitive(root, "Hisseler");
	cJSON_ArrayForEach(jsonHisse, jsonHisseler)
    {
        cJSON *id = cJSON_GetObjectItemCaseSensitive(jsonHisse, "_id");
        cJSON *sembol = cJSON_GetObjectItemCaseSensitive(jsonHisse, "Sembol");
		cJSON *ad = cJSON_GetObjectItemCaseSensitive(jsonHisse, "Ad");
		cJSON *fiyat = cJSON_GetObjectItemCaseSensitive(jsonHisse, "Fiyat");
		
		this->hisseler[i]->id = id->valuestring;
		this->hisseler[i]->sembol = sembol->valuestring;
		this->hisseler[i]->ad = ad->valuestring;
		this->hisseler[i]->fiyat = fiyat->valuedouble;
		i++;
    }
	
}

int HisseBul(char* sembol, const Banka this)
{
    for(int i = 0; i < this->size_hisse; i++)
    {
        if(strstr(this->hisseler[i]->sembol, sembol) != NULL)
        {
            return i;
        }
    }
    return -1;
}

void PortfoyOku(const Banka this)
{
	char* icerik = this->oku("./doc/portfoy.json");

	const cJSON* jsonPortfoy = NULL;
	const cJSON* jsonPortfoyler = NULL;
	cJSON* root = cJSON_Parse(icerik);
	if(root == NULL)
	{
		printf("root is null");
	}
	
	int i = 0;
	jsonPortfoyler = cJSON_GetObjectItemCaseSensitive(root, "Portfoy");
	cJSON_ArrayForEach(jsonPortfoy, jsonPortfoyler)
    {
        cJSON *id = cJSON_GetObjectItemCaseSensitive(jsonPortfoy, "_id");
        cJSON *sembol = cJSON_GetObjectItemCaseSensitive(jsonPortfoy, "Sembol");
		cJSON *maliyet = cJSON_GetObjectItemCaseSensitive(jsonPortfoy, "Maliyet");
		cJSON *adet = cJSON_GetObjectItemCaseSensitive(jsonPortfoy, "Adet");
		
		this->portfoyler[i]->id = id->valuestring;
		this->portfoyler[i]->sembol = sembol->valuestring;
		this->portfoyler[i]->maliyet = maliyet->valuedouble;
		this->portfoyler[i]->adet = adet->valuedouble;
		i++;
    }
	
}

int PortfoyBul(char* sembol, const Banka this)
{
    for(int i = 0; i < this->size_portfoy; i++)
    {
        if(strstr(this->portfoyler[i]->sembol, sembol) != NULL)
        {
            return i;
        }
    }
    return -1;
}

void EmirOku(const Banka this)
{
	char* icerik = this->oku("./doc/emirler.json");

	const cJSON* jsonEmir = NULL;
	const cJSON* jsonEmirler = NULL;
	cJSON* root = cJSON_Parse(icerik);
	if(root == NULL)
	{
		printf("root is null");
	}
	
	int i = 0;
	jsonEmirler = cJSON_GetObjectItemCaseSensitive(root, "Emirler");
	cJSON_ArrayForEach(jsonEmir, jsonEmirler)
    {
        cJSON *id = cJSON_GetObjectItemCaseSensitive(jsonEmir, "_id");
        cJSON *sembol = cJSON_GetObjectItemCaseSensitive(jsonEmir, "Sembol");
		cJSON *islem = cJSON_GetObjectItemCaseSensitive(jsonEmir, "Islem");
		cJSON *adet = cJSON_GetObjectItemCaseSensitive(jsonEmir, "Adet");
		
		this->emirler[i]->id = id->valuestring;
		this->emirler[i]->sembol = sembol->valuestring;
		this->emirler[i]->islem = islem->valuestring;
		this->emirler[i]->adet = adet->valuedouble;
		i++;
    }
	
}

int EmirBul(char* sembol, const Banka this)
{
    for(int i = 0; i < this->size_emir; i++)
    {
        if(strstr(this->emirler[i]->sembol, sembol) != NULL)
        {
            return i;
        }
    }
    return -1;
}

void KarZararYazdir(const Banka this)
{
	printf("Satışlar Kar/Zarar:\n");
	
	double guncelFiyat;
	double maliyet;
	double karZarar;
	double toplamKarZarar = 0;
	
	int i;
	for(i = 0; i < this->size_emir; i++)
	{
		if(strstr(this->emirler[i]->islem, "SATIS") != NULL)
		{
			if(this->hisseBul(this->emirler[i]->sembol,this) != -1 && this->portfoyBul(this->emirler[i]->sembol,this) != -1)
			{
				if(this->emirler[i]->adet <= this->portfoyler[this->portfoyBul(this->emirler[i]->sembol,this)]->adet)
				{
					guncelFiyat = this->emirler[i]->adet * this->hisseler[this->hisseBul(this->emirler[i]->sembol,this)]->fiyat;
					maliyet = this->emirler[i]->adet * this->portfoyler[this->portfoyBul(this->emirler[i]->sembol,this)]->maliyet;
				}
				else
				{
					guncelFiyat = this->portfoyler[this->portfoyBul(this->emirler[i]->sembol,this)]->adet * this->hisseler[this->hisseBul(this->emirler[i]->sembol,this)]->fiyat;
					maliyet = this->portfoyler[this->portfoyBul(this->emirler[i]->sembol,this)]->adet * this->portfoyler[this->portfoyBul(this->emirler[i]->sembol,this)]->maliyet;
				}
				
				karZarar = guncelFiyat - maliyet;
				
				if(karZarar > 0)
				{
					printf("%s: %0.2f TL Kar\n",this->emirler[i]->sembol,karZarar);
				}
				else if(karZarar < 0)
				{
					printf("%s: %0.2f TL Zarar\n",this->emirler[i]->sembol,-karZarar);
				}
				else
				{
					printf("%s: %0.2f TL\n",this->emirler[i]->sembol,karZarar);
				}
				toplamKarZarar += karZarar;
			}
		}
	}
	if(toplamKarZarar > 0)
    {
		printf("Toplam Kar/Zarar: +%0.2f TL\n\n",toplamKarZarar);
    }
    else
    {
		printf("Toplam Kar/Zarar: %0.2f TL\n\n",toplamKarZarar);
    }
}

void GuncelPortfoyYazdir(const Banka this)
{
    printf("Güncel Portföy:\n");

    double guncelFiyat;
    double eskiFiyat;
    double yeniFiyat;
    double yeniMaliyet;
    double yeniAdet;

    int sayac = 0;
	
	int i;
    for(i = 0; i < this->size_emir; i++)
    {
		
        if(strstr(this->emirler[i]->islem, "ALIS") != NULL)
        {
            if(this->hisseBul(this->emirler[i]->sembol,this) != -1)
            {
                if(this->portfoyBul(this->emirler[i]->sembol, this) != -1)
                {
                    guncelFiyat = this->emirler[i]->adet * this->hisseler[this->hisseBul(this->emirler[i]->sembol, this)]->fiyat;
                    eskiFiyat = this->portfoyler[this->portfoyBul(this->emirler[i]->sembol, this)]->adet * this->portfoyler[this->portfoyBul(this->emirler[i]->sembol, this)]->maliyet;
                    yeniFiyat = eskiFiyat + guncelFiyat;
                    yeniAdet = this->emirler[i]->adet + this->portfoyler[this->portfoyBul(this->emirler[i]->sembol, this)]->adet;
                }
                else
                {
                    yeniFiyat = this->emirler[i]->adet * this->hisseler[this->hisseBul(this->emirler[i]->sembol, this)]->fiyat;
                    yeniAdet = this->emirler[i]->adet;
                }

                yeniMaliyet = yeniFiyat / yeniAdet;

                if(sayac > 0)
                {
                    printf("--------------------------\n");
                }
                printf("Hisse: %s\nAdet: %0.2f\nMaliyet: %0.2f\n", this->emirler[i]->sembol, yeniAdet, yeniMaliyet);
                sayac = 1;
            }
        }
    }
    for(i = 0; i < this->size_portfoy; i++)
    {
        if(this->emirBul(this->portfoyler[i]->sembol, this) == -1)
        {
            if(sayac > 0)
            {
                printf("--------------------------\n");
            }
            printf("Hisse: %s\nAdet: %0.2f\nMaliyet: %0.2f\n", this->portfoyler[i]->sembol, this->portfoyler[i]->adet, this->portfoyler[i]->maliyet);
            sayac = 1;
        }
    }
}

void BankaYoket(Banka this)
{
	if(this == NULL) return;
	int i;
	for(i = 0; i < this->size_hisse; i++)
	{
		this->hisseler[i]->Yoket(this->hisseler[i]);
	}
	for(i = 0; i < this->size_portfoy; i++)
	{
		this->portfoyler[i]->Yoket(this->portfoyler[i]);
	}
	for(i = 0; i < this->size_emir; i++)
	{
		this->emirler[i]->Yoket(this->emirler[i]);
	}
	free(this->hisseler);
	free(this->portfoyler);
	free(this->emirler);
	free(this);
}