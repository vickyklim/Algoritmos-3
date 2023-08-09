#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
using namespace std;


void dfs1(long long v, vector<bool>& nodosVisitados, stack<long long>& Stack, vector<vector<long long>>& adj){
    nodosVisitados[v] = true;
    for (long long i = 0; i < adj[v].size(); ++i)
        if (!nodosVisitados[adj[v][i]])
            dfs1(adj[v][i], nodosVisitados, Stack, adj);
    Stack.push(v);
}

void dfs2(long long v, vector<bool>& nodosVisitados, vector<vector<long long>>& adjT, vector<long long>& componente){
    nodosVisitados[v] = true;
    componente.push_back(v);
    for (long long i = 0; i < adjT[v].size(); ++i)
        if (!nodosVisitados[adjT[v][i]])
            dfs2(adjT[v][i], nodosVisitados, adjT, componente);
}


vector<vector<long long>> obtenerSCCs(vector<vector<long long>>& adj, vector<vector<long long>>& adjT, long long V){
    stack<long long> Stack;
    vector<bool> nodosVisitados(V, false);

    for (long long i = 0; i < V; i++)
        if (nodosVisitados[i] == false)
            dfs1(i, nodosVisitados, Stack, adj);


    for(int i=0; i<V; i++){
        nodosVisitados[i] = false;
    }

    vector<vector<long long>> SCCs;
    while (Stack.empty() == false)
    {
        long long v = Stack.top();
        Stack.pop();
        if (nodosVisitados[v] == false)
        {
            vector<long long> componente;
            dfs2(v, nodosVisitados, adjT, componente);
            SCCs.push_back(componente);
        }
    }
    return SCCs;
}

vector<long long> calculoGradosEntrada(const vector<vector<long long>>& SCCs, const vector<vector<long long>>& adj) {
    long long numSCCs = SCCs.size();
    vector<long long> gradosCadaUna(numSCCs, 0);

    for (long long i = 0; i < numSCCs; i++) {
        unordered_set<long long> componenteActual;

        for (long long nodo : SCCs[i])
            componenteActual.insert(nodo);

        for (long long nodo : SCCs[i]) {
            for (long long vecino : adj[nodo]) {
                if (!componenteActual.count(vecino)) {
                    gradosCadaUna[i]++;
                    if (gradosCadaUna[i] > 0) {
                        break; // solo me importa si es 0
                    }
                }
            }
            if (gradosCadaUna[i] > 0) {
                break;
            }
        }
    }

    return gradosCadaUna;
}


int main() {
    long long V;
    long long E;
    cin >> V;
    V++;
    vector<long long> nodosEntrada0(V, true);
    vector<vector<long long>> adj(V);
    vector<vector<long long>> adjT(V);
    cin >> E;
    for (long long i = 0; i < E; i++) {
        long long a;
        long long b;
        cin >> a;
        cin >> b;
        adj[a].push_back(b);
        nodosEntrada0[b] = false;
        adjT[b].push_back(a);
    }
// KOSARAJU
    vector<vector<long long>> SCCs = obtenerSCCs(adj, adjT, V);

    // Chequeo las SCC con grado de entrada 0
    vector<long long> gradosDeEntrada = calculoGradosEntrada(SCCs, adjT);

    vector<long long> res;
    //Me quedo con el minimo de los relevantes
    for(long long i=0; i<SCCs.size(); i++){
        if(gradosDeEntrada[i]==0 and SCCs[i]!=vector<long long>{0}){
            long long min = SCCs[i][0];
            for(long long j; j<SCCs[i].size(); j++){
                if(SCCs[i][j]<min){
                    min = SCCs[i][j];
                }
            }
            res.push_back(min);
        }
    }
    sort(res.begin(), res.end());
    cout<< res.size()<< endl;
    for(long long i=0; i<res.size();i++){
        cout<< res[i] << endl;
    }
/*
    for (int i = 0; i < gradosDeEntrada.size(); i++) {
        cout << "SCC " << i << ": " << gradosDeEntrada[i] << endl;
        for(long long j=0; j< SCCs[i].size(); j++){
            cout << SCCs[i][j] << " ";
        }
        cout << "\n";
    }*/
    return 0;
}

/*
 6 6
 1 2
 2 3
 3 1
 4 5
 5 6
 4 6

 8 11
 1 2
 1 3
 2 1
 3 4
 4 3
 5 6
 6 5
 5 3
 7 5
 7 8
 8 7



7 8
1 3
4 1
4 3
4 2
5 6
6 4
6 7
7 5
 */