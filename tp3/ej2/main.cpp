#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1000000;

// Usamos la implementación de Edmonds-Karp del siguiente link https://cp-algorithms.com/graph/edmonds_karp.html#ford-fulkerson-method

int n;
int m;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int edmondsKarp(int s, int t) {
    int flow = 0;
    vector<int> parent(n+2);
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    //AGREGAMOS LOS DOS VÉRTICES PARA EL GRAFO DE FLUJO
    while (true) {
        scanf("%d %d", &n, &m);
        if (n==0 && m == 0) break;
        capacity.assign(n + 2, vector<int>(n + 2, 0));
        adj.assign(n + 2,vector<int>());


        for (int i = 0; i < n; i++) {
            int voto;
            scanf("%d", &voto);
            if (voto == 1) { // VOTO PRIM
                adj[0].push_back(i+1);
                capacity[0][i+1]=1;
            } else { //VOTO KRUSKAL
                adj[i+1].push_back(n+1);
                capacity[i+1][n+1]=1;
            }
        }

        //AMISTADES
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
            capacity[u][v] = 1;
            capacity[v][u] = 1;
        }
        printf("%d\n", edmondsKarp(0, n+1));
    }
    return 0;
}

/*
3 3
1 0 0
1 2
1 3
3 2

6 6
1 1 1 0 0 0
1 2
2 3
4 2
3 5
4 5
5 6
0 0
 */
