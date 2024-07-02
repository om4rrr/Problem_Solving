const long long N = 100 + 5,M = 1e5, oo = 1e18;
pair<long long, pair<long long, long long>> edges[M];
long long dist[N][N];
long long n, m;

void floyd(void)
{
    for (int u = 1; u <= n; ++u)
    {
        for (int v = 1; v <= n; ++v)
        {
            if(u == v) dist[u][v] = 0;
            else dist[u][v] = oo;
        }
    }

    for(long long i = 0; i < m; ++i)
    {
        auto [w, edge] = edges[i];
        auto [u, v] = edge;
        dist[u][v] = min(w,dist[u][v]);
        // if (undirected graph) --> dist[u][v] = dist[v][u] = w;
    }

    for (int k = 1; k <= n; ++k)
    {
        for (int u = 1; u <= n; ++u)
        {
            for (int v = 1; v <= n; ++v)
            {
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
            }
        }
    }
}