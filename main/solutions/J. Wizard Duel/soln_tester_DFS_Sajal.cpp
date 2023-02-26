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

class Graph
{
private:
    vector < vector < Edge > > edges;
    vector < int > dsu;
    vector < Fraction > fromRoot;
    vector < bool > visited;
    int nodes;

    int FindPar(int u)
    {
        if (dsu[u] == u) return u;
        return dsu[u] = FindPar(dsu[u]);
    }

    bool Connect(int u, int v)
    {
        int parU = FindPar(u), parV = FindPar(v);
        if (parU != parV)
        {
            dsu[parU] = parV;
            return true;
        }
        return false;
    }

    void Dfs(int n)
    {
        if (visited[n]) return;
        visited[n] = 1;
        for (auto edge : edges[n])
        {
            int u = edge.U, v = edge.V, x = edge.X, y = edge.Y;
            assert (u == n);
            fromRoot[v] = fromRoot[n].Multiply(edge.value);
            Dfs(v);
        }
    }

public:
    Graph(int n, vector < Edge > &uniDirectional)
    {
        nodes = n;
        Fraction one(1, 1);
        for (int i = 0 ; i <= n ; i++)
        {
            dsu.push_back(i);
            fromRoot.push_back(one);
        }

        Edge zero(0, 0, 0, 0);
        edges.resize(n+1, vector < Edge >(0, zero));
        visited.resize(n+1, 0);
        assert (visited.size() == n+1);
        assert (edges.size() == n+1);
        for (int i = 0; i <= n ; i++)
        {
            assert(edges[i].size() == 0);
            assert(visited[i] == 0);
        }

        for (auto edge : uniDirectional)
        {
            int u = edge.U, v = edge.V;
            // cout<<"edge: "<<u<<" "<<v<<endl;
            if (Connect(u, v))
            {
                edges[u].push_back(edge);
                edges[v].push_back(edge.Reverse());
            }
        }

        // for (int i = 1; i <= nodes; i++)
        // {
        //     cout<<"Findpar: "<<i<<" "<<FindPar(i)<<endl;
        // }

        for (int i = 1; i <= nodes; i++)
        {
            if (FindPar(i) == i)
            {
                Dfs(i);
            }
        }
    }

    Fraction Calculate(int u, int v)
    {
        Fraction invalid(0,0);
        if (FindPar(u) != FindPar(v)) return invalid;
        return fromRoot[u].Reverse().Multiply(fromRoot[v]);
    }
};

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
        Graph graph(n, edges);
        while (q--)
        {
            int u, v;
            cin>>u>>v;
            Fraction value = graph.Calculate(u, v);
            PrintVerdict(value);
        }
    }
}


int main()
{
    Solve();
}