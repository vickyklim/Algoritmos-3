#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

long long n;
vector<vector<long long>> adj;

vector<bool> visitados;
vector<long long> tin, low;
long long orden_de_visita;
vector<pair<long long, long long>> puentes;

void dfs(long long v, long long p = -1) {
    visitados[v] = true;
    tin[v] = low[v] = orden_de_visita++;
    for (long long to : adj[v]) {
        //cout<< "padre: " << v << " hijos: " << to << "\n";
        if (to == p) continue;
        if (visitados[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            //cout << "llamo dfs "<< to << " " << v << "\n";
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                puentes.push_back({v, to});

            }
        }
    }
}

void buscador_de_puentes() {
    orden_de_visita = 0;
    vector<long long> t(n,-1);
    vector<long long> l(n,-1);
    tin = t;
    low = l;
    vector<bool> v(n,false);
    visitados = v;
    for (long long i = 0; i < n; ++i) {
        if (!visitados[i])
            dfs(i);
    }

}

vector<bool> visitados_2;
vector<long long> componentes;

void dfs_2(long long v) {
    visitados_2[v] = true;
    componentes.back()++; //modif ultimo elemento

    for (long long u : adj[v]) {
        if (!visitados_2[u]) {
            dfs_2(u);
        }
    }
}

vector<long long> cuantosVerticesHay() {
    visitados_2.assign(n, false);
    componentes.clear();

    for (long long v = 0; v < n; v++) {
        if (!visitados_2[v]) {
            componentes.push_back(0);
            dfs_2(v);
        }
    }

    return componentes;
}

vector<vector<long long>> memo_comb;

long long combinatorio(long long n, long long k) {
    if (k == 0 || k == n) {
        return 1;
    }

    if (memo_comb[n][k] != 0) {
        return memo_comb[n][k];
    }

    memo_comb[n][k] = combinatorio(n - 1, k - 1) + combinatorio(n - 1, k);

    return memo_comb[n][k];
}

void leer_input(){
    long long nodos = 0;
    long long m = 0;
    cin >> nodos >> m;
    n = nodos;
    vector<vector<long long>> ady(n);
    for(long long i = 0; i<m;i++){
        long long a;
        long long b;
        cin>> a >> b;
        ady[a-1].push_back(b-1);
        ady[b-1].push_back(a-1);
    }
    adj = ady;
    vector<bool> v_bools(n,false);
    visitados = v_bools;
    visitados_2 = v_bools;

}


int main() {

    leer_input();
    buscador_de_puentes();

//Eliminamos las aristas puente del grafo orignial.

    /* for (const auto& p : puentes) {
         long long u = p.first;
         long long v = p.second;

         auto it = find(adj[u].begin(), adj[u].end(), v);
         if (it != adj[u].end()) {
             adj[u].erase(it);
         }


         it = find(adj[v].begin(), adj[v].end(), u);
         if (it != adj[v].end()) {
             adj[v].erase(it);
         }
     }
 */


    //for (auto bridge : puentes) {
    //  cout << bridge.first << " " << bridge.second << endl;
    // }
    for (const auto& p : puentes) {
        long long u = p.first;
        long long v = p.second;

        for (int i = 0; i < adj[u].size(); i++) {
            if (adj[u][i] == v) {
                adj[u].erase(adj[u].begin() + i);
                break;
            }
        }

        for (int i = 0; i < adj[v].size(); i++) {
            if (adj[v][i] == u) {
                adj[v].erase(adj[v].begin() + i);
                break;
            }
        }
    }

    vector<long long> tamanio_conexas = cuantosVerticesHay();
    // for(auto x:tamanio_conexas){
    // cout<< x << " ";
    // }



    memo_comb.resize(n + 1, vector<long long>(3, 0));

    long long prob_de_ganar = 0;
    for(long long i = 0;i<tamanio_conexas.size();i++){
        if (2 > tamanio_conexas[i]){
            prob_de_ganar+=0;
        }else{
            prob_de_ganar = prob_de_ganar + combinatorio(tamanio_conexas[i],2);
        }
    }
    double result = static_cast<double>(prob_de_ganar)/ static_cast<double>(combinatorio(n,2));
    cout<<"\n" << fixed << setprecision(5)<< 1.0 - result;

}