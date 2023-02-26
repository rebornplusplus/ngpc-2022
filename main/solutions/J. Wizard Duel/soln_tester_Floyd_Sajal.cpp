#include<bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL)
#define LL long long
#define MAX (LL) 4e18
#define MOD 998244353
#define N 5005
#define endl "\n"
using namespace std;
namespace fs = std::filesystem;

class Fraction
{
public:
    LL Up, Down;
    Fraction(LL u, LL d)
    {
        Up = u, Down = d;
    }

    Fraction()
    {
        Up = Down = 0;
    }

    Fraction Reverse()
    {
        Fraction reverse(Down, Up);
        return reverse;
    }

    void Print()
    {
        cout<<Up<<" "<<Down<<endl;
    }

    Fraction Multiply(Fraction b)
    {
        LL up = Up, down = Down;
        LL upG = __gcd(up, b.Down);
        LL downG = __gcd(down, b.Up);
        up /= upG;
        down /= downG;
        assert(up < MAX / (b.Up / downG));
        assert(down < MAX / (b.Down / upG));
        up *= b.Up / downG;
        down *= b.Down / upG;
        LL g = __gcd(up, down);
        assert(g == 1);
        Fraction fraction(up, down);
        return fraction;
    }
};

class Edge
{
public:
    int U, V, X, Y;
    Fraction value;
    Edge(int u, int v, int x, int y)
    {
        U = u, V = v, X = x, Y = y;
        Fraction w(x,y);
        value = w;
    }

    Edge()
    {
        U = V = X = Y = 0;
    }

    Edge Reverse()
    {
        Edge reverseEdge(V, U, Y, X);
        return reverseEdge;
    }
};

vector < vector < Fraction > > Floyd(int n, vector < Edge > &edges)
{
    Fraction invalid(0, 0);
    vector < vector < Fraction > > allPair(n+1, vector < Fraction >(n+1, invalid));
    assert(allPair.size() == n+1);
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n ; j++)
        {
            assert(allPair[i].size() == n+1);
            assert(allPair[i][j].Up == 0 && allPair[i][j].Down == 0);
        }
    }

    for (auto edge : edges)
    {
        int u = edge.U, v = edge.V, x = edge.X, y = edge.Y;
        Fraction forward(x, y);
        Fraction backward = forward.Reverse();
        allPair[u][v] = forward;
        allPair[v][u] = backward;
    }

    for (int k = 1 ; k <= n ; k++)
    {
        for (int i = 1 ; i <= n ; i++)
        {
            for (int j = 1 ; j <= n ; j++)
            {
                if (allPair[i][j].Down == 0 && allPair[i][k].Down != 0 && allPair[k][j].Down != 0)
                {
                    allPair[i][j] = allPair[i][k].Multiply(allPair[k][j]);
                }
            }
        }
    }

    return allPair;
}

void PrintVerdict(Fraction value)
{
    // value.Print();
    if (value.Down == 0)
    {
        cout<<"unknown\n";
    }
    else if (value.Down == value.Up)
    {
        cout<<"draw\n";
    }
    else if (value.Up > value.Down)
    {
        cout<<"win\n";
    }
    else cout<<"lose\n";
}



void Solve()
{
    int t;
    cin>>t;
    while (t--)
    {
        int n, m, q;
        cin>>n>>m>>q;
        vector < Edge > edges;
        while (m--)
        {
            int u, v, x, y;
            cin>>u>>v>>x>>y;
            Edge newEdge(u, v, x, y);
            edges.push_back(newEdge);
        }
        vector < vector < Fraction > > allPair = Floyd(n, edges);
        while (q--)
        {
            int u, v;
            cin>>u>>v;
            PrintVerdict(allPair[u][v]);
        }
    }
}


int main()
{
    Solve();
}