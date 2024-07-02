const long long N = 5000 + 5, M = 5000 + 5, oo = 1e18;
pair<long long, pair<long long, long long>> edges[M];
long long dist[N];
long long parent[N];
long long n, m;
bool negative_cycle = 0;

void bellman(long long src)
{
    for (long long i = 1; i <= n; ++i) dist[i] = oo;
    dist[src] = 0;
    parent[src] = src;

    for (long long i = 1; i <= n ; ++i)
    {
        bool exist = 0;
        for(long long j = 0; j < m; ++j)
        {
            auto [w, edge] = edges[j];
            auto [u, v] = edge;

            if(dist[v] > dist[u] + w)
            {
                if(i == n) negative_cycle = 1;
                dist[v] = dist[u] + w;
                parent[v] = u;
                exist = 1;
            }
        }
        if(!exist) break;
    }
}
