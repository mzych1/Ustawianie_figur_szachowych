//nazwa: Plansza.h

class Plansza
{
  private:
    int x, y;//ilosc kolumn i wierszy planszy
    int **tablica;//tablica 2wymiarowa, oznaczanie miejsc zajetych przez figury oraz miejsc bitych
  public:
    Plansza(int, int);
    ~Plansza();

    int iloscPol();
    int iloscWierszy();
    int iloscKolumn();
    int pole(int, int);
    void wypisz();

    void zajmijPole(int, int, int=1);
    void zajmijWiersz(int, int, int);
    void zajmijKolumne(int, int, int);
    void zajmijUkosy(int, int, int);

    void zwolnijPole(int, int, int=1);
    void zwolnijWiersz(int, int);
    void zwolnijKolumne(int, int);
    void zwolnijUkosy(int, int);
};

