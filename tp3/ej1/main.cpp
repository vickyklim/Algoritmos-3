#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

vector<list<pair<long long, long long>>> grafo;

const long long INF = 1e18;

vector<long long> dijkstra(long long desde) {
    long long n = grafo.size();
    vector<long long> dist(n, INF);
    vector<bool> visitado(n, false);
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;

    dist[desde] = 0;
    pq.push(make_pair(0, desde));

    while (!pq.empty()) {
        long long u = pq.top().second;
        long long uDist = pq.top().first;
        pq.pop();

        if (visitado[u]) {
            continue;
        }

        visitado[u] = true;

        for (const auto& neighbor : grafo[u]) {
            long long v = neighbor.first;
            long long peso = neighbor.second;

            // Relajacion
            if (!visitado[v] && dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

vector<long long> dijkstraModificado(long long desde) {
    long long n = grafo.size();
    vector<long long> dist(n, INF);
    vector<bool> visitado(n, false);

    dist[desde] = 0;

    for (long long i = 0; i < n; i++) {
        long long u = -1;
        for (long long j = 0; j < n; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) {
            break;
        }

        visitado[u] = true;

        for (const auto& neighbor : grafo[u]) {
            long long v = neighbor.first;
            long long peso = neighbor.second;

            // Relajación
            if (!visitado[v] && dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }

    return dist;
}


void construirGrafo() {
    long long numCasos;
    cin >> numCasos;

    for (long long caso = 0; caso < numCasos; caso++) {
        long long n, m, k, s, t;
        cin >> n >> m >> k >> s >> t;

        // Reinicializar el grafo para cada caso
        grafo.clear();
        grafo.resize(2*(n + 1));  // El índice 0 no se utiliza

        // Leer calles unidireccionales
        for (long long i = 0; i < m; i++) {
            long long di, ci, li;
            cin >> di >> ci >> li;
            grafo[di].push_back(make_pair(ci, li));
            grafo[di+n+1].push_back(make_pair(ci+n+1, li));
        }

        // Leer calles bidireccionales
        for (long long j = 0; j < k; j++) {
            long long uj, vj, qj;
            cin >> uj >> vj >> qj;
            grafo[uj].push_back(make_pair(vj+n+1, qj));
            //grafo[vj+n+1].push_back(make_pair(uj, qj));
            grafo[vj].push_back(make_pair(uj+n+1, qj));
            //grafo[uj+n+1].push_back(make_pair(vj, qj));
        }

        vector<long long> distancia1 = dijkstra(s);
        vector<long long> distancia2 = dijkstra(s+n+1);
        long long distanciaFinal;
        // caso1: distancia1[t+n+1]==INF y distancia2[t+n+1]==INF -> no hay camino
        // caso2: distancia1[t+n+1]==INF y distancia2[t+n+1]!=INF -> la bidireccional es necesaria para que haya camino
        // caso3: distancia1[t+n+1]!=INF y distancia2[t+n+1]!=INF -> veo si conviene o no usar bidireccionales (tomo el minimo)
        // caso4: distancia1[t+n+1]!=INF y distancia2[t+n+1]==INF -> esto no va a pasar
        if(distancia1[t+n+1] == INF and distancia2[t+n+1] == INF){
            distanciaFinal = -1;
        } else{
            distanciaFinal = min(distancia1[t+n+1],distancia2[t+n+1]);
        }
        cout<< distanciaFinal << "\n" <<endl;
    }
}

int main() {
    construirGrafo();
    return 0;
}