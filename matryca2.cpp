#include <iostream>
#include <string>
using namespace std;

string tapeta;

void wejscie ()
{
  cin>>tapeta;
}

void tajnyAlgorytm ()
{
  string matryca;
  long long dlugoscmatrycy = 1;
  char poprzedni = tapeta[0];
  char pierwszy = tapeta[0];
  long long takiesame = 0;
  long long roznica = 0;
  long long gwiazdki = 0;
  long long mingw = 0;
  long long ostatnio = 0;
  long long j = 0;
  while (j < tapeta.length()) {
    if (tapeta[j] == '*') {
      j++;
      poprzedni = tapeta[j];
    }
    else break;
  }
  for (long long i = 0; i < tapeta.length(); i++)
  {
    if ((tapeta[i] == poprzedni)&&(tapeta[i] != '*')) {
      if (pierwszy != poprzedni) {
        dlugoscmatrycy = i - gwiazdki + 1;
        pierwszy = tapeta[i];
      }
      takiesame++;
      gwiazdki = 0;
    }
    else if (tapeta[i] == '*') {
      gwiazdki++;
      takiesame++;
    }
    else {
      if (mingw == 0) {
        mingw = gwiazdki;
      }
      if ((mingw > gwiazdki)&&(gwiazdki > 0)) {
        mingw = gwiazdki;
      }
      dlugoscmatrycy = i - mingw + 1;
      gwiazdki = 0;
      poprzedni = tapeta[i];
      takiesame = 0;
    }
    
  }
  if (takiesame == tapeta.length()){
    cout<<1<<endl;
  }
  else {
    cout<<tapeta.length() - mingw<<endl;
  }
  

  
}

void wyjscie ()
{
  string matryca;
  for (long long i = 0; i < tapeta.length(); i++)
  {
    matryca = tapeta.substr(0, i+1);
    cout<<matryca<<endl;
  }
  
}

int main ()
{
  wejscie();
  tajnyAlgorytm();
  //wyjscie();
}
