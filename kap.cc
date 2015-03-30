#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>

#define MIN(a, b) ((a < b) ? a : b)
#define PLUS(a) (((a) >= 0) ? (a) : -(a))
// N - number of nodes, x,y - coordinates.
long long n, x, y;

std::vector<std::pair<long long, long long>> XCoordinates, YCoordinates, islands;
std::vector<std::vector<long long>> neighbours;

void readInput ()
{
	scanf ("%lld", &n);
	XCoordinates.resize (n + 1);
	YCoordinates.resize (n + 1);
	islands.resize (n + 1);
	neighbours.resize (n + 1);
	for (long long i = 1; i <= n; i++)
	{
		scanf ("%lld %lld", &x, &y);
		XCoordinates[i] = std::make_pair (x, i);
		YCoordinates[i] = std::make_pair (y, i);
		islands[i] = std::make_pair (x, y);
	}
}

void fillNeighbours ()
{
	std::sort (XCoordinates.begin (), XCoordinates.end ());
	std::sort (YCoordinates.begin (), YCoordinates.end ());
	for (long long i = 1; i <= n; i++)
	{
		// If not last.
		if (i != n )
		{
			neighbours[XCoordinates[i].second].push_back (XCoordinates[i + 1].second);
			neighbours[YCoordinates[i].second].push_back (YCoordinates[i + 1].second);
		}
		// If not first.
		if (i != 1 )
		{
			neighbours[XCoordinates[i].second].push_back (XCoordinates[i - 1].second);
			neighbours[YCoordinates[i].second].push_back (YCoordinates[i - 1].second);
		}
	}
}

// Just some dijkstra stuff.
void doMagic ()
{
	std::set<std::pair<long long, long long>> S;
	std::vector<long long> len (n + 1, -1);
	S.insert (std::make_pair (0, 1));
	len[1] = 0;
	std::pair<long long, long long> result, next;
	bool stop = false;
	do
	{
		auto it1 = S.begin ();
		result = *it1;
		S.erase (it1);
		if (result.second == n)
			stop = true;
		else
		{
			for (auto neighbour : neighbours[result.second])
			{
				long long xx = PLUS (islands[neighbour].first - islands[result.second].first);
				long long yy = PLUS (islands[neighbour].second - islands[result.second].second);
				long long w = MIN (xx, yy);
				w = w + result.first;
				if (len[neighbour] == -1)
				{
					len[neighbour] = w;
					S.insert (std::make_pair (w, neighbour));
				}
				else if (len[neighbour] > w)
				{
					auto it2 = S.find (std::make_pair (len[neighbour], neighbour));
					len[neighbour] = w;
					next = *it2;
					S.erase (it2);
					next.first = w;
					S.insert (next);
				}
				len[result.second] = 0;
			}
		}
	} while (!stop);
	printf("%lld\n", result.first);
}

int main ()
{
	readInput ();
	fillNeighbours ();
	doMagic ();
}
