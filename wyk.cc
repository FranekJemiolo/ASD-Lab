#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
static const int maxSize = 5000;
static const int treeSize = 2048;


int n,k;

typedef struct 
{
    int w[3][3];
    int sizeElem[3][3];
    int line; 
} node;

typedef struct 
{
    node* nodes[treeSize];
    int sizeTree;
    
    int getMax (int a, int b, int c)
    {
        return max (max (a, b), c);
    }
   
    void zeroAll (int position)
    {
        while (position > 0)
        {
            if (nodes[position] != NULL)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        nodes[position]->w[i][j] = 0;
                        nodes[position]->line = 0;
                    }
                }
                position /= 2;
            }
            else
            {
                nodes[position] = new node ();    
            }

        }

    }
    
    void createAll (int size)
    {
        sizeTree = size;
        for (int i = 0; i < sizeTree; i++)
        {
            zeroAll (sizeTree + i);
        }
    }
    
    void actualize (int position)
    {
        while (position > 0)
        {
            node* leftnode = nodes[(2*position)];
            node* rightnode = nodes[(2*position) +1];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int sum[3], lsum[3], rsum[3], lelems[3], relems[3], elems[3];
                    lsum[0] = (leftnode->w[i][0]);
                    lsum[1] = (leftnode->w[i][1]);
                    lsum[2] = (leftnode->w[i][2]);
                    rsum[0] = (rightnode->w[0][j]);
                    rsum[1] = (rightnode->w[1][j]);
                    rsum[2] = (rightnode->w[2][j]);
                    sum[0] = (lsum[0] + rsum[0]);
                    sum[1] = (lsum[1] + rsum[1]);
                    sum[2] = (lsum[2] + rsum[2]);
                    lelems[0] = (leftnode->sizeElem[i][0]);
                    lelems[1] = (leftnode->sizeElem[i][1]);
                    lelems[2] = (leftnode->sizeElem[i][2]);
                    relems[0] = (rightnode->sizeElem[0][j]);
                    relems[1] = (rightnode->sizeElem[1][j]);
                    relems[2] = (rightnode->sizeElem[2][j]);
                    
                    elems[0] = (lelems[0] + relems[0]);
                    elems[1] = (lelems[1] + relems[1]);
                    elems[2] = (lelems[2] + relems[2]);
                    int maxSum = getMax (sum[0], sum[1], sum[2]);
                    //nodes[position]->w[i][j] = 
                    if (elems1[0] <= k) {
                        if (sum[0] == maxSum) {
                            nodes[position]->sizeElem[i][j] = elems[0];
                            nodes[position]->w[i][j] = maxSum;
                        }
                            
                    }
                    else if (elems[1] <= k) {
                        if (sum[1] == maxSum) {
                            nodes[position]->sizeElem[i][j] = elems[1];
                            nodes[position]->w[i][j] = maxSum;
                        }
                    }
                    else if (elems[2] <=k) {
                        if (sum[2] == maxSum) {
                            nodes[position]->sizeElem[i][j] = elems[2];
                            nodes[position]->w[i][j] = maxSum;
                        }                   
                    }
                    else {
                        
                    }

                    
                }
            }
            position /= 2;       
        }

    }
    
    void insert (int a[3], int line)
    {
        int position = sizeTree+line;
        int sum = a[0]+a[1]+a[2];
        int sizee = 0;
        int sumw = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if ((i == 0) && (j == 0)) {
                    if (k < 2) {
                        sumw = max (a[1], a[2]);
                        sizee = 1;
                    }
                    else if (k > 1) {
                        sumw = sum - a[0];
                        sizee = 2;
                    }
                    else {
                        sumw = 0;
                        sizee = 0;
                    }       
                }
                else if ((i == 0) && (j == 1)) {
                    if (k < 2) {
                        sumw = a[2];
                        sizee = 1;
                    }
                    else if (k > 1) {
                        sumw = a[2];
                        sizee = 1;
                    }
                    else {
                        sumw = 0;
                        sizee = 0;
                    }
                }
                else if ((i == 0) && (j == 2)) {
                    sumw = 0;
                }
                else if ((i == 1) && (j == 0)) {
                    if (k < 2) {
                        sumw = a[2];
                        sizee = 1;
                    }
                    else if (k > 1) {
                        sumw = a[2];
                        sizee = 1;
                    }
                    else {
                        sumw = 0;
                        sizee = 0;
                    }
                }
                else if ((i == 1) && (j == 1)) {
                    if (k < 2) {
                        sumw = max (a[0], a[2]);
                        sizee = 1;
                    }
                    else if (k > 1) {
                        sumw = sum - a[1];
                        sizee = 2;
                    }
                    else {
                        sumw = 0;
                        sizee = 0;
                    }
                }
                else if ((i == 1) && (j == 2)) {
                    if (k < 2) {
                        sumw = a[0];
                        sizee = 1;
                    }
                    else if (k > 1) {
                        sumw = a[0];
                        sizee = 1;
                    }
                    else {
                        sumw = 0;
                        sizee = 0;
                    }
                }
                else if ((i == 2) && (j == 0)) {
                    sumw = 0;
                }
                else if ((i == 2) && (j == 1)) {
                    if (k < 2) {
                        sumw = a[0];
                        sizee = 1;
                    }
                    else if (k > 1) {
                        sumw = a[0];
                        sizee = 1;
                    }
                    else {
                        sumw = 0;
                        sizee = 0;
                    }
                }
                else if ((i == 2) && (j == 2)) {
                    if (k < 2) {
                        sumw = max (a[0], a[2]);
                        sizee = 1;
                    }
                    else if (k > 1) {
                        sumw = sum - a[1];
                        sizee = 2;
                    }
                    else {
                        sumw = 0;
                        sizee = 0;
                    }
                }
                nodes[position]->w[i][j] = sumw;
                nodes[position]->sizeElem[i][j] = sizee;

            }
        }
        nodes[position]->line = line;
        actualize (position/2);
        
    }
    
    int getSum ()
    {
        int sum1 = ((nodes[1]->w[0][0]));
        int sum2 = ((nodes[1]->w[1][1]));
        int sum3 = ((nodes[1]->w[2][2]));
        int elems1 = ((nodes[1]->sizeElem[0][0]));
        int elems2 = ((nodes[1]->sizeElem[1][1]));
        int elems3 = ((nodes[1]->sizeElem[2][2]));
                    
        int maxSum = getMax (sum1, sum2, sum3);
        if (sum1 == maxSum) {
            if (elems1 <= k) {
                return maxSum;   
            }
            else {
            
            }
                  
        }

        if (sum2 == maxSum) {
            if (elems2 <= k) {
                return maxSum;   
            }
            else {
            
            }
        }

        if (sum3 == maxSum) {
            if (elems3 <= k) {
                return maxSum;   
            }
            else {
            
            }
        
        }

             
    }
} tree;


int main ()
{
    int riches[maxSize][3];
    tree* t = new tree ();
    scanf ("%d %d", &n, &k);
    t->createAll (n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf ("%d", &riches[i][j]);
        }
        t->insert (riches[i], i);
    }
    printf ("Wynik to : %d", t->getSum ());
}
