#include <iostream>
#include <new>

using namespace std;

class Bazarek
{
  private :
    long long iloscProduktow;
    long long * produkty;
    //liczba nieparzystych i parzystych cen produktów.
    long long nieparzyste,parzyste;
    long  long liczbaDni;
    long long * dni;
    //Tablice z liczbami cen parzystych i nieparzystych.
    long long * tablicaParzysta;
    long long * tablicaNieparzysta;
    //Tablica wyników.
    long long * wyniki;

  public : 
    void wejscie()
    //Wczytujemy wejście, czyli ilość produktów i ich ceny oraz liczbę dni i ile
    //bajtula kupuje produktów każdego dnia oraz tworzymy tablice na wyniki.
    {
      cin>>iloscProduktow;
      parzyste = 0;
      nieparzyste = 0;
      produkty = new long long[iloscProduktow];
      for (long long i = 0; i < iloscProduktow; i++)
      {
        cin>>produkty[i];
        if (produkty[i] % 2 == 0) {
          parzyste++;
        }
        else {
          nieparzyste++;    
        }
      }
      cin>>liczbaDni;
      dni = new long long[liczbaDni];
      for (long long i = 0; i < liczbaDni; i++)
      {
        cin>>dni[i];
      }
      wyniki = new long long[iloscProduktow]; 
    };
  
    void wczytajDoTablic()
    //Wczytujemy do tablic liczby parzyste i nieparzyste.
    {
      tablicaParzysta = new long long[parzyste];
      tablicaNieparzysta = new long long[nieparzyste];
      long long jPar = 0;
      long long jNpar = 0;
      for (long long i = 0; i < iloscProduktow; i++)
      {
        if (produkty[i] % 2 == 0) {
          tablicaParzysta[jPar] = produkty[i];
          jPar++;
        }
        else {
          tablicaNieparzysta[jNpar] = produkty[i];
          jNpar++;  
        }
      }
      
    };

    void tajnyAlgorytm()
    //W tym algorytmie bedziemy zapełniać tablice wyników.
    {
      long long indeksNpar, indeksPar;
      indeksNpar = nieparzyste - 1;
      indeksPar = parzyste - 1;
      if (indeksNpar > -1) {
        wyniki[0] = tablicaNieparzysta[indeksNpar];
        indeksNpar--;
        
      }
      else {
        wyniki[0] = -1;
      }
      //Musimy wpisać każdy wynik do tablicy, dla każdego dnia.
      for (long long i=1; i < iloscProduktow; i++)
      {
        //cout<<indeksNpar<<" "<<indeksPar<<" "<<wyniki[i-1]<<endl;

        if (i % 2 == 0) {    
          if ((i > 1)&&(wyniki[i-2] == -1)) {
            wyniki[i] = -1;
          }
          if ((indeksNpar > 0)&&(indeksPar > 0)) {
            if ((tablicaNieparzysta[indeksNpar]+tablicaNieparzysta[indeksNpar-1]) > (tablicaParzysta[indeksPar] + tablicaParzysta[indeksPar-1])) {
              wyniki[i] = wyniki[i-2] + (tablicaNieparzysta[indeksNpar]+tablicaNieparzysta[indeksNpar-1]);
              indeksNpar -= 2;
            }
            else {
              wyniki[i] = wyniki[i-2] + (tablicaParzysta[indeksPar] + tablicaParzysta[indeksPar-1]);
              indeksPar -= 2;
            }
          }
          else if (indeksNpar > 0) {
            wyniki[i] = wyniki[i-2] + (tablicaNieparzysta[indeksNpar]+tablicaNieparzysta[indeksNpar-1]);
            indeksNpar -= 2;
          }
          else if (indeksPar > 0) {
            wyniki[i] = wyniki [i-2] + (tablicaParzysta[indeksPar] + tablicaParzysta[indeksPar-1]);
            indeksPar -= 2;
          }
          else {
            wyniki[i] = -1;
          } 
        }
        else {
          if (wyniki[i-1] == -1) {
            wyniki[i] = -1;
          }
          else if (indeksPar > -1) {
            wyniki[i] = wyniki[i-1] + tablicaParzysta[indeksPar];
          } 
          else {
            wyniki[i] = -1;
          }
        }
      }
        
       
    };

    void wypisz()
    {
     /*for (long long i = 0; i < parzyste; i++)
      {
        cout<<tablicaParzysta[i]<<" ";
      }
      cout<<endl;
      for (long long i = 0; i < nieparzyste; i++)
      {
        cout<<tablicaNieparzysta[i]<<" ";
      }
      cout<<endl;
      for (long long i = 0; i < iloscProduktow; i++)
      {
        cout<<wyniki[i]<<" ";
      }
      cout<<endl;*/
     
      for (long long i = 0; i < liczbaDni; i++)
      {
        if (dni[i] >= iloscProduktow){
          cout<<-1<<endl;        
        }
        else {
          cout<<wyniki[dni[i] - 1]<<endl;
        }
      }
      
    };
  
};




int main()
{
  Bazarek baz;
  baz.wejscie();
  baz.wczytajDoTablic();
  baz.tajnyAlgorytm();
  baz.wypisz();
   
  return 0;

}
