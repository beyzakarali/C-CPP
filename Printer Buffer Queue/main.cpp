#include <iostream>
#include <fstream>
#include <string>
#define SIZE  100

using namespace std;

void Ekle(struct belge temp1[], struct belge belge2[]);
void Cikar(struct belge belge3[]);

struct tarih {

	int yil;
	int  ay;
	int gun;
	int saat;
	int dakika;
	int saniye;

};

struct belge_sahibi {
	string ad;
	string soyad;
	string k_adi;
	string eposta;
	int d_yil;
};
struct belge
{
	string belgeadi;
	string belgeboyut;
	int  sayfasayisi;
	tarih tarih1;
	belge_sahibi  belge_sahibi1;

};

void Ekle(struct belge temp1[],struct belge belge2[]) {
	for (int i = 0; i < SIZE; i++) {

		if (belge2[i].belgeadi == "") {
			belge2[i] = temp1[0];
			cout << "PC kuyruga yazdi\t" ;
			Cikar(temp1);
			break;
		}
	}
}

void Cikar(struct belge belge3[]) {

	cout << belge3[0].belgeadi << "\tyazdi..." << endl;

	for (int i = 0; i < SIZE-2; i++) {

		belge3[i] = belge3[i + 1];

	}
}

int main()
{
	int saniye=0,hiz,sn,i=0 , sayfa_sayisi=0;

	belge temp[SIZE];
	belge belge1[SIZE];


	ifstream dosya1;
	dosya1.open("belgeler.txt");
	cout << "Dosya acildi.." << endl;

	cout << "PC kac saniyede kuyruga belge gonderir (sn) : ?" << endl;
	cin >> sn;

	cout << "Yazicinin bir sayfayi yazma hizi nedir? (cn): ?" << endl;
	cin >> hiz;


	while (!dosya1.eof()) {
		dosya1 >> temp[i].belgeadi >> temp[i].belgeboyut >> temp[i].sayfasayisi >> temp[i].belge_sahibi1.ad >> temp[i].belge_sahibi1.soyad
			>> temp[i].belge_sahibi1.k_adi >> temp[i].belge_sahibi1.eposta >> temp[i].belge_sahibi1.d_yil >> temp[i].tarih1.yil >> temp[i].tarih1.ay
			>> temp[i].tarih1.gun >> temp[i].tarih1.saat >> temp[i].tarih1.dakika >> temp[i].tarih1.saniye;
			i++;
	}

	for (;;) {

		if (saniye%sn == 0){
			cout << saniye << ".saniye\t-\t";
			Ekle(temp, belge1);

		}

		if (belge1[0].belgeadi == "" && saniye%sn == 0) break;

		if (sayfa_sayisi == 0) {
			cout << saniye << ".saniye\t-\t";
			sayfa_sayisi = belge1[0].sayfasayisi;
			Cikar(belge1);


		}
		else
			sayfa_sayisi--;


		saniye++;
	}

	     dosya1.close();
		 cout << "Tum belgeler yazdirildi...";



		 getchar();
		 getchar();

	     return 0;


}

