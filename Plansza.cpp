//nazwa: Plansza.cpp

#include "Plansza.h"
#include <iostream>
//[wiersz][kolumna] ->sposob w jaki nalezy odnosic sie do pol planszy

using namespace std;

Plansza::Plansza (int a, int b)
{
  x=b;//ilosc kolumn
  y=a;//ilosc wierszy
  tablica = new int * [y];//pierwsza wspolrzedna to numer wiersza
  for(int i=0; i<y; i++)
    tablica[i]=new int [x];//druga wspolrzedna to numer kolumny

  //wyzerowanie wszystkich pol tablicy
  for(int i=0; i<y; i++)
    for(int j=0; j<x; j++)
      tablica[i][j]=0;
}

Plansza::~Plansza()//niszczenie tablicy 2wymiarowej
{
  for(int i=0; i<y; i++)
    delete [] tablica[i];
  delete [] tablica;
}

int Plansza::iloscPol()
{
  return x*y;
}

int Plansza::iloscWierszy()
{
  return y;
}

int Plansza::iloscKolumn()
{
  return x;
}

int Plansza::pole(int w, int k)
{
  return tablica[w][k];
}

void Plansza::wypisz()
{
  for(int i=0; i<y; i++)
  {
    for(int j=0; j<x; j++)
    {
      switch(tablica[i][j])
      {
        case -1: cout<<"P "; break;//pionek
        case -2: cout<<"W "; break;//wieza
        case -3: cout<<"G "; break;//goniec
        case -4: cout<<"H "; break;//hetman
        case -5: cout<<"S "; break;//skoczek
        case -6: cout<<"K "; break;//krol
        case  0: cout<<"- "; break;//pole wolne
        default: cout<<"* "; break;//pole bite
      }
    }

    cout<<endl;
  }
  cout<<"Legenda:"<<endl;
  cout<<"- ->pole wolne (nie stoi na nim figura i nie jest bite)"<<endl;
  cout<<"* ->pole bite"<<endl;
  cout<<"P ->pionek"<<endl;
  cout<<"W ->wieza"<<endl;
  cout<<"G ->goniec"<<endl;
  cout<<"H ->hetman"<<endl;
  cout<<"S ->skoczek"<<endl;
  cout<<"K ->krol"<<endl;
}

//zajmowanie odpowiednich miejsc planszy
void Plansza::zajmijPole(int w, int k, int rodzajFig)//rodzajFig to liczba -1, -2, -3, -4, -5 lub -6 (gdy oznaczamy jaka figura tam stoi) albo 1 gdy oznaczamy ze pole jest bite
{
  if(w>=0 && k>=0 && w<y && k<x)
    tablica[w][k]+=rodzajFig;

}

void Plansza::zajmijWiersz(int w, int k, int rodzajFig)
{
  for(int i=0; i<k; i++)
    tablica[w][i]++;
  tablica[w][k]=rodzajFig;//oznaczenie jaka figura stoi w danym miejscu
  for(int i=k+1; i<x; i++)
    tablica[w][i]++;
}

void Plansza::zajmijKolumne(int w, int k, int rodzajFig)
{
  for(int i=0; i<w; i++)
    tablica[i][k]++;
  tablica[w][k]=rodzajFig;//oznaczenie jaka figura stoi w danym miejscu
  for(int i=w+1; i<y; i++)
    tablica[i][k]++;}

void Plansza::zajmijUkosy(int w, int k, int rodzajFig)
{
 for(int i=1; i<=min(w,k); i++)
   tablica[w-i][k-i]++;
 for(int i=1; i<=min(w,x-k-1); i++)
   tablica[w-i][k+i]++;
 for(int i=1; i<=min(y-w-1,x-k-1); i++)
   tablica[w+i][k+i]++;
 for(int i=1; i<=min(y-w-1,k); i++)
   tablica[w+i][k-i]++;
  tablica[w][k]=rodzajFig;//oznaczenie jaka figura stoi w danym miejscu
}

//zwalnianie odpowiednich pol planszy
void Plansza::zwolnijPole(int w, int k, int rodzajFig)
{
  if(w>=0 && k>=0 && w<y && k<x)
   tablica[w][k]-=rodzajFig;
}

void Plansza::zwolnijWiersz(int w, int k)
{
  for(int i=0; i<k; i++)
    tablica[w][i]--;
  tablica[w][k]=0;
  for(int i=k+1; i<x; i++)
    tablica[w][i]--;
}

void Plansza::zwolnijKolumne(int w, int k)
{
  for(int i=0; i<w; i++)
    tablica[i][k]--;
  tablica[w][k]=0;
  for(int i=w+1; i<y; i++)
    tablica[i][k]--;
}

void Plansza::zwolnijUkosy(int w, int k)
{
  for(int i=1; i<=min(w,k); i++)
   tablica[w-i][k-i]--;
 for(int i=1; i<=min(w,x-k-1); i++)
   tablica[w-i][k+i]--;
 for(int i=1; i<=min(y-w-1,x-k-1); i++)
   tablica[w+i][k+i]--;
 for(int i=1; i<=min(y-w-1,k); i++)
   tablica[w+i][k-i]--;
 tablica[w][k]=0;
}
