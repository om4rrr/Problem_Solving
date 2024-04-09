// Don't forget to Check all Connected Components

const int N = 1e6 + 5, OO = 1e18 + 5;

vector<int> adj[N];
int color[N];

int n, m;

bool bfs_bipartite(int start)
{
    queue<int>q;
    q.push(start);
    color[start] = 1;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(auto v : adj[u])
        {
            if(!color[v])
            {
                color[v] = 3 - color[u];
                q.push(v);
            }
            else
            {
                if(color[v] == color[u])
                    return false;
            }
        }
    }
    return true;
}