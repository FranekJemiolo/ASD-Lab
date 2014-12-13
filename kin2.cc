#include <cstdio>
#include <iostream>
using namespace std;
#define ll long long
const static ll maxSize = 100000;

ll tab[maxSize];
ll tab_2[maxSize][10];

void fill (ll size, ll ksize)
{
    for (ll i = 0; i < size; i++)
    {
        tab_2[i][0] = 1;
        for (ll k = 1; k < ksize; k++)
        {
            tab_2[i][k] = 0;      
        }

    }
}

ll count (ll size, ll ksize)
{
    for (ll i = 0; i < size; i++)
    {
        ll tmp = tab[i];
        for (ll j = 1; j < ksize; j++)
        {
            for (ll k = tmp+1; k <= size; k++)
            {
                tab_2[tmp-1][j] += tab_2[k-1][j-1];
            }
            
        }
    }
    ll ret = 0;
    for (ll i = 0; i < size; i++)
    {
        ret += tab_2[i][ksize-1];
    }
    return ret;
}

int main ()
{
    ll n, k;
    scanf ("%lld %lld", &n, &k);
    for (ll i = 0; i < n; i++)
    {
        scanf ("%lld", &tab[i]);
    }
    fill (n, k);
    printf ("%lld\n", count (n, k));
    
}
