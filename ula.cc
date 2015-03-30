#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <algorithm>
#include <set>

static const long long MAX_SIZE = 200005;

struct Node
{
	// The number of the node and it's value.
	long long nr, value;
	// The set that contains out-going. No multi-edges.
	std::set<long long> out;
};

Node graph[MAX_SIZE];
Node graphSCC[MAX_SIZE];

// n - vertices , m - edges.
long long n, m, nscc;

// For tarajanAlg this is actual pointed node.
long long act;
// Array of numbers of vertices.
long long VN[MAX_SIZE] = {1};
// Low parameters array.
long long VLow[MAX_SIZE];
// If node is on stack?
bool VS[MAX_SIZE] = {false};
// The stack of vertices.
std::stack<long long> S;
// Vector holding vectors of vertices that are in the same scc.
std::vector<std::vector<long long> > Lscc;

// In this array we will hold the value that can be reached from this node.
long long VALS[MAX_SIZE] = {0};
long long valuemax = 0;

void CLEARS ()
{
	for (long long i = 0; i < nscc; i++)
	{
		VS[i] = false;
	}
}

void DFS (long long x)
{
	if (!VS[x])
	{
		VS[x] = true;
		if (graphSCC[x].out.size () != 0)
		{
			
			for (auto z : graphSCC[x].out)
			{
				DFS (z);
				VALS[x] = ((VALS[z] + graphSCC[x].value > VALS[x]) ? 
					(VALS[z] + graphSCC[x].value) : VALS[x]);
			}
		}
		else
		{
			VALS[x] = graphSCC[x].value;
		}
		valuemax = VALS[x] > valuemax ? VALS[x] : valuemax;
	}
}


// Using tarajan algorithm we are finding all sccs.
void tarajanAlg (long long v)
{
	// List of vertices.
	std::vector<long long> sccp;
	act++;
	VN[v] = act;
	VLow[v] = act;
	S.push (v);
	VS[v] = true;
	// Every neighbour of node v.
	for (auto u : graph[v].out)
	{
		if (VN[u] != 0)
		{
			if (VS[u] == true)
			{
				VLow[v] = std::min (VLow[v], VN[u]);
			}
		}
		else
		{
			tarajanAlg (u);
			VLow[v] = std::min (VLow[v], VLow[u]);
		}
	}
	long long u;
	if (VLow[v] == VN[v])
	{
		do
		{
			u = S.top ();
			S.pop ();
			VS[u] = false;
			sccp.push_back (u);
		} while (u != v);
		Lscc.push_back (sccp);
	}

}

// Creates new graph with all strongly connected components as one node.
void createSCC ()
{
	act = 1;
	for (long long v = 1; v <= n; v++)
	{
		if (VN[v] == 0)
			tarajanAlg (v);
	}
	long long i = 0;
	for (auto x : Lscc)
	{
		graphSCC[i].value = 0;
		// Setting for new node.
		for (auto y : x)
		{
			graph[y].nr = i;
		}
		i++;
	}
	nscc = i;
	i = 0;
	for (auto x : Lscc)
	{
		graphSCC[i].value = 0;
		// Now gluing nodes.
		for (auto y : x)
		{
			graphSCC[i].value += graph[y].value;
			for (auto z : graph[y].out)
			{
				if (graph[z].nr != i)
					graphSCC[i].out.insert (graph[z].nr);
			}
		}
		i++;
	}
	CLEARS ();
	for (long long x = 0; x < nscc; x++)
	{
		if (!VS[x])
		{
			DFS (x);
		}
	}
	printf("%lld\n", valuemax);

}


int main ()
{
	scanf ("%lld %lld", &n, &m);
	// Reading values.
	for (long long i = 1; i <= n; i++)
	{
		scanf("%lld", &graph[i].value);
	}
	// Reading edges.
	long long x,y;
	for (long long i = 1; i <= m; i++)
	{
		scanf ("%lld %lld", &x, &y);
		graph[x].out.insert(y);
	}
	createSCC ();
}