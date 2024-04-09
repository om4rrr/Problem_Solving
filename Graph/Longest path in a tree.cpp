int n;
vector<vector<int>>adj;
vector<bool>vis;
vector<int>depth;

void dfs(int u){
    vis[u] = true;
    for(auto v : adj[u]){
        if(!vis[v]){
            depth[v] = 1 + depth[u];
            dfs(v);
        }
    }
}

void solve(int t) {
    cin >> n;
    adj.resize(n + 1), vis.resize(n + 1), depth.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    int max = *max_element(all(depth));
    for (int i = 1; i <= n; ++i) {
        if(depth[i] == max){
            max = i;
            break;
        }
    }
    vis.clear(), depth.clear();
    vis.resize(n + 1), depth.resize(n + 1);
    dfs(max);
    cout <<  *max_element(all(depth))  << '\n';
}