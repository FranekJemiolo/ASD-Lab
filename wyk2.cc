#include <iostream>
#include <cstdio>
#include <algorithm>
#define i001 1
#define i010 2
#define i100 4
#define i110 6
#define i111 7
#define i101 5
#define i011 3
#define i000 0
#define max(wyn, liczba) (wyn = max (wyn, pop + liczba));
using namespace std;
static const int maxSize = 10000;



int n,k;
int riches[maxSize][3];

int wynik[maxSize][maxSize][7];

void zapelnij (int x, int y)
{
    for (int i = 0; i < x+1; i++)
    {
        for (int j = 0; j < y+1; j++)
        {
            for (int l = 0; l < 8; l++)
            {
                wynik[i][j][l] = 0;
            }
        }
    }
    
}

int addVec (int mask1, int mask2)
{
    if (mask1 == i000) {
        if (mask2 == i000)
            return i000;
        else if (mask2 == i001)
            return i001;
        else if (mask2 == i010)
            return i010;
        else if (mask2 == i100)
            return i100;
        else if (mask2 == i011)
            return i011;
        else if (mask2 == i101)
            return i101;
        else if (mask2 == i110)
            return i110;
        else if (mask2 == i111)
            return i111;
            
    }
    else if ((mask1 == i001)) {
        if (mask2 == i000)
            return i001;
        else if (mask2 == i001)
            return i001;
        else if (mask2 == i010)
            return i011;
        else if (mask2 == i100)
            return i101;
        else if (mask2 == i011)
            return i011;
        else if (mask2 == i101)
            return i101;
        else if (mask2 == i110)
            return i111;
        else if (mask2 == i111)
            return i111;
            
    }
    else if ((mask1 == i010)) {
        if (mask2 == i000)
            return i010;
        else if (mask2 == i001)
            return i011;
        else if (mask2 == i010)
            return i010;
        else if (mask2 == i100)
            return i110;
        else if (mask2 == i011)
            return i011;
        else if (mask2 == i101)
            return i111;
        else if (mask2 == i110)
            return i110;
        else if (mask2 == i111)
            return i111;
            
    }
        else if ((mask1 == i100)) {
        if (mask2 == i000)
            return i100;
        else if (mask2 == i001)
            return i101;
        else if (mask2 == i010)
            return i110;
        else if (mask2 == i100)
            return i100;
        else if (mask2 == i011)
            return i111;
        else if (mask2 == i101)
            return i101;
        else if (mask2 == i110)
            return i110;
        else if (mask2 == i111)
            return i111;
            
    }
        else if ((mask1 == i011)) {
        if (mask2 == i000)
            return i011;
        else if (mask2 == i001)
            return i011;
        else if (mask2 == i010)
            return i011;
        else if (mask2 == i100)
            return i111;
        else if (mask2 == i011)
            return i011;
        else if (mask2 == i101)
            return i111;
        else if (mask2 == i110)
            return i111;
        else if (mask2 == i111)
            return i111;
            
    }
        else if ((mask1 == i110)) {
        if (mask2 == i000)
            return i110;
        else if (mask2 == i001)
            return i111;
        else if (mask2 == i010)
            return i110;
        else if (mask2 == i100)
            return i110;
        else if (mask2 == i011)
            return i111;
        else if (mask2 == i101)
            return i111;
        else if (mask2 == i110)
            return i110;
        else if (mask2 == i111)
            return i111;
            
    }
        else if ((mask1 == i101)) {
        if (mask2 == i000)
            return i101;
        else if (mask2 == i001)
            return i101;
        else if (mask2 == i010)
            return i111;
        else if (mask2 == i100)
            return i101;
        else if (mask2 == i011)
            return i111;
        else if (mask2 == i101)
            return i101;
        else if (mask2 == i110)
            return i111;
        else if (mask2 == i111)
            return i111;
            
    }
    else
        return i111;
}

bool canPass (int mask1, int mask2)
{
    if ((mask1 == i000)&&(mask2 != i111)) {
        return true;   
    }
    else if ((mask1 == i001)) {
        if ((mask2 != i110)&&(mask2 != i111))
            return true;
        else
            return false;
    }
    else if ((mask1 == i010)) {
        if ((mask2 != i101)&&(mask2 != i111))
            return true;
        else
            return false;
    }
    else if ((mask1 == i100)) {
        if ((mask2 != i011)&&(mask2 != i111))
            return true;
        else
            return false;
    }
    else if ((mask1 == i110)) {
        if ((mask2 == i110)||(mask2 == i100)||(mask2 == i010)||(mask2 == i000))
            return true;
        else
            return false;
    }
    else if ((mask1 == i101)) {
        if ((mask2 == i101)||(mask2 == i100)||(mask2 == i001)||(mask2 == i000))
            return true;
        else
            return false;
    }
    else if ((mask1 == i011)) {
        if ((mask2 == i011)||(mask2 == i010)||(mask2 == i001)||(mask2 == i000))
            return true;
        else
            return false;
    }
    else if (mask2 == i000)
        return true;
    else
        return false;
}

void oblicz (int i, int j, int prev, int act)
{
    
    //if (i > n)
    int pop = 0;
    int l = addVec (prev, act);
    if ((i < n)&&(l != i111))
    {
        //cout<<wynik[i-1][j][l]<<"->";
         
                if (i > 0)
                    pop = wynik[i-1][j][l];
                else 
                    pop = 0;
                if (l == i000)
                {
                    max(wynik[i][j][i000], (0));
                    oblicz (i+1, j, l, i000);
                    max(wynik[i][j+1][i001], (riches[i][0]));
                    oblicz (i+1, j+1, l, i001);
                    max(wynik[i][j+1][i010], (riches[i][1]));
                    oblicz (i+1, j+1, l, i010);
                    max(wynik[i][j+2][i011], (riches[i][1]+riches[i][0]));
                    oblicz (i+1, j+2, l, i011);
                    max(wynik[i][j+1][i100], (riches[i][2]));
                    oblicz (i+1, j+1, l, i100);
                    max(wynik[i][j+2][i101], (riches[i][2]+riches[i][0]));
                    oblicz (i+1, j+2, l, i101);
                    max(wynik[i][j+2][i110], (riches[i][2]+riches[i][1]));
                    oblicz (i+1, j+2, l, i110);
                }
                if (l == i001)
                {
                    max(wynik[i][j][i000], (0));
                    oblicz (i+1, j, l, i000);
                    max(wynik[i][j+1][i001], (riches[i][0]));
                    oblicz (i+1, j+1, l, i001);
                    max(wynik[i][j+1][i010], (riches[i][1]));
                    oblicz (i+1, j+1, l, i010);
                    max(wynik[i][j+2][i011], (riches[i][1]+riches[i][0]));
                    oblicz (i+1, j+2, l, i011);
                    max(wynik[i][j+1][i100], (riches[i][2]));
                    oblicz (i+1, j+1, l, i100);
                    max(wynik[i][j+2][i101], (riches[i][2]+riches[i][0]));
                    oblicz (i+1, j+2, l, i101);
                    
                }
                if (l == i010)
                {
                    max(wynik[i][j][i000], (0));
                    oblicz (i+1, j, l, i000);
                    max(wynik[i][j+1][i001], (riches[i][0]));
                    oblicz (i+1, j+1, l, i001);
                    max(wynik[i][j+1][i010], (riches[i][1]));
                    oblicz (i+1, j+1, l, i010);
                    max(wynik[i][j+2][i011], (riches[i][1]+riches[i][0]));
                    oblicz (i+1, j+2, l, i011);
                    max(wynik[i][j+1][i100], (riches[i][2]));
                    oblicz (i+1, j+1, l, i100);
                    max(wynik[i][j+2][i110], (riches[i][2]+riches[i][1]));
                    oblicz (i+1, j+2, l, i110);
                }
                if (l == i011)
                {
                    max(wynik[i][j][i000], (0));
                    oblicz (i+1, j, l, i000);
                    max(wynik[i][j+1][i001], (riches[i][0]));
                    oblicz (i+1, j+1, l, i001);
                    max(wynik[i][j+1][i010], (riches[i][1]));
                    oblicz (i+1, j+1, l, i010);
                    max(wynik[i][j+2][i011], (riches[i][1]+riches[i][0]));
                    oblicz (i+1, j+2, l, i011);
                    
                }
                if (l == i110)
                {
                    max(wynik[i][j][i000], (0));
                    oblicz (i+1, j, l, i000);
                    max(wynik[i][j+1][i010], (riches[i][1]));
                    oblicz (i+1, j+1, l, i010);
                    max(wynik[i][j+1][i100], (riches[i][2]));
                    oblicz (i+1, j+1, l, i100);
                    max(wynik[i][j+2][i110], (riches[i][2]+riches[i][1]));
                    oblicz (i+1, j+2, l, i110);
                    
                }
                if (l == i100)
                {
                    max(wynik[i][j][i000], (0));
                    oblicz (i+1, j, l, i000);
                    max(wynik[i][j+1][i001], (riches[i][0]));
                    oblicz (i+1, j+1, l, i001);
                    max(wynik[i][j+1][i010], (riches[i][1]));
                    oblicz (i+1, j+1, l, i010);
                    max(wynik[i][j+1][i100], (riches[i][2]));
                    oblicz (i+1, j+1, l, i100);
                    max(wynik[i][j+2][i101], (riches[i][2]+riches[i][0]));
                    oblicz (i+1, j+2, l, i101);
                    max(wynik[i][j+2][i110], (riches[i][2]+riches[i][1]));
                    oblicz (i+1, j+2, l, i110);
                    
                }
                if (l == i101)
                {
                    max(wynik[i][j][i000], (0));
                    oblicz (i+1, j, l, i000);
                    max(wynik[i][j+1][i001], (riches[i][0]));
                    oblicz (i+1, j+1, l, i001);
                    max(wynik[i][j+1][i100], (riches[i][2]));
                    oblicz (i+1, j+1, l, i100);
                    max(wynik[i][j+2][i101], (riches[i][2]+riches[i][0]));
                    oblicz (i+1, j+2, l, i101);
                }

   /* int i = n-1;
    int z = n-1;
            for (int j = 0; j <= k; j++)//k
        {

                if (x == i000)
                {
                    pop = wynik[z-1][j][i110];
                    max(wynik[z][j+2][i110], (riches[i][2]+riches[i][1]));
                    pop = wynik[z-1][j][i011];
                    max(wynik[z][j+2][i011], (riches[i][1]+riches[i][0]));
                    pop = wynik[z-1][j][i101];
                    max(wynik[z][j+2][i101],  (riches[i][2]+riches[i][0]));
                    pop = wynik[z-1][j][i100];
                    max(wynik[z][j+1][i100],  (riches[i][2]));
                    pop = wynik[z-1][j][i000];
                    max(wynik[z][j][i000],  (0));
                    pop = wynik[z-1][j][i010];
                    max(wynik[z][j+1][i010], riches[i][1]);
                    pop = wynik[z-1][j][i001];
                    max(wynik[z][j+1][i001],  riches[i][0]);
                }
                if (x == i001)
                {
                    pop = wynik[z-1][j][i011];
                    max(wynik[z][j+2][i011], (riches[i][1]+riches[i][0]));
                    pop = wynik[z-1][j][i101];
                    max(wynik[z][j+2][i101],  (riches[i][2]+riches[i][0]));
                    pop = wynik[z-1][j][i100];
                    max(wynik[z][j+1][i100],  (riches[i][2]));
                    pop = wynik[z-1][j][i000];
                    max(wynik[z][j][i000],  (0));
                    pop = wynik[z-1][j][i010];
                    max(wynik[z][j+1][i010], riches[i][1]);
                    pop = wynik[z-1][j][i001];
                    max(wynik[z][j+1][i001],  riches[i][0]);
                    
                }
                if (x == i010)
                {
                    pop = wynik[z-1][j][i110];
                    max(wynik[z][j+2][i110], (riches[i][2]+riches[i][1]));
                    pop = wynik[z-1][j][i011];
                    max(wynik[z][j+2][i011], (riches[i][1]+riches[i][0]));
                    pop = wynik[z-1][j][i100];
                    max(wynik[z][j+1][i100],  (riches[i][2]));
                    pop = wynik[z-1][j][i000];
                    max(wynik[z][j][i000],  (0));
                    pop = wynik[z-1][j][i010];
                    max(wynik[z][j+1][i010], riches[i][1]);
                    pop = wynik[z-1][j][i001];
                    max(wynik[z][j+1][i001],  riches[i][0]);
                    
                }
                if (x == i011)
                {
                    pop = wynik[z-1][j][i011];
                    max(wynik[z][j+2][i011], (riches[i][1]+riches[i][0]));
                    pop = wynik[z-1][j][i000];
                    max(wynik[z][j][i000],  (0));
                    pop = wynik[z-1][j][i010];
                    max(wynik[z][j+1][i010], riches[i][1]);
                    pop = wynik[z-1][j][i001];
                    max(wynik[z][j+1][i001],  riches[i][0]);
                    
                }
                if (x == i110)
                {
                    pop = wynik[z-1][j][i110];
                    max(wynik[z][j+2][i110], (riches[i][2]+riches[i][1]));
                    pop = wynik[z-1][j][i100];
                    max(wynik[z][j+1][i100],  (riches[i][2]));
                    pop = wynik[z-1][j][i000];
                    max(wynik[z][j][i000],  (0));
                    pop = wynik[z-1][j][i010];
                    max(wynik[z][j+1][i010], riches[i][1]);
                    
                }
                if (x == i100)
                {
                    pop = wynik[z-1][j][i110];
                    max(wynik[z][j+2][i110], (riches[i][2]+riches[i][1]));
                    pop = wynik[z-1][j][i101];
                    max(wynik[z][j+2][i101],  (riches[i][2]+riches[i][0]));
                    pop = wynik[z-1][j][i100];
                    max(wynik[z][j+1][i100],  (riches[i][2]));
                    pop = wynik[z-1][j][i000];
                    max(wynik[z][j][i000],  (0));
                    pop = wynik[z-1][j][i010];
                    max(wynik[z][j+1][i010], riches[i][1]);
                    pop = wynik[z-1][j][i001];
                    max(wynik[z][j+1][i001],  riches[i][0]);
                    
                }
                if (x == i101)
                {
                    pop = wynik[z-1][j][i101];
                    max(wynik[z][j+2][i101],  (riches[i][2]+riches[i][0]));
                    pop = wynik[z-1][j][i100];
                    max(wynik[z][j+1][i100],  (riches[i][2]));
                    pop = wynik[z-1][j][i000];
                    max(wynik[z][j][i000],  (0));
                    pop = wynik[z-1][j][i001];
                    max(wynik[z][j+1][i001],  riches[i][0]);
                    
                }
            }*/
    }
}

void ustaw (int l)
{
    int pop = 0;
    int j = 0, i = 0;
                if (l == i000)
                {

                    max(wynik[i][j][i000], (0));
                    oblicz(1,0,l,l);

                }
                if (l == i001)
                {

                    max(wynik[i][j+1][i001], (riches[i][0]));
                    oblicz(1,1,l,l);
                    
                }
                if (l == i010)
                {

                    max(wynik[i][j+1][i010], (riches[i][1]));
                    oblicz(1,1,l,l);

                    
                }
                if (l == i011)
                {
                    max(wynik[i][j+2][i011], (riches[i][1]+riches[i][0]));
                    oblicz(1,2,l,l);
                    
                }
                if (l == i110)
                {
                    max(wynik[i][j+2][i110], (riches[i][2]+riches[i][1]));
                    oblicz(1,2,l,l);

                    
                }
                if (l == i100)
                {

                    max(wynik[i][j+1][i100], (riches[i][2]));
                    oblicz(1,1,l,l);

                    
                }
                if (l == i101)
                {
                    max(wynik[i][j+2][i101], (riches[i][2]+riches[i][0]));
                    oblicz(1,2,l,l);

                    
                }
                //oblicz (0, 0, l);
}



void wypisz ()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            cout<<"i = "<<i<<" j = "<<j<<endl;
            for (int l = 0; l < 7; l++)
            {
                cout<<wynik[i][j][l]<<" ";
            }
            cout<<endl;
        }
    }
}

int returnMax ()
{
    int maxim = 0;
    int i  =  n-1 ;
        for (int j = 0; j < 7; j++)
        {
            zapelnij (n,k+2);
            ustaw(j);
            cout<<"Teraz wypisuje "<<j<<endl;
            wypisz ();
            //cout<<"Teraz idzie "<< j<<endl;
            //cout << wynik[i][k][j] << endl;
            for (int l = 0; l < 7; l++)
            {
                //if (canPass(j, l)) {
                    //cout << wynik[i][k][l]<<endl;
                    if (wynik[i][k][l] > maxim)
                        maxim = wynik[i][k][l];
                //}
            }
        }
    return maxim;
}


int main ()
{
    
    scanf ("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf ("%d", &riches[i][j]);
        }
    }
    printf ("%d\n", returnMax ());
}
