const long long N = 2e5 + 5, oo = 1e18;
vector<long long> adj[N];
long long dist[N];
long long parent[N];
long long n, m;

void bfs(vector<long long> & srcs)
{
    queue<long long> q;

    for (long long i = 1; i <= n; ++i) dist[i] = oo;
    for(auto & src : srcs)
    {
        dist[src] = 0;
        parent[src] = src;
        q.push(src);
    }

    while (!q.empty())
    {
        long long u = q.front();
        q.pop();

        for(auto v : adj[u])
        {
            if(dist[v] == oo)
            {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}