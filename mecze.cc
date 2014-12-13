#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
//#define DEBUG
#define MAX_MECZY 50
#define MAX_GRACZY 40000
#define vv vector<string>

int M[MAX_MECZY][MAX_GRACZY];
int meczy, graczy;
string gracze[MAX_GRACZY];
vv wekt;

void input ()
{
  scanf("%d%d",&graczy,&meczy);
  for (int i = 0; i < graczy; i++)
  {
    gracze[i] = "";
  }
  for (int i = 0; i < meczy; i++)
  {
    for (int j = 0; j < graczy; j++)
    {
      scanf("%d",&M[i][j]);
      if (j < graczy/2) {
        gracze[M[i][j]-1] += "0";
      }
      else {
        gracze[M[i][j]-1] += "1";
      }
      
    }
  }
}

bool sprawdz ()
{
  bool w = true;
  for (int i = 0; i < graczy; i++)
  {
    wekt.push_back (gracze[i]);
  }
  sort (wekt.begin(), wekt.end());
  for (int i = 1; i < graczy; i++)
  {
    w = ((w) && ((wekt[i] != wekt[i-1])));
  }
  return w;
}

void output (bool b)
{
  if (b) {
    printf ("TAK\n");
  }
  else {
    printf ("NIE\n");
  }
}

int main ()
{
  input();
  output(sprawdz());
}
