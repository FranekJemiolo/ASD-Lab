#include <iostream>
#include <cstdio>
#include <algorithm>
#define lnums 3
#define maxRes(a,b,c) (a = max (a, b+c));
using namespace std;
static const int maxSize = 5003;

int n,k;
int riches[maxSize][lnums];
int result[2][maxSize][lnums][lnums];


int retPrev (int i, int j, int m, int l)
{
    if (i > 0)
        return result[(i-1)%2][j][m][l];
    else
        return 0;
}

void calc ()
{
    int prev;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            for (int m = 0; m < lnums; m++)
            {
                for (int l = 0; l < lnums; l++)
                {
                    prev = retPrev (i,j,m,l);
                    if (i == 0) {
                        if ((l == 0)&&(m == 0)) {
                             maxRes(result[i%2][j][m][0],prev,0); // 0 -> 0 mozna brac 1 i 2
                             maxRes(result[i%2][j+1][m][0],prev,riches[i][1]);
                             maxRes(result[i%2][j+1][m][0],prev,riches[i][2]);
                             maxRes(result[i%2][j+2][m][0],prev,(riches[i][1]+riches[i][2]));
                             maxRes(result[i%2][j][m][1],prev,0); // 0 -> 1 mozna brac 2
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][2]);
                             maxRes(result[i%2][j][m][2],prev,0); // 0 -> 2 nic nie mozna brac
                        }
                        else if ((l == 1)&&(m == 1)) {
                             maxRes(result[i%2][j][m][0],prev,0); // 1 -> 0 mozna brac 2
                             maxRes(result[i%2][j+1][m][0],prev,riches[i][2]);
                             maxRes(result[i%2][j][m][1],prev,0); // 1 -> 1 mozna brac 0 i 2
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][0]);
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][2]);
                             maxRes(result[i%2][j+2][m][1],prev,(riches[i][0]+riches[i][2]));
                             maxRes(result[i%2][j][m][2],prev,0); // 1 -> 2 mozna brac 0
                             maxRes(result[i%2][j+1][m][2],prev,riches[i][0]); 
                        }
                        else if ((l == 2)&&(m == 2)) {
                             maxRes(result[i%2][j][m][2],prev,0); // 2 -> 2 mozna brac 0 i 1
                             maxRes(result[i%2][j+1][m][2],prev,riches[i][0]);
                             maxRes(result[i%2][j+1][m][2],prev,riches[i][1]);
                             maxRes(result[i%2][j+2][m][2],prev,(riches[i][0]+riches[i][1]));
                             maxRes(result[i%2][j][m][1],prev,0); // 2 -> 1 mozna brac 0
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][0]);
                             maxRes(result[i%2][j][m][0],prev,0); // 2 -> 0 nic nie mozna brac
                        }
                    }
                    else if (i < n) {
                        if (l == 0) {
                             maxRes(result[i%2][j][m][0],prev,0); // 0 -> 0 mozna brac 1 i 2
                             maxRes(result[i%2][j+1][m][0],prev,riches[i][1]);
                             maxRes(result[i%2][j+1][m][0],prev,riches[i][2]);
                             maxRes(result[i%2][j+2][m][0],prev,(riches[i][1]+riches[i][2]));
                             maxRes(result[i%2][j][m][1],prev,0); // 0 -> 1 mozna brac 2
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][2]);
                             maxRes(result[i%2][j][m][2],prev,0); // 0 -> 2 nic nie mozna brac
                        }
                        else if (l == 1) {
                             maxRes(result[i%2][j][m][0],prev,0); // 1 -> 0 mozna brac 2
                             maxRes(result[i%2][j+1][m][0],prev,riches[i][2]);
                             maxRes(result[i%2][j][m][1],prev,0); // 1 -> 1 mozna brac 0 i 2
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][0]);
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][2]);
                             maxRes(result[i%2][j+2][m][1],prev,(riches[i][0]+riches[i][2]));
                             maxRes(result[i%2][j][m][2],prev,0); // 1 -> 2 mozna brac 0
                             maxRes(result[i%2][j+1][m][2],prev,riches[i][0]); 
                        }
                        else if (l == 2) {
                             maxRes(result[i%2][j][m][2],prev,0); // 2 -> 2 mozna brac 0 i 1
                             maxRes(result[i%2][j+1][m][2],prev,riches[i][0]);
                             maxRes(result[i%2][j+1][m][2],prev,riches[i][1]);
                             maxRes(result[i%2][j+2][m][2],prev,(riches[i][0]+riches[i][1]));
                             maxRes(result[i%2][j][m][1],prev,0); // 2 -> 1 mozna brac 0
                             maxRes(result[i%2][j+1][m][1],prev,riches[i][0]);
                             maxRes(result[i%2][j][m][0],prev,0); // 2 -> 0 nic nie mozna brac
                        }
                    }
                }
            }
        }
    }
}

int returnMax ()
{
    int biggest = 0;
    int x = (n-1)%2;
    calc ();
    for (int j = 0; j < lnums; j++)
    {
        if (result[x][k][j][j] > biggest)
            biggest = result[x][k][j][j];

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
    printf ("%d\n", returnMax ());
}
