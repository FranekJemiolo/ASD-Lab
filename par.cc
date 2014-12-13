#include <iostream>
#include <cstdio>
#include <new>
#include <algorithm>
#include <math.h>
#include <queue>
#include <assert.h>
#define maxSize 500000

struct Tree
{
    int* left; // left son of a node
    int* right; // right son of a node
    int* parent; // parent of a node
    int* depth; // depth for every node;
    int **links; // array of jumps
    int size;
    int floorSize;
    int** fardown;
    int** farup;
    int** far;
    int i;
    int c_1[2];
    int c_2[2];
    int c_3[2];
    int l;
    int res1;
    int res[2];
    int d1,d2;
    int du,dv;
    /*
    int left[maxSize]; // left son of a node
    int right[maxSize]; // right son of a node
    int parent[maxSize]; // parent of a node
    int depth[maxSize]; // depth for every node;
    int links[18][maxSize]; // array of jumps
    int size;
    int floorSize;
    int fardown[maxSize][2];
    int farup[maxSize][2];
    int far[maxSize][2];
    */
    
    // Constructor.
    Tree (int treeSize)
    {
        size = treeSize+1;
        left = new int[size];
        right = new int[size];
        parent = new int[size];
        depth = new int[size];
        fardown = new int*[size];
        farup = new int*[size];
        //far = new int*[size];
        for (i = 1; i < size; i++)
        {
            fardown[i] = new int[2];
            farup[i] = new int[2];
            //far[i] = new int[2];
        }
        
        
        floorSize = floor (log2 (size));
        links = new int*[floorSize+1];
        for (i = 0; i <= floorSize; i++)
        {
            links[i] = new int[size];
        }
    }
    
    // Reading input of a tree, for i-th node it's left and right node.
    void readTree ()
    {
        parent[1] = -1;
        for (i = 1; i < size; i++)
        {
            scanf ("%d %d", &left[i], &right[i]);
            if (left[i] > 0)
                (parent[left[i]] = i);
            if (right[i] > 0)
                (parent[right[i]] = i);
            
        }
    }
    
    // For every node counting it's depth using BFS.
    void setDepth ()
    {
        std::queue<int> qi;
        qi.push(1);
        i = 1;
        while (!qi.empty())
        {
            i = qi.front();
            qi.pop();
            depth[i] = depth[parent[i]]+1;
            if (left[i] > 0)
                qi.push(left[i]);
            if (right[i] > 0)
                qi.push(right[i]);
        }
        
    }
    
    /*void setDepth (int u, int h)
    {
        if (u > 0)
        {
            depth[u] = h;
            setDepth (left[u], h+1);
            setDepth (right[u], h+1);
        }
    }*/
    
    // Counting jump links.
    void countLinks ()
    {
        for (i = 0; i <= floorSize; i++)
        {
            for (int v = 1; v < size; v++)
            {
                if (i == 0)
                {
                    links[i][v] = parent[v];
                }
                else
                {
                    links[i][v] = (links[i-1][v] != -1 ? links[i-1][links[i-1][v]] : -1);
                }
            }
        }
    }
    
    // Returns ancestor h-far from v.
    int ancestor (int v, int h)
    {
        res1 = v;
        i = floorSize;
        while (h > 0)
        {
            if (pow(2,i) > h)
                i--;
            else
            {
                res1 = links[i][res1];
                h = h - pow(2,i);
            }
        }
        return res1;
    }
    
    // Returns lowest common ancestor.
    int lca (int u, int v)
    {
        du = depth[u];
        dv = depth[v];
        if (du < dv)
        {
            v = ancestor (v, dv-du);
            dv = depth[v];
        }
        else if (du > dv)
        {
            u = ancestor (u, du-dv);
            du = depth[u];
        }
        //assert (du==dv);
        if (u==v)
            return u;
        i = floorSize;
        
        while (i >= 0)
        {
            if (links[i][u] != links[i][v])
            {
                u = links[i][u];
                v = links[i][v];
            }
            i--;
        }
        return parent[u];
    }
    
    // Counting farthest node down from node u.
    void countFardown (int u)
    {
        if (left[u] > 0)
            countFardown(left[u]);
        if (right[u] > 0)
            countFardown(right[u]);
        c_1[0] = 0;
        c_1[1] = u;
        if (left[u] > 0)
        {
            c_2[0] = fardown[left[u]][0]+1;
            c_2[1] = fardown[left[u]][1];
        }
        else
        {
            c_2[0] = -1;
            c_2[1] = -1;
        }
        
        if (right[u] > 0)
        {
            c_3[0] = fardown[right[u]][0]+1;
            c_3[1] = fardown[right[u]][1];
        }
        else
        {
            c_3[0] = -1;
            c_3[1] = -1;
        }
        fardown[u][0] = ((c_1[0] < c_2[0]) ? ((c_2[0] < c_3[0]) ? c_3[0] : c_2[0])
            : ((c_1[0] < c_3[0]) ? c_3[0] : c_1[0]));
        fardown[u][1] = ((c_1[0] == fardown[u][0]) ? c_1[1] : (c_2[0] == fardown[u][0] ? c_2[1] : c_3[1]));       
    }
    
    // Counting farthest node down from node u.
    
    void countFarup (int u)
    {
        c_1[0] = 0;
        c_1[1] = u;
        if (parent[u] > 0)
        {
            c_2[0] = farup[parent[u]][0]+1;
            c_2[1] = farup[parent[u]][1];
        }
        else
        {
            c_2[0] = -1;
            c_2[1] = -1;
        }
        
        if (parent[u] > 0)
        {
            if ((left[parent[u]] == u ? right[parent[u]] : left[parent[u]]) > 0)
            {
                c_3[0] = fardown[(left[parent[u]] == u ? right[parent[u]] : left[parent[u]])][0]+2;
                c_3[1] = fardown[(left[parent[u]] == u ? right[parent[u]] : left[parent[u]])][1];
            }
            else
            {
                c_3[0] = -1;
                c_3[1] = -1;
            }
        }
        else
        {
            c_3[0] = -1;
            c_3[1] = -1;
        }
        farup[u][0] = ((c_1[0] < c_2[0]) ? ((c_2[0] < c_3[0]) ? c_3[0] : c_2[0])
            : ((c_1[0] < c_3[0]) ? c_3[0] : c_1[0]));
        farup[u][1] = ((c_1[0] == farup[u][0]) ? c_1[1] : (c_2[0] == farup[u][0] ? c_2[1] : c_3[1]));
        if (left[u] > 0)
            countFarup(left[u]);
        if (right[u] > 0)
            countFarup(right[u]);       
    }
    
    void countFar ()
    {

        if (size > 1)
            countFardown (1);
        if (size > 1)
            countFarup (1);
        /*for (int i = 1; i < size; i++)
        {
            far[i][0] = (fardown[i][0] > farup[i][0] ? fardown[i][0] : farup[i][0]);
            far[i][1] = (fardown[i][0] > farup[i][0] ? fardown[i][1] : farup[i][1]);
        }*/
    }
    
    int dist (int u, int d)
    {
        res[0] = (fardown[u][0] > farup[u][0] ? fardown[u][0] : farup[u][0]);//far[u][0];
        res[1] = (fardown[u][0] > farup[u][0] ? fardown[u][1] : farup[u][1]);//far[u][1];
        if (d > res[0])
            return -1;
        l = lca (u, res[1]);
        d1 = depth[u] - depth[l];
        d2 = depth[res[1]] - depth[l];
        if (d <= d1)
            return ancestor (u, d);
        else
            return ancestor (res[1], res[0]-d);
    }
    
};







int main ()
{
    int treeCount;
    int treeQueries;
    scanf ("%d", &treeCount);
    Tree tree (treeCount);
    tree.readTree ();
    tree.setDepth ();
    tree.countLinks ();
    tree.countFar ();
    

    scanf ("%d", &treeQueries);
    int a, b;
    
    for (int i = 0; i < treeQueries; i++)
    {
        scanf ("%d %d", &a, &b);
        printf ("%d\n", tree.dist(a, b));
    }
}
 
