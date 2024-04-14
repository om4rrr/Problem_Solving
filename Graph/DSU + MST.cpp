struct DSU
{
    int sets = 0;
    vector<int> setParent, setSize;

    void init(int n)
    {
        setParent.resize(n + 1);
        setSize.resize(n + 1);

        for (int i = 1; i <= n; ++i) {
            setParent[i] = i;
            setSize[i] = 1;
        }

        sets = n;
    }

    int findSet(int u)
    {
        if(setParent[u] == u)
            return u;

        return setParent[u] = findSet(setParent[u]);
    }

    bool sameSet(int u, int v)
    {
        return findSet(u) == findSet(v);
    }

    void unionSet(int u, int v)
    {
        int a = findSet(u);
        int b = findSet(v);

        if(a == b)
            return;

        if(setSize[a] > setSize[b])
        {
            setParent[b] = a;
            setSize[a] += setSize[b];
        }
        else
        {
            setParent[a] = b;
            setSize[b] += setSize[a];
        }

        sets--;
    }
};

struct edge
{
    int u, v, cost;
};

vector<edge>edges;

pair<vector<pair<int, int>>, int> MST(vector<edge> & edges, int n) // nodes
{
    sort(edges.begin(), edges.end(), [](edge A, edge B){return A.cost < B.cost;});

    DSU D;
    D.init(n);

    vector<pair<int, int>> MST_edges;
    long long MST_Cost = 0;
    for(auto & [u, v, c] : edges)
    {
        if(!D.sameSet(u, v))
        {
            D.unionSet(u, v);
            MST_edges.push_back({u, v});
            MST_Cost += c;
        }
    }

    return {MST_edges, MST_Cost};
}
