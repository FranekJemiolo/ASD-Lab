#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 1001;

int W [N] [N] [2];
int t [N];
int ile;

int wynik (int i, int j, int k)
{
  int &w = W[i][j][k];
  if (w != -1) return w;
  if (i == j) return w;
  w = 0;
  int dl = j-i;
  if ((t[i] < t[i+1])&&(k == 0)) {
    w += wynik (i+1, j, 0);
    w %= (int)1e9;
  }
  if (dl >1)
  {
    if ((t[i] < t[j])&&(k == 0))  {
      w += wynik (i+1, j, 1);
      w %= (int)1e9;
    }
  }
    if ((t[i] < t[j])&&(k == 1))  {
      w += wynik (i, j-1, 0);
      w %= (int)1e9;
    }
  if (dl >1)
  {
    if ((t[j] > t[j-1])&&(k == 1))  {
      w += wynik (i, j-1, 1);
      w %= (int)1e9;
    }  
  }
  return w%= (int)1e9;
    
};


void wejscie ()
{
  scanf("%d", &ile);
  for (int i = 0; i < ile; i++)
  {
    scanf("%d", &t[i]);
  }
}

void uzupelnij ()
{
  for (int i = 0; i < ile; i++)
  {
    for (int j = 0; j < ile; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        if (i == j) {
          W[i][j][k] = 1;
        }
        else {
          W[i][j][k] = -1;
        }
      }
    }
  }
};

void wypisz ()
{
  for (int i = 0; i < ile; i++)
  {
    for (int j = 0; j < ile; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        cout<<W[i][j][k]<<" ";
      }
    }
    cout<<endl;
  }
};


int main ()
{
  wejscie ();
  uzupelnij ();
  if (ile > 1)
  {
    cout<<((wynik (0, ile - 1, 0) + wynik (0, ile - 1, 1))% ((int)1e9))<<endl;  
  }
  else {
    cout<<1<<endl;
  }

}

