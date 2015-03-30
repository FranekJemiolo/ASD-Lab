#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int maxSize = 100005;

struct Node
{
    int val;
    int inDeg;
    std::vector<int> neighbours;
};


Node nodes[maxSize];
std::priority_queue<std::pair<int, int>> Q;
int main ()
{
    int n, m, k;
    scanf ("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++)
    {
        scanf ("%d", &nodes[i].val);
    }
    int u,v;
    while (m--)
    // Reading dependencies of vertices in graph.
    {
        scanf ("%d %d", &v, &u);
        u--;
        v--;
        nodes[v].inDeg++;
        nodes[u].neighbours.push_back (v);
    }
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        if (!nodes[i].inDeg)
        {
            Q.push (std::make_pair (-nodes[i].val, i));
        }
    }
    while (k--)
    {
        u = Q.top ().second;
        Q.pop ();
        res = (res > nodes[u].val ? res : nodes[u].val);
        for (int nbs: nodes[u].neighbours)
        {
            --nodes[nbs].inDeg;
            if (!nodes[nbs].inDeg)
            {
                Q.push (std::make_pair (-nodes[nbs].val, nbs));
            }
        }
    }
    printf ("%d\n", res);
}

