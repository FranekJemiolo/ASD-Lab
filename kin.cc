#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;

ll tab[20001];
ll n, k;
ll wynik (ll i,ll j, ll ile)
{
  if (n-j+1 < ile) {
    return 0;
  }
  else {
    if (ile == 0) {
    }
    else {
      if (tab[i] > tab[j]) {
        return (wynik(j,j+1,ile-1)+wynik(i,j+1,ile))%(ll)1e9;
      }
      else {
        return wynik(i,j+1,ile)%(ll)1e9;
      }
    }
  }
}

int main ()
{
  scanf("%lld%lld",&n,&k);
  for (ll i = 0; i < n; i++)
  {
    scanf("%lld",&tab[i]);
  }
  printf("%lld\n",wynik(0,1,k));
}
