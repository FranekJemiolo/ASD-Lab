#include <iostream>
#include <cstdio>
#include <algorithm>
#define lnums 3
#define i001 1
#define i010 2
#define i100 4
#define i110 6
#define i111 7
#define i101 5
#define i011 3
#define i000 0
#define maxRes(a,b,c) (a = max (a, b+c));
using namespace std;
static const int maxSize = 5003;
//1 - oznacza które sciezki rezerwowane na przejscie a 0 oznacza z ktorych mozna 
//brac sume.



int n,k;
int riches[maxSize][lnums];

int result[2][maxSize][lnums][lnums];

int retMask (int l1, int l2)
{
    if (l1 == 0) {
        if (l2 == 0) {
            return i001;
        }
        else if (l2 == 1) {
            return i011;
        }
        else if (l2 == 2) {
            return i111;
        }
    }
    else if (l1 == 1) {
        if (l2 == 0) {
            return i011;
        }
        else if (l2 == 1) {
            return i010;
        }
        else if (l2 == 2) {
            return i110;
        }
    }
    else if (l1 == 2) {
        if (l2 == 0) {
            return i111;
        }
        else if (l2 == 1) {
            return i110;
        }
        else if (l2 == 2) {
            return i100;
        }
    }
    return i111;
}

int retAdded (int line, int mask, int count) 
{
    if ((count < 1)||(mask == i111))
        return 0;
    else if (count == 1) {
        if (mask == i001) {
            return max (riches[line][2], riches[line][1]);
        }
        else if (mask == i010) {
            return max (riches[line][2], riches[line][0]);
        }
        else if (mask == i100) {
            return max (riches[line][1], riches[line][0]);
        }
        else if (mask == i011) {
            return riches[line][2];
        }
        else if (mask == i110) {
            return riches[line][0];
        }
    }
    else if (count >= 2) {
        if (mask == i001) {
            return (riches[line][2]+riches[line][1]);
        }
        else if (mask == i010) {
            return (riches[line][2]+riches[line][0]);
        }
        else if (mask == i100) {
            return (riches[line][1]+riches[line][0]);
        }
        else if (mask == i011) {
            return riches[line][2];
        }
        else if (mask == i110) {
            return riches[line][0];
        }
    }
}

void fill (int y)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < y+1; j++)
        {
            for (int l = 0; l < lnums; l++)
            {
                for (int z = 0; z < lnums; z++)
                {
                    result[i][j][l][z] = 0;
                }
            }
        }
    }
    
}

int retPrev (int i, int j, int m)
{
    if (i > 0)
        return max (result[(i-1)%2][j][0][m], max (result[(i-1)%2][j][1][m], result[(i-1)%2][j][2][m]));
    else
        return 0;
}

void setFirst (int i)
{
    int mask;
    for (int m = 0; m <= k; m++)
    {
        for (int j = 0; j < lnums; j++)
        {
            mask = retMask (i,j);
            maxRes (result[0][m][i][j],0, retAdded (0, mask, m))
        }
        
        //result[0][m][i][i] = retAdded (0, mask, m);
    }
}

void calc ()
{
    int mask;
    int prev;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            for (int m = 0; m < lnums; m++)
            {
                for (int l = 0; l < lnums; l++)
                {
                    prev = retPrev (i,j,m);
                    mask = retMask (m, l);
                    for (int v = 0; v < lnums; v++)
                    {
                        maxRes(result[i%2][j+v][m][l],prev,retAdded(i,mask,v));
                    }
                }
            }
        }
    }
}

void writeAll ()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            cout<<"i ="<<i<<" j ="<<j<<endl;
            for (int l = 0; l < lnums; l++)
            {
                for (int z = 0; z < lnums; z++)
                {
                    cout<<result[i][j][l][z]<<" ";
                }
            }
            cout<<endl;
        }
    }
}

int returnMax ()
{
    int biggest = 0;
    int x = (n-1)%2;
    //setFirst(0);
    //setFirst(1);
    //setFirst(2);
    for (int j = 0; j < lnums; j++)
    {
        fill (k+1);
        setFirst (j);
        calc ();
        //writeAll ();
        //for (int m = 0; m <= k; m++)
        //{
            for (int i = 0; i < lnums; i++)
            {
                if (result[x][k][i][j] > biggest)
                    biggest = result[x][k][i][j];
            }
        //}

    }

    return biggest;
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
    //fill (k+1);
    //calc ();
    printf ("%d\n", returnMax ());
}
