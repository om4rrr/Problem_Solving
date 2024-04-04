bool isCyclic(int u, int p){
    vis[u] = 1;
    for(auto v : adj[u]){
        if (vis[v] && v != p)   return true;
        else if (!vis[v]) {
            if (isCyclic(v, u)) return true;
        }
    }
    return false;
}