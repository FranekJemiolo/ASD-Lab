#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string tapeta;

void wejscie ()
{
	cin>>tapeta;
}

//#define DEBUG
void tajnyAlgorytm()
{
  long long matryca = tapeta.length();
  long long pop = 0;
  long long najmniejgwiazdek = 0;
  long long terazGwiazdek = 0;
  for (long long i = 0; i < tapeta.length(); i++)
  {
    if ((tapeta[i] == tapeta[pop])||(tapeta[i] == '*')) {
      
      matryca--;
      #ifdef DEBUG
        cout<<matryca<<" "<<terazGwiazdek<<" "<<najmniejgwiazdek<<endl;
      #endif
      if (tapeta[i] == '*') {
        terazGwiazdek++;
      }
      else {
        if (najmniejgwiazdek == 0){
          najmniejgwiazdek = terazGwiazdek;
        }
        else {
          if (najmniejgwiazdek > terazGwiazdek) {
            najmniejgwiazdek = terazGwiazdek;
          }
        }
        terazGwiazdek = 0;
      }
      
    }
    else {
      if (najmniejgwiazdek == 0){
        najmniejgwiazdek = terazGwiazdek;
      }
      matryca = tapeta.length()-najmniejgwiazdek;
      pop = i;
    }
  }
  if (matryca < 1){
    matryca = 1;
  }
  cout<<matryca<<endl;
}


int main ()
{
	wejscie();
	tajnyAlgorytm();
}
