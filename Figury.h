//nazwa: Figury.h

#include<iostream>

using namespace std;

//klasy potrzebne do rozrozniania metod w szablonie Figura
class Krol{};
class Goniec{};
class Hetman{};
class Pionek{};
class Wieza{};
class Skoczek{};

//klasa abstrakcyjna, dzieki jej uzyciu wszystkie obiekty mozna przechowywac w jednym wektorze
class Pojemnik
{
public:
  virtual void ustaw(Plansza&, int, int)=0;
  virtual void zdejmij(Plansza&)=0;
  virtual bool czyBije(Plansza&, int, int)=0;
  virtual int podajWiersz()=0;
  virtual int podajKolumne()=0;
};

template <typename Typ>
class Figura:public Pojemnik
{
private:
  int wiersz, kolumna;//wiersz i kolumna w ktorej aktualnie ustawiony jest obiekt
public:
  Figura();
  ~Figura(){}
  int podajWiersz(), podajKolumne();
  void ustaw(Plansza&, int, int);
  void zdejmij(Plansza&);
  bool czyBije(Plansza&, int, int);
};

template <typename Typ>
Figura<Typ>::Figura()
{
  wiersz=-1;
  kolumna=-1;
}

//informacja o tym w ktorym wierszu i kolumnie stoi figura
template <typename Typ>
int Figura<Typ>::podajWiersz()
{
  return wiersz;
}

template <typename Typ>
int Figura<Typ>::podajKolumne()
{
  return kolumna;
}

//ustawianie figur na planszy oraz oznaczanie pol przez nie bitych
template<>
void Figura<Krol>::ustaw(Plansza& p, int w, int k)
{
  wiersz=w;
  kolumna=k;
  //cout<<"Ustawiono krola"<<endl;
  p.zajmijPole(w, k, -6);//oznaczanie pola na ktorym ustawiony jest krol
  //oznaczanie pol ktore sa bite przez krola
  p.zajmijPole(w, k-1);
  p.zajmijPole(w, k+1);
  p.zajmijPole(w-1, k-1);
  p.zajmijPole(w-1, k);
  p.zajmijPole(w-1, k+1);
  p.zajmijPole(w+1, k-1);
  p.zajmijPole(w+1, k);
  p.zajmijPole(w+1, k+1);
}

template <>
void Figura<Wieza>::ustaw(Plansza& p, int w, int k)
{
  wiersz=w;
  kolumna=k;
  //cout<<"Ustawiono wieze"<<endl;
  //oznaczanie pol ktore sa bite przez wieze oraz miejsca na ktorym bedzie ona stala
  p.zajmijWiersz(w, k, -2);
  p.zajmijKolumne(w, k, -2);
}

template <>
void Figura<Hetman>::ustaw(Plansza& p, int w, int k)
{
  wiersz=w;
  kolumna=k;
  //cout<<"Ustawiono hetmana"<<endl;
  //oznaczanie pol ktore sa bite przez hetmana oraz miejsca na ktorym bedzie on stal
  p.zajmijWiersz(w, k, -4);
  p.zajmijKolumne(w, k, -4);
  p.zajmijUkosy(w, k, -4);
}

template <>
void Figura<Pionek>::ustaw(Plansza& p, int w, int k)
{
  wiersz=w;
  kolumna=k;
  //cout<<"Ustawiono pionek"<<endl;
  p.zajmijPole(w, k, -1);//ozneczanie miejsca na ktorym bedzie stal pionek
  //oznaczanie pol bitych przez pionka
  p.zajmijPole(w-1, k-1);
  p.zajmijPole(w-1, k+1);
}

template <>
void Figura<Skoczek>::ustaw(Plansza& p, int w, int k)
{
  wiersz=w;
  kolumna=k;
  //cout<<"Ustawiono skoczka"<<endl;
  p.zajmijPole(w, k, -5);//oznaczene miejsca na ktorym bedzie stal skoczek
  //oznaczenie pol bitych przez skoczka
  p.zajmijPole(w-1, k-2);
  p.zajmijPole(w-2, k-1);
  p.zajmijPole(w-2, k+1);
  p.zajmijPole(w-1, k+2);
  p.zajmijPole(w+1, k+2);
  p.zajmijPole(w+2, k+1);
  p.zajmijPole(w+2, k-1);
  p.zajmijPole(w+1, k-2);
}

template <>
void Figura<Goniec>::ustaw(Plansza& p, int w, int k)
{
  wiersz=w;
  kolumna=k;
  //cout<<"Ustawiono gonca"<<endl;
  //oznaczanie pol ktore sa bite przez gonca oraz miejsca na ktorym bedzie on stal
  p.zajmijUkosy(w, k, -3);
}

//zdejmowanie figur
template<>
void Figura<Krol>::zdejmij(Plansza& p)
{
  int w=wiersz;
  int k=kolumna;
  //cout<<"Zdjeto krola"<<endl;
  p.zwolnijPole(w, k, -6);
  p.zwolnijPole(w, k-1);
  p.zwolnijPole(w, k+1);
  p.zwolnijPole(w-1, k-1);
  p.zwolnijPole(w-1, k);
  p.zwolnijPole(w-1, k+1);
  p.zwolnijPole(w+1, k-1);
  p.zwolnijPole(w+1, k);
  p.zwolnijPole(w+1, k+1);
}

template <>
void Figura<Wieza>::zdejmij(Plansza& p)
{
  int w=wiersz;
  int k=kolumna;
  //cout<<"Zdjeto wieze"<<endl;
  p.zwolnijWiersz(w, k);
  p.zwolnijKolumne(w, k);
}

template <>
void Figura<Hetman>::zdejmij(Plansza& p)
{
  int w=wiersz;
  int k=kolumna;
 // cout<<"Zdjeto hetmana"<<endl;
  p.zwolnijWiersz(w, k);
  p.zwolnijKolumne(w, k);
  p.zwolnijUkosy(w, k);
}

template <>
void Figura<Pionek>::zdejmij(Plansza& p)
{
  int w=wiersz;
  int k=kolumna;
  //cout<<"Zdjeto pionek"<<endl;
  p.zwolnijPole(w, k, -1);
  p.zwolnijPole(w-1, k-1);
  p.zwolnijPole(w-1, k+1);
}

template <>
void Figura<Skoczek>::zdejmij(Plansza& p)
{
  int w=wiersz;
  int k=kolumna;
  //cout<<"Zdjeto skoczka"<<endl;
  p.zwolnijPole(w, k, -5);
  p.zwolnijPole(w-1, k-2);
  p.zwolnijPole(w-2, k-1);
  p.zwolnijPole(w-2, k+1);
  p.zwolnijPole(w-1, k+2);
  p.zwolnijPole(w+1, k+2);
  p.zwolnijPole(w+2, k+1);
  p.zwolnijPole(w+2, k-1);
  p.zwolnijPole(w+1, k-2);
}

template <>
void Figura<Goniec>::zdejmij(Plansza& p)
{
  int w=wiersz;
  int k=kolumna;
  //cout<<"Zdjeto gonca"<<endl;
  p.zwolnijUkosy(w, k);
}

//sprawdzanie czy ustawienie figury nie spowoduje bicia innej figury
template<>
bool Figura<Krol>::czyBije(Plansza& p, int w, int k)
{
  //ujemna wartosc w polu planszy oznacza ze stoi tam juz jakas figura
  if(k-1>=0 && p.pole(w, k-1)<0)
    return true;
  if(k+1<p.iloscKolumn() && p.pole(w, k+1)<0)
    return true;
  if(k-1>=0 && w-1>=0 && p.pole(w-1, k-1)<0)
    return true;
  if(w-1>=0 && p.pole(w-1, k)<0)
    return true;
  if(w-1>=0 && k+1<p.iloscKolumn() && p.pole(w-1, k+1)<0)
    return true;
  if(k-1>=0 && w+1<p.iloscWierszy() && p.pole(w+1, k-1)<0)
    return true;
  if(w+1<p.iloscWierszy() && p.pole(w+1, k)<0)
    return true;
  if(w+1<p.iloscWierszy() && k+1<p.iloscKolumn() && p.pole(w+1, k+1)<0)
    return true;

  return false;
}

template <>
bool Figura<Wieza>::czyBije(Plansza& p, int w, int k)
{
  for(int i=0; i<p.iloscKolumn(); i++)//sprawdzanie wiersza
    if(p.pole(w, i)<0)
      return true;
  for(int i=0; i<p.iloscWierszy(); i++)//sprawdzanie kolumny
    if(p.pole(i, k)<0)
      return true;

  return false;
}

template <>
bool Figura<Hetman>::czyBije(Plansza& p, int w, int k)
{
  for(int i=0; i<p.iloscKolumn(); i++)//sprawdzanie wiersza
    if(p.pole(w, i)<0)
      return true;
  for(int i=0; i<p.iloscWierszy(); i++)//sprawdzanie kolumny
    if(p.pole(i, k)<0)
      return true;
  //sprawdzanie ukosow
  for(int i=1; i<=min(w,k); i++)
    if(p.pole(w-i, k-i)<0)
      return true;
 for(int i=1; i<=min(w,p.iloscKolumn()-k-1); i++)
    if(p.pole(w-i, k+i)<0)
      return true;
 for(int i=1; i<=min(p.iloscWierszy()-w-1,p.iloscKolumn()-k-1); i++)
    if(p.pole(w+i, k+i)<0)
      return true;
 for(int i=1; i<=min(p.iloscWierszy()-w-1,k); i++)
    if(p.pole(w+i, k-i)<0)
      return true;

 return false;
}

template <>
bool Figura<Pionek>::czyBije(Plansza& p, int w, int k)
{
  if(w-1>=0 && k-1>=0 && p.pole(w-1, k-1)<0)
    return true;
  if(w-1>=0 && k+1<p.iloscKolumn() && p.pole(w-1, k+1)<0)
    return true;

  return false;
}

template <>
bool Figura<Skoczek>::czyBije(Plansza& p, int w, int k)
{
  if(w-1>=0 && k-2>=0 && p.pole(w-1, k-2)<0)
    return true;
  if(w-2>=0 && k-1>=0 && p.pole(w-2, k-1)<0)
    return true;
  if(k+1<p.iloscKolumn() && w-2>=0 && p.pole(w-2, k+1)<0)
    return true;
  if(w-1>=0 && k+2<p.iloscKolumn() && p.pole(w-1, k+2)<0)
    return true;
  if(w+1<p.iloscWierszy() && k+2<p.iloscKolumn() && p.pole(w+1, k+2)<0)
    return true;
  if(w+2<p.iloscWierszy() && k+1<p.iloscKolumn() && p.pole(w+2, k+1)<0)
    return true;
  if(w+2<p.iloscWierszy() && k-1>=0 && p.pole(w+2, k-1)<0)
    return true;
  if(w+1<p.iloscWierszy() && k-2>=0 && p.pole(w+1, k-2)<0)
    return true;

  return false;
}

template <>
bool Figura<Goniec>::czyBije(Plansza& p, int w, int k)
{
  for(int i=1; i<=min(w,k); i++)
    if(p.pole(w-i, k-i)<0)
      return true;
 for(int i=1; i<=min(w,p.iloscKolumn()-k-1); i++)
    if(p.pole(w-i, k+i)<0)
      return true;
 for(int i=1; i<=min(p.iloscWierszy()-w-1,p.iloscKolumn()-k-1); i++)
    if(p.pole(w+i, k+i)<0)
      return true;
 for(int i=1; i<=min(p.iloscWierszy()-w-1,k); i++)
    if(p.pole(w+i, k-i)<0)
      return true;

 return false;
 }
