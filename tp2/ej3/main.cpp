#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <iomanip>


using namespace std;
//clase de kruskal pero cambio todos los int a ll por las dudas y como escribe los for porque se me rompia
using ll = long long;
typedef tuple<ll, ll> Arista;

struct DSU_sin_optimizar {
    DSU_sin_optimizar(ll n) {
        padre = vector<ll>(n);
        arboles = n;
        for (ll v = 0; v < n; v++) padre[v] = v;
    }

    ll find_sin_optimizar(ll v) {
        if (v == padre[v]) return v;
        return find_sin_optimizar(padre[v]);
    }

    void unite_sin_optimizar(ll u, ll v) {
        u = find_sin_optimizar(u), v = find_sin_optimizar(v);
        if (u == v) return;
        padre[v] = padre[u];
        arboles--;
    }

    vector<ll> padre;
    ll arboles;
};



struct DSU {
    DSU(ll n) {
        padre = rank = vector<ll>(n);
        arboles = n; //agrego esto por los modems
        for(ll v = 0; v < n; v++) padre[v] = v;
    }

    ll find(ll v) {
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(ll u, ll v) {
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
        arboles--; //aca tambien

    }

    vector<ll> padre;
    vector<ll> rank;
    ll arboles; //y aca
};

void kruskal(vector<tuple<double, ll, ll, bool>>& E, ll n, ll w, vector<tuple<double, ll, ll, bool>>& agm) { //los paso por parametro porque se rompe todo
    sort(E.begin(), E.end());
    ll res = 0;
    ll aristas = 0;
    DSU dsu(n);
    for (ll i = 0; i < E.size(); i++) { // for(auto [c,u,v] : E) se rompia
        double c = get<0>(E[i]);
        ll u = get<1>(E[i]);
        ll v = get<2>(E[i]);
        bool esUTP = get<3>(E[i]);
        // si (u,v) es arista segura
        if (dsu.find(u) != dsu.find(v)) {
            if (dsu.arboles == w)  // Verificar si ya se formaron W árboles
                break;
            // agregar
            dsu.unite(u, v);
            aristas++;
            res += c;
            agm.push_back(make_tuple(c, u, v, esUTP)); // guardar arista del AGM (no esta en la clase)
        }
    }
    /*
    if (aristas == n - 1)
        cout << res << endl;
    else
        cout << "IMPOSSIBLE\n";
        */
}

//hasta aca

double distancia(const tuple<double, double>& oficina1, const tuple<double, double>& oficina2) {
    double dx = get<0>(oficina1) - get<0>(oficina2);
    double dy = get<1>(oficina1) - get<1>(oficina2);
    return sqrt(dx * dx + dy * dy);
}

void separarAristas(const vector<tuple<double, ll, ll, bool>>& agm, vector<tuple<double, ll, ll>>& aristasUTP, vector<tuple<double, ll, ll>>& aristasfibra) {
    for (ll i = 0; i < agm.size(); i++) {
        double peso = get<0>(agm[i]);
        ll u = get<1>(agm[i]);
        ll v = get<2>(agm[i]);
        bool esUTP = get<3>(agm[i]);
        if (esUTP) {
            aristasUTP.push_back(make_tuple(peso, u, v));
        } else {
            aristasfibra.push_back(make_tuple(peso, u, v));
        }
    }
}



int main() {
    ll K;
    cin >> K;
    ll caso=0;

    while (caso<K) {
        ll N;
        double R;
        ll W;
        ll UTP;
        ll fibra;
        cin >> N >> R >> W >> UTP >> fibra;
        vector<tuple<double, double>> coords;
        for (ll i = 0; i < N; i++) {
            double a;
            double b;
            cin >> a >> b;
            coords.push_back(make_tuple(a, b));
        }
        //creo el grafo
        vector<tuple<double, ll, ll, bool>> E;
        for (ll i = 0; i < N; i++) {
            for (ll j = i + 1; j < N; j++) {
                double dist = distancia(coords[i], coords[j]);
                double peso;
                bool esUTP;
                if (dist <= R) {
                    peso = (UTP * dist); //redondeo para arriba porque el peso es long long
                    esUTP = true;
                } else {
                    peso = (fibra * dist);
                    esUTP = false;
                }
                E.push_back(make_tuple(peso, i, j, esUTP)); //estructura de la clase de kruskal modificada
            }
        }

        vector<tuple<double, ll, ll, bool>> agm;
        kruskal(E, N, W, agm);
        vector<tuple<double, ll, ll>> aristasUTP;
        vector<tuple<double, ll, ll>> aristasfibra;
        separarAristas(agm, aristasUTP, aristasfibra);
        double precioUTP=0;
        double preciofibra=0;

        for(ll i=0; i<aristasUTP.size();i++){
            precioUTP += get<0>(aristasUTP[i]);
        }
        for(ll i=0; i<aristasfibra.size();i++){
            preciofibra += get<0>(aristasfibra[i]);
        }
        cout<< "Caso #" <<caso+1<<": ";
        cout << fixed << setprecision(3) << precioUTP << endl;
        cout << fixed << setprecision(3) << preciofibra << endl;
        caso++;
    }

    return 0;
}


/*

 3 1 1 1 1
 0 0
 0 1
 1 0

6 1 3 2 3
0 0
0 2
2 0
3 2
2 3
3 3

 */


