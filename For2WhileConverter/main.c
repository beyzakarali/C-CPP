#include <stdio.h>
#include <stdlib.h>
void hata_bulma(char dosyaokuma[]);
int main(int argc, char *argv[])
{

    char dosyaokuma[1000];
    if (argc != 3)
    {
        printf("Istenilenleri girmediniz\n");
        exit(1);
    }
    int bbaslangic=0, bilkparantez=0, bilknoktalivirgul=0,bikincinoktalivirgul=0,bsonparantez=0,bwhilebaslangic=0;
    int ibaslangic=0, iilkparantez=0, iilknoktalivirgul=0,iikincinoktalivirgul=0,isonparantez=0,iwhilebaslangic=0;
    int suslupar=0;

    FILE *filerp=fopen( argv[1],"r");
    FILE *filewp=fopen( argv[2],"w+"); // cıktı dosyasının içini sil
    fclose(filewp);
    FILE *fileap=fopen( argv[2],"r+");

    if(filerp==NULL)
        printf("Dosya okunamadi.\n");

    else
        printf("dosya okundu.\n");


    int i=0;
    while(!feof(filerp))
    {
        dosyaokuma[i] = fgetc(filerp);
        if (ferror(filerp))
        {
            printf("Dosyadan okuma hatasi!\n");
            exit(1);
        }
        printf("%c",dosyaokuma[i]);
        i++;
    }
    for(int a=0; dosyaokuma[a]!='}'; a++)
    {

        if( (dosyaokuma[a]=='f')&& (dosyaokuma[a+1]=='o') && (dosyaokuma[a+2]=='r'))
        {
            bbaslangic=a;

            //ilk for un oldugu yere kadar olan yerler.
            for (i=0; i<bbaslangic; i++)
            {
                fputc(dosyaokuma[i],fileap);
            }

            while(dosyaokuma[a-1] !='(')
            {
                bilkparantez=a;
                a++;
            }
            while(dosyaokuma[a-1] !=';')
            {
                bilknoktalivirgul=a;
                a++;
            }

            for (i=bilkparantez+1 ; i<=bilknoktalivirgul; i++)
            {
                fputc(dosyaokuma[i],fileap);
            }

            fputs("\nwhile(",fileap);
            a++;

            while(dosyaokuma[a-1] !=';')
            {
                bikincinoktalivirgul=a;
                a++;
            }

            for (i=bilknoktalivirgul+1 ; i<bikincinoktalivirgul; i++)
            {
                fputc(dosyaokuma[i],fileap);
            }

            fputs(")\n",fileap);


            while(dosyaokuma[a-1] !=')')
            {
                bsonparantez=a;
                a++;
            }


            for( ; dosyaokuma[a]!='}'; a++)
            {


                if( (dosyaokuma[a]=='f')&& (dosyaokuma[a+1]=='o') && (dosyaokuma[a+2]=='r'))
                {

                    while(dosyaokuma[a-1] !='(')
                    {
                        iilkparantez=a;
                        a++;
                    }
                    while(dosyaokuma[a-1] !=';')
                    {
                        iilknoktalivirgul=a;
                        a++;
                    }
                    for (i=iilkparantez+1 ; i<=iilknoktalivirgul; i++)
                    {
                        fputc(dosyaokuma[i],fileap);
                    }

                    fputs("\nwhile(",fileap);
                    a++;

                    while(dosyaokuma[a-1] !=';')
                    {
                        iikincinoktalivirgul=a;
                        a++;
                    }

                    for (i=iilknoktalivirgul+1 ; i<iikincinoktalivirgul; i++)
                    {
                        fputc(dosyaokuma[i],fileap);
                    }

                    fputs(")\n",fileap);
                    a++;

                    while(dosyaokuma[a-1] !=')')
                    {
                        isonparantez=a;
                        a++;
                    }


                    while(dosyaokuma[a-1] !='}')
                    {
                        suslupar=a;
                        a++;
                    }

                    for (i=isonparantez+1 ; i<suslupar; i++)
                    {
                        fputc(dosyaokuma[i],fileap);
                    }


                }
                fputc(dosyaokuma[a],fileap);

            }

            //2. döngü var mi tespiti
            if((iikincinoktalivirgul!=0)&&(isonparantez!=0))
            {

                for (i=iikincinoktalivirgul+1 ; i<isonparantez; i++)
                {
                    fputc(dosyaokuma[i],fileap);
                }

                if(dosyaokuma[i]!=';')
                    fputc(';',fileap);

                fputs("\n}",fileap);
            }

            for (i=bikincinoktalivirgul+1 ; i<bsonparantez; i++)
            {
                fputc(dosyaokuma[i],fileap);
            }
            if(dosyaokuma[i]!=';')
                fputc(';',fileap);
            fputs("\n}",fileap);
            a++;
        }


    }


    fclose(filerp);
    fclose(fileap);

    return 0;
}

void hata_bulma(char dosyaokuma[])
{
    int i=0;

    for(i=0 ; dosyaokuma[i] != '\0' ; i++){
        if((dosyaokuma[i] == '\n') && (dosyaokuma[i-1] != ';'))
        {
            if(dosyaokuma[i-1]=='}'|| dosyaokuma[i-1]=='{' || dosyaokuma[i-1] == '\n'){
                continue;
            }
            printf("\nHATA\n");
            exit(1);
        }

    }
}
