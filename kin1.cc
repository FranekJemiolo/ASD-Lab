#include <cstdio>
#include <iostream>
using namespace std;
#define ll long long
const ll maxSize = 100000;
const ll treeBase = 32768; 
const ll treeSize = 2 * treeBase;
const ll modulo = (ll)1e9;
ll input[maxSize];
//ll tab_2[maxSize][10];
ll tree[treeSize];
ll inversions[maxSize];
ll n, k;

void fill (ll a[], ll size, ll val)//, ll ksize)
{
    for (ll i = 0; i < size; i++)
    {
        a[i] = val;
    }
}

void insert (ll wezel, ll val)
{
    wezel += treeBase;
    
    while (wezel > 0)
    {
        tree[wezel] = (tree[wezel] + val) % modulo;
        wezel /= 2;
    }
}

ll getSum (ll i)
{
    i = i + treeBase;
    ll ret = 0;
        while (i > 0)
        {
            //We are left son so we are adding right child of i's father.
            if (i % 2 == 0) {
                ret += tree[i+1];
                ret %= modulo;
            }
            i /= 2;
        }
    return ret;
}

ll sum ()
{
    ll ret = 0;
    for (ll i = 0; i < n; i++)
    {
        ret += inversions[i];
        ret %= modulo;
    }
    return ret;
}


int main ()
{
    scanf ("%lld %lld", &n, &k);
    fill (inversions, n, 1);
    for (ll i = 0; i < n; i++)
    {
        scanf ("%lld", &input[i]);

    }
        for (ll g = 0; g < k-1; g++)
        {
            fill (tree, treeSize, 0);
            for (ll l = 0; l < n; l++)
            {
                insert (input[l], inversions[l]);
                inversions[l] = getSum(input[l]);
            }
        }
    printf ("%lld\n", sum ());
    
}
