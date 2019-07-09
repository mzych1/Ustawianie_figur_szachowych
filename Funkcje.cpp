//nazwa: Funkcje.cpp

#include "Funkcje.h"
#include "Plansza.h"
#include "Figury.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

Plansza *plansza;
vector<Pojemnik* > wektor;
bool czyWypisacPlansze = true;

void menu()
{
  char wybor;

  cout << "--------------------------------------------" << endl;
  cout << "1. Szukanie ustawienia bez bic"<<endl;
  cout << "2. Testy"<<endl;
  cout << "3. Wyjscie"<<endl;

  do
  {
    cin>>wybor;
  }while(wybor!='1' && wybor!='2' && wybor!='3');

  switch(wybor)
  {
    case '1': szukajUstawienia(); break;
    case '2':
            test(8, 8, 0, 0, 0, 8);
            test(3, 3, 0, 2, 1);
            test(5, 4, 0, 0, 0, 0, 8, 1);
            test(4, 3, 8);
            test(10, 10, 2, 3, 8, 1, 3, 2);
      break;
    case '3': wyjscie(); break;//wylaczenie programu
  }
}

void wyjscie()
{
  exit(0);
}

int wczytajDane()//zwraca ilosc wybranych figur
{
  int a, b, wiezaHetman=0;
  cout<<"** Wymiary planszy **"<<endl;
  cout<<"Podaj liczbe wierszy planszy: "<<endl;
  a=poprWczytanie(true);
  cout<<"Podaj liczbe kolumn planszy: "<<endl;
  b=poprWczytanie(true);
  plansza = new Plansza(a, b);//tworzenie obiektu plansza

  do
  {
    if(b==0)
      cout<<"Nie podano zadnej figury"<<endl;
    b=0;//b teraz jest iloscia wszystkich figur
    cout<<"** Ilosc poszczegolnych typow figur **"<<endl;

    cout<<"Podaj liczbe pionkow: "<<endl;
    a=poprWczytanie();
    b+=a;
    for(int i=0; i<a; i++)//tworzenie odpowiedniej ilosci pionkow
      wektor.push_back(new Figura<Pionek>);

    cout<<"Podaj liczbe wiez: "<<endl;
    a=poprWczytanie();
    b+=a;
    wiezaHetman+=a;
    for(int i=0; i<a; i++)
      wektor.push_back(new Figura<Wieza>);

    cout<<"Podaj liczbe goncow: "<<endl;
    a=poprWczytanie();
    b+=a;
    for(int i=0; i<a; i++)
      wektor.push_back(new Figura<Goniec>);

    cout<<"Podaj liczbe hetmanow: "<<endl;
    a=poprWczytanie();
    b+=a;
    wiezaHetman+=a;
    for(int i=0; i<a; i++)
      wektor.push_back(new Figura<Hetman>);

    cout<<"Podaj liczbe skoczkow: "<<endl;
    a=poprWczytanie();
    b+=a;
    for(int i=0; i<a; i++)
      wektor.push_back(new Figura<Skoczek>);

    cout<<"Podaj liczbe kroli: "<<endl;
    a=poprWczytanie();
    b+=a;
    for(int i=0; i<a; i++)
      wektor.push_back(new Figura<Krol>);
  }while(b==0);

  if(wiezaHetman>min(plansza->iloscWierszy(), plansza->iloscKolumn()))
    return plansza->iloscPol()+10;
  else
    return b;
}

int poprWczytanie(bool czyPlansza)
{
  int x;

  if(czyPlansza)
  {
    do//przy wczytywaniu wymiarow planszy, liczba musi byc dodatna
    {
      cin.clear();//czyszczenie flagi bledu
      cin.ignore( 1000, '\n' );
      cin>>x;
    }while(cin.good()==0 || x<=0);
  }
  else
  {
    do//przy wczytywaniu ilosci figur, liczba musi byc nieujemna
    {
      cin.clear();//czyszczenie flagi bledu
      cin.ignore( 1000, '\n' );
      cin>>x;
    }while(cin.good()==0 || x<0);
  }

  return x;
}

void szukajUstawienia()
{
  if(wczytajDane() > plansza->iloscPol())//gdy jest wiecej figur niz pol planszy lub hetmanow i wiez jest lacznie za duzo aby mozna bylo je rozstawic (kazda z tych figur zajmuje cala kolumne i wiersz)
    cout<<"Ustawienie podanych figur bez bic jest niemozliwe"<<endl;
  else
    {
     czyWypisacPlansze=true;
     algorytm(0, 0, 0);
     if(czyWypisacPlansze)
       plansza->wypisz();
    }
  usunObiekty();
}

void usunObiekty()
{
  delete plansza;
  for(int i=0; i<wektor.size(); i++)
      delete wektor[i];
  wektor.clear();
}

void algorytm(int w, int k, int nrFig)
{
  for(int i=w; i<plansza->iloscWierszy(); i++)
    for(int j=k; j<plansza->iloscKolumn(); j++)
      if(plansza->pole(i, j)==0 && !(wektor[nrFig]->czyBije(*plansza, i, j)))//ustawianie figury jesli pole jest puste (inna figura tam nie stoi ani pole nie jest bite)
                                                             //i ustawienie na tym polu figury nie spowoduje bicia wczesniej ustawionej figury
        {
          wektor[nrFig]->ustaw(*plansza, i, j);
          //cout<<"Ustawiono figure "<<nrFig<<endl;
          nrFig++;
          if(nrFig<wektor.size())
            algorytm(0, 0, nrFig);
          return;
        }
  //gdy nie ma gdzie ustawic figury trzeba sciagnac poprzednia
  if(nrFig==0 || (nrFig==1 && (wektor[0]->podajWiersz()) > (plansza->iloscWierszy())/2))//jesli figura o numerze 0 byla juz ustawiana na gornej polowie planszy
    { //i nie znaleziono rozwiazania to znaczy ze nie da sie ustawic figur bez bic (bo roziazania sa symetryczne, poza sytuacjami z pionkami, dla ktorych bardziej
      cout<<"Ustawienie podanych figur bez bic jet niemozliwe"<<endl;//korzystne jest usawienie na gorzze planszy - w 0 wierszu pionek nie powoduje zadnego bicia)
      czyWypisacPlansze=false;
    }
    else
    {
      nrFig--;
      wektor[nrFig]->zdejmij(*plansza);
      //cout<<"Zdjeto figure "<<nrFig<<endl;
      if(wektor[nrFig]->podajKolumne()==(plansza->iloscKolumn())-1)//gdy wczesniej figura stala w ostatniej kolumnie
      {
        algorytm(wektor[nrFig]->podajWiersz()+1 , 0, nrFig);//szukanie wolnych miejsc od nastepnego wiersza i zerowej kolumny
        return;
      }
      else
      {
        algorytm(wektor[nrFig]->podajWiersz(), (wektor[nrFig]->podajKolumne())+1, nrFig);//szukanie wolnych miejsc od nastepnej kolumny i tego samego wiersza
        return;
      }
    }
}

void test(int wi, int kol, int p, int w, int g, int h, int s, int k)
{
  plansza = new Plansza(wi, kol);//tworzenie obiektu plansza

  for(int i=0; i<p; i++)//tworzenie odpowiedniej ilosci pionkow
      wektor.push_back(new Figura<Pionek>);
  for(int i=0; i<w; i++)
      wektor.push_back(new Figura<Wieza>);
  for(int i=0; i<g; i++)
    wektor.push_back(new Figura<Goniec>);
  for(int i=0; i<h; i++)
    wektor.push_back(new Figura<Hetman>);
  for(int i=0; i<s; i++)
    wektor.push_back(new Figura<Skoczek>);
  for(int i=0; i<k; i++)
    wektor.push_back(new Figura<Krol>);

  cout<<endl;
  cout<<"** Wymiary planszy **"<<endl;
  cout<<"Ilosc wierszy: "<<wi<<endl;
  cout<<"Ilosc kolumn: "<<kol<<endl;
  cout<<"** Ilosc poszczegolnych typow figur **"<<endl;
  if(p>0)
    cout<<"Pionki: "<<p<<endl;
  if(w>0)
    cout<<"Wieze: "<<w<<endl;
  if(g>0)
    cout<<"Gonce: "<<g<<endl;
  if(h>0)
    cout<<"Hetmany: "<<h<<endl;
  if(s>0)
    cout<<"Skoczki: "<<s<<endl;
  if(k>0)
    cout<<"Krole: "<<k<<endl;

  if(wektor.size()>plansza->iloscPol())
    cout<<"Ustawienie podanych figur bez bic jest niemozliwe (podano wiecej figur niz jest pol planszy)."<<endl;
  else
  {
   czyWypisacPlansze=true;
   algorytm(0, 0, 0);
   if(czyWypisacPlansze)
     plansza->wypisz();
  }

  usunObiekty();
}
