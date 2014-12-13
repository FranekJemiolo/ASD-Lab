#include <iostream>
#include <cstdio>
using namespace std;

const int maxTab = 1000003;
long long liczbaProduktow, liczbaDni;
long long cenaProduktu[maxTab], dni[maxTab];
long long sumySufix[maxTab], poprzParz[maxTab], kolejnyParz[maxTab],
          poprzNParz[maxTab], kolejnyNParz[maxTab];



void wejscie()
{
  scanf("%lld", &liczbaProduktow);
  for (long long i = 0; i < liczbaProduktow; i++)
  {
    scanf("%lld", &cenaProduktu[i]);
  }
  scanf("%lld", &liczbaDni);
  for (long long i = 0; i < liczbaDni; i++)
  {
    scanf("%lld", &dni[i]);
  }
}

void obliczSumySufix()
{
  long long suma = 0;
  for (long long i = liczbaProduktow-1; i >= 0; i--)
  {
    suma += cenaProduktu[i];
    sumySufix[i] = suma;
  }
}

void uzupelnijKolejneIPoprzednie()
{
  if (cenaProduktu[0] % 2 == 0) {
    poprzParz[0] = cenaProduktu[0];
    poprzNParz[0] = -1;
  }
  else {
    poprzParz[0] = -1;
    poprzNParz[0] = cenaProduktu[0];
  }
  for (long long i = 1; i < liczbaProduktow; i++)
  {
    if (cenaProduktu[i] % 2 == 0) {
      poprzParz[i] = cenaProduktu[i];
      poprzNParz[i] = poprzNParz[i-1];
    }
    else {
      poprzNParz[i] = cenaProduktu[i];
      poprzParz[i] = poprzParz[i-1];
    }
  }

  if (cenaProduktu[liczbaProduktow-1] % 2 == 0) {
    kolejnyParz[liczbaProduktow-1] = cenaProduktu[liczbaProduktow-1];
    kolejnyNParz[liczbaProduktow-1] = -1;
  }
  else {
    kolejnyParz[liczbaProduktow-1] = -1;
    kolejnyNParz[liczbaProduktow-1] = cenaProduktu[liczbaProduktow-1];
  }
  for (long long i = liczbaProduktow-2; i >= 0; i--)
  {
    if (cenaProduktu[i] % 2 == 0) {
      kolejnyParz[i] = cenaProduktu[i];
      kolejnyNParz[i] = kolejnyNParz[i+1];
    }
    else {
      kolejnyNParz[i] = cenaProduktu[i];
      kolejnyParz[i] = kolejnyParz[i+1];
    }
  }
}

void tajnyAlgorytm()
{
  obliczSumySufix();
  uzupelnijKolejneIPoprzednie();

}

void wyjscie()
{
  for (long long i = 0; i < liczbaDni; i++)
  {
    if (sumySufix[liczbaProduktow - dni[i]] % 2 == 0) {
      if (liczbaProduktow - dni[i] < 1){
        printf("-1\n");
      }
      else {
        long long suma1, suma2;
        suma1 = -1;
        suma2 = -1;
        if ((poprzParz[liczbaProduktow-dni[i]-1] != -1)&&(kolejnyNParz[liczbaProduktow-dni[i]] != -1)) {
          suma1 = sumySufix[liczbaProduktow-dni[i]] - kolejnyNParz[liczbaProduktow-dni[i]] + poprzParz[liczbaProduktow-dni[i]-1];
        }
        if ((kolejnyParz[liczbaProduktow-dni[i]] != -1)&&(poprzNParz[liczbaProduktow-dni[i]-1] != -1)) {
          suma2 = sumySufix[liczbaProduktow-dni[i]] - kolejnyParz[liczbaProduktow-dni[i]] + poprzNParz[liczbaProduktow-dni[i]-1];
        }
        if (suma1 > suma2) {
          printf("%lld\n", suma1);
        }
        else {
          printf("%lld\n", suma2);
        }
      } 
    }
    else {
      printf("%lld\n", sumySufix[liczbaProduktow - dni[i]]);
    }
  }
}

void wyjscieDebug()
{
  for (long long i = 0; i < liczbaProduktow; i++)
  {
    printf("%lld ", sumySufix[i]);
  }
  printf("\n");
  for (long long i = 0; i < liczbaProduktow; i++)
  {
    printf("%lld ", kolejnyParz[i]);
  }
  printf("\n");
  for (long long i = 0; i < liczbaProduktow; i++)
  {
    printf("%lld ", kolejnyNParz[i]);
  }
  printf("\n");
  for (long long i = 0; i < liczbaProduktow; i++)
  {
    printf("%lld ", poprzParz[i]);
  }
  printf("\n");
  for (long long i = 0; i < liczbaProduktow; i++)
  {
    printf("%lld ", poprzNParz[i]);
  }
  printf("\n");

}



int main ()
{
  wejscie();
  tajnyAlgorytm();
  wyjscie();
  //wyjscieDebug();
}
