#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

class space{

public:
     space(int w, int h)
     {
            spacewidth=w;
            spaceheight=h;
     }

    class Box{

        public:
       class coord{
           private:
               int x;
               int y;

           public:
               int getx(){
                 return x;
               }
               void setx(int a){
                   x=a;
               }
               int gety(){
                  return y;
               }
               void sety(int b){
                   y=b;
               }
       }coordinate;

    private:
        double density;
        double  width;
        double height;

    public:
        double getdensity(){
            return density;
        }
        void setdensity(int d){
            density=d;
        }
        double getwidth(){
            return width;
        }
        void setwidth(int w){
            width=w;
        }
        double getheight(){
            return height;
        }
        void setheight(int h){
            height=h;
        }

    }kutular[20];



    void fillRandomBox(int boxcnt, int maxboxdimension, int boxdensity)
    {

       if((maxboxdimension>getspaceheight())||(maxboxdimension>getspacewidth())){
           cout<<"Kutu spaceden buyuk olamaz"<<endl;

           return ;
           }


        srand(time(0));
        boxcount = boxcnt;
        maxboxd =maxboxdimension;
        for (int i=0;i<boxcnt;i++)
        {
            int uyg=0;
            int dimwidth = 1 + rand()% maxboxdimension;
            int dimheight = 1 + rand()% maxboxdimension;

            int y=0;
            int x=0;
            while(y<spaceheight){
                    while(x<spacewidth){

                    kutular[i].coordinate.setx(-1);
                    kutular[i].coordinate.sety(-1);
                    kutular[i].setheight(0);
                    kutular[i].setwidth(0);


                    if (uygunmu(x,y,dimwidth,dimheight,i)==1)
                    {
                        kutular[i].coordinate.setx(x);
                        kutular[i].coordinate.sety(y);
                        kutular[i].setheight(dimheight);
                        kutular[i].setwidth(dimwidth);

                        x=spacewidth;
                        y=spaceheight;
                    }
                     else
                    {

                        kutular[i].setheight(dimheight);
                        kutular[i].setwidth(dimwidth);
                    }

                    y++;
                    x++;
                }
            }
                kutular[i].setdensity(boxdensity);
         }


    }

    void printBoxCoordinates()
    {
        int yerlesemeyenler=0;

        for(int i=0;i<boxcount;i++)
        {
          if ((kutular[i].coordinate.getx()>=0)&&(kutular[i].coordinate.getx()+kutular[i].getwidth()>=0)){

            cout<<kutular[i].coordinate.getx()<<","<<kutular[i].coordinate.gety()<<"\t"
                 <<kutular[i].coordinate.getx()+kutular[i].getwidth()<<","
                 <<kutular[i].coordinate.gety()+kutular[i].getheight()<<"\t"
                 <<kutular[i].getdensity() << endl;
        }
          else

             yerlesemeyenler++;
      }

      cout<<"yerlesemeyen kutu sayisi:"<<yerlesemeyenler<<endl;

        for(int i=0;i<boxcount;i++)
        {

          if (kutular[i].coordinate.getx()<0||kutular[i].coordinate.gety()<0){
            cout<<kutular[i].coordinate.getx()+kutular[i].getwidth()<<","
                 <<kutular[i].coordinate.gety()+kutular[i].getheight()<<"\t"
                 <<kutular[i].getwidth()<<"x"<<kutular[i].getheight()<< endl;
            }
         }


       }

    void printCenterOfMass()
    {

        double totalMass=0,topx=0,topy=0;
        double bm;


        for (int i=0;i<boxcount;i++)
        {
         if((kutular[i].coordinate.getx()>=0)&&(kutular[i].coordinate.gety()>=0)){

            bm = kutular[i].getwidth() * kutular[i].getheight() * kutular[i].getdensity();//kutu k�tlesi
            topx += bm * ((kutular[i].coordinate.getx() + (kutular[i].coordinate.getx()+ kutular[i].getwidth())) /2);
            topy += bm * ((kutular[i].coordinate.gety() +  (kutular[i].coordinate.gety()+kutular[i].getheight())) /2);
            totalMass += bm;
          }
        }

        cout <<"Center of mass of space:\t(" << topx/totalMass <<","<<topy/totalMass<<")"<<endl;
       }
    int uygunmu(int ax,int ay,int w,int h,int k)
    {
        // daha once sol kose olarak girilmis mi kontrol ediyoruz
        for (int z=0;z<k;z++)
        {
            if (kutular[z].coordinate.getx()==ax && kutular[z].coordinate.gety()==ay)
            {//ayni noktadan baslanmasi engellendi.

                return 0;
            }
        }

        for (int a=0;a<=w+1;a++)//genislik icin
        {
            for (int b=0;b<=h+1;b++)//yukseklik icin
            {
                for (int z=0;z<k;z++)//kutular icin
                {
                    if ((ax+a>=spacewidth)|| (ay+b>=spaceheight))
                    {
                        return 0;
                    } else if (ax+a>kutular[z].coordinate.getx()&& ax+a<kutular[z].coordinate.getx()+kutular[z].getwidth() &&
                               ay+b>kutular[z].coordinate.gety() && ay+b<kutular[z].coordinate.gety()+kutular[z].getheight())
                               {
                                   return 0;
                               }
                               else
                               {

                               }
                }
            }
        }
        return 1;
    }
private:
     int boxcount;
     double maxboxd;
     int spacewidth;
     int spaceheight;

public:
    double getmaxboxd(){
       return maxboxd;
    }
    double getspaceheight(){
      return spaceheight;
    }
    double getspacewidth(){
      return spacewidth;
    }
    void dosyayaz(){

    ofstream dosya;
    dosya.open("kutuspace.txt");

     int y=0;
     for(int i=0;i<boxcount;i++){
       if ((kutular[i].coordinate.getx()>=0)&&(kutular[i].coordinate.getx()+kutular[i].getwidth()>=0)){
        dosya<<kutular[i].coordinate.getx()<<","<<kutular[i].coordinate.gety()<<"\t\t"
                 <<kutular[i].coordinate.getx()+kutular[i].getwidth()<<","
                 <<kutular[i].coordinate.gety()+kutular[i].getheight()<<"\t\t"
                 <<kutular[i].getdensity() << endl;
       }
        else
              y++;
     }

     dosya<<"yerlesemeyen kutu sayisi:"<<y<<endl;

      for(int i=0;i<boxcount;i++)
        {
          if (kutular[i].coordinate.getx()<0||kutular[i].coordinate.gety()<0){
            dosya<<kutular[i].coordinate.getx()+kutular[i].getwidth()<<","
                 <<kutular[i].coordinate.gety()+kutular[i].getheight()<<"\t\t"
                 <<kutular[i].getwidth()<<"x"<<kutular[i].getheight()<< endl;
}
}


     double totalMass=0,topx=0,topy=0;
        double bm;


        for (int i=0;i<boxcount;i++)
        {
         if((kutular[i].coordinate.getx()>=0)&&(kutular[i].coordinate.gety()>=0)){

            bm = kutular[i].getwidth() * kutular[i].getheight() * kutular[i].getdensity();
            topx += bm * ((kutular[i].coordinate.getx() + (kutular[i].coordinate.getx()+ kutular[i].getwidth())) /2);
            topy += bm * ((kutular[i].coordinate.gety() +  (kutular[i].coordinate.gety()+kutular[i].getheight())) /2);
            totalMass += bm;
        }
        }

        dosya <<"Center of mass of space:\t(" << topx/totalMass <<","<<topy/totalMass<<")"<<endl;
    }

};

int main()
{

    space a(10,10);
    if((a.getmaxboxd()>a.getspaceheight())||(a.getmaxboxd()>a.getspacewidth())){
           cout<<"Kutu spaceden buyuk olamaz"<<endl;

           return 0;
           }
    else{
        a.fillRandomBox(15,6,1);//yerlestirilecek kutu sayısı,boyut sınırı,yogunluk
        a.printBoxCoordinates();
        a.printCenterOfMass();
        a.dosyayaz();

    return 0;
    }
}
