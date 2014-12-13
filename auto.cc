#include <iostream>
#include <cstdio>
#include <new>
using namespace std;
#define ll long long
static const ll maxSize = 10000000;


typedef struct 
{
    ll l,r;
    ll color;
    ll sum;
    
} node;

typedef struct
{
    node* nodes[maxSize+1];
    ll sizeTree;
    void removeAll ()
    {
        for (ll i = 1; i <= maxSize; i++)
        {
            delete nodes[i];
        }
    }
    void create (ll size)
    {
        this->sizeTree = 2*size;
        createAll (1,1,size);
    }
    void createAll (ll i,ll l, ll r)
    {
        if (l == r) {
            nodes[i] = new node ();
            nodes[i]->sum = 0;
            nodes[i]->l = l;
            nodes[i]->r = r;
            nodes[i]->color = 0;
        }
        else if (l < r) {
            ll s = ((l + r) / 2);
            nodes[i] = new node ();
            nodes[i]->sum = 0;
            nodes[i]->l = l;
            nodes[i]->r = r;
            nodes[i]->color = 0;
            createAll (2*i, l, s);
            createAll ((2*i)+1, s+1, r);
        }
    }
    void expand (ll i)
    {
        nodes[2*i]->color = nodes[i]->color;
        nodes[(2*i)+1]->color = nodes[i]->color;
        if (nodes[i]->color == 1)
        {
            nodes[2*i]->sum = (nodes[2*i]->r - nodes[2*i]->l + 1);
            nodes[(2*i)+1]->sum = (nodes[(2*i)+1]->r - nodes[(2*i)+1]->l + 1);
        }
        else {
            nodes[2*i]->sum = 0;
            nodes[(2*i)+1]->sum = 0;
        }

        nodes[i]->color = 2;
    }
    
    void update (ll i, ll l, ll r, ll new_val)
    {
        if ((l > nodes[i]->r) || (r < nodes[i]->l)) {
            return;
        }
        else if ((l <= nodes[i]->l) && (r >= nodes[i]->r)) {
            nodes[i]->color = new_val;
            if (new_val == 1) {
                nodes[i]->sum = (nodes[i]->r - nodes[i]->l + 1);
            }
            else {
                nodes[i]->sum = 0;
            }
            
        }
        else {
            if (nodes[i]->color < 2) {
                expand (i);
            }
            update (2*i, l, r, new_val);
            update ((2*i)+1, l, r, new_val);
            nodes[i]->sum = nodes[2*i]->sum + nodes[(2*i)+1]->sum;
        }
    }
    
    void updateSum (ll i)
    {
        if (nodes[i] != NULL)
        {
            if (nodes[i]->color == 2) {
                if ((nodes[2*i] != NULL) && (nodes[(2*i)+1] != NULL)) {
                    nodes[i]->sum = nodes[2*i]->sum + nodes[(2*i)+1]->sum; 
                }
            }
            else if (nodes[i]->color == 1) {
                nodes[i]->sum = (nodes[i]->r - nodes[i]->l + 1);
            
            }
            else {
                nodes[i]->sum = 0;
            }

            
        }
    }
    
    ll returnTop ()
    {
        updateSum (1);
        if (nodes[1] != NULL) {
            return nodes[1]->sum;
        }
        return 0;
    }
    void printTree ()
    {
        for (ll i = 1; i <= 2*sizeTree; i++)
        {
            if (nodes[i] != NULL)
                cout<<i<<" ma kolor "<<nodes[i]->color<<" and sum "<<nodes[i]->sum<<" a przedział to "<<nodes[i]->l<<" "<<nodes[i]->r<<endl;
            else
                cout<<"Mamy nulla"<<endl;
        }
        cout<<endl;
    }
} intTree;

int main ()
{
    intTree* t = new intTree ();
    ll len = 0;
    scanf ("%lld", &len);
    ll paints = 0;
    scanf ("%lld", &paints);
    ll l,r;
    char c;
    t->create (len);
    for (ll i = 0; i < paints; i++) 
    {
        scanf ("%lld %lld %c", &l, &r, &c);
        if (c == 'C') {
            //cout<<"C"<<endl;
            t->update (1, l, r, 0);
        }
        else {
            t->update (1, l, r, 1);
        }
        printf ("%lld\n", t->returnTop ());
        //t->printTree ();
    }
    //t->removeAll ();

       
}
