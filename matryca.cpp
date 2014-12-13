#include <iostream>
#include <new>
#include <string>

using namespace std;

class Matryca
{
  string tapeta;
  long long wynik;
  
  public :
    void wejscie()
    {
      cin>>tapeta;
    };

    void tajnyAlgorytm()
    {
      wynik = tapeta.length();
      bool daSie, stop;
      //string matryca;
      stop = false;
      long long k = 1;
      while (!stop)
      {
        if(((tapeta[k]==tapeta[0])&&((tapeta[k] == tapeta[tapeta.length()-1])||(tapeta[tapeta.length()-1] == '*')))||(tapeta[k]=='*')) {
          k++;
        }
        else {
          stop = true;
        }
      }
      wynik = tapeta.length()-k+1;

    };

    void wypisz()
    {
      cout<<wynik<<endl;
    };
  


};

int main() {
  Matryca mat;
  mat.wejscie();
  mat.tajnyAlgorytm();
  mat.wypisz();
}
