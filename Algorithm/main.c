#include <stdio.h>
#include <stdlib.h>

int d1bulma (long long sayi);
long long yenisayiolustur(long long sayi, int d1);


int main(int argc, char *argv[])
{
    printf("\t\t Numerical Integration \n");

    long long sayi,yenisayi;
    int d1;

	if (argc <= 1) {
		printf("sayi girmediniz\n");
		exit(1);
	}
	sayi = atoll(argv[1]);


    d1=d1bulma(sayi);
    yenisayi=yenisayiolustur(sayi,d1);

    printf("d1:%d\n",d1);

    if(sayi/100000000==0){
            printf("yenisayi:%s%d",argv[1],d1);
    }
    else
        printf("yenisayi:%lld",yenisayi);


    return 0;
}

int d1bulma (long long sayi)
{

    int rakamlar,aratoplam,d1;
    int toplam=0;
    int i =2;

    while (i<11){
        if(sayi!=0){
            rakamlar=sayi%10;
            aratoplam=rakamlar*(i);
            sayi=sayi/10;
            toplam = toplam + aratoplam;
            i++;
        }
        else{
            break;
        }
    }

    if(toplam%11!=0){
        d1=11-(toplam%11);
    }
    else{
        d1=0;
    }
     return d1;
}

long long yenisayiolustur(long long sayi, int d1)
{

    long long yenisayi;
    if (d1!=10){
            yenisayi=sayi*10+d1;
        }
        else{
            yenisayi=sayi*100+d1;
         }
        return yenisayi;
    }

