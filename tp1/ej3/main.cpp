#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

vector<tuple<int,int>> actividades;
int n;

vector<vector<tuple<int, tuple<int, int>>>> bucketSort(vector<tuple<int, int>> v) { //(pos, (s,t))
    n = v.size();
    vector<vector<tuple<int, tuple<int, int>>>> buckets(2*n+1);
    for(int i=0; i<v.size(); i++){
        int empieza = get<0>(v[i]);
        int termina = get<1>(v[i]);
        buckets[termina].push_back(make_tuple(i, make_tuple(empieza,termina)));
    }
    vector<vector<tuple<int, tuple<int, int>>>> res;
    for (int bucket = 0; bucket < buckets.size(); bucket++) {
        if (!buckets[bucket].empty()) {
            vector<tuple<int, tuple<int, int>>> subvector;
            for (const auto& e: buckets[bucket]) {
                subvector.push_back(e);
            }
            res.push_back(subvector);
        }
    }
    return res;
}

tuple<int,tuple<int,int>> minimoPosible(vector<tuple<int, tuple<int, int>>> v, int ult){
    tuple<int,tuple<int,int>> res = make_tuple(n, make_tuple(2*n+2, 2*n+2));
    for(int i=0; i<v.size(); i++){
        if(get<0>(get<1>(v[i])) < get<0>(get<1>(res)) and get<0>(get<1>(v[i])) >= ult){
            res = v[i];
        }
    }
    return res;
}


vector<tuple<int, tuple<int, int>>> activsMax(vector<tuple<int,int>> v){
    vector<vector<tuple<int, tuple<int, int>>>> buckets = bucketSort(v);
    vector<tuple<int, tuple<int, int>>> res;
    int ultimaTerm = -1;
    for(int b=0; b<buckets.size(); b++){
        tuple<int,tuple<int,int>> mejorTemp = minimoPosible(buckets[b],ultimaTerm);
        if (mejorTemp != make_tuple(n, make_tuple(2*n+2, 2*n+2))){
            ultimaTerm = get<1>(get<1>(mejorTemp));
            res.push_back(mejorTemp);
        }
    }
    return res;
}

void respuesta(){
    //vector<tuple<int,int>> vec =  {make_tuple(6,7), make_tuple(1,4), make_tuple(0,3), make_tuple(4,10), make_tuple(3,6)};
    int cant; int s; int t; vector<tuple<int,int>> vec;
    cin>> cant;
    for(int i=0; i<cant; i++){
        cin >> s >> t;
        vec.push_back(make_tuple(s,t));
    }

    vector<tuple<int, tuple<int, int>>> optim = activsMax(vec);
    cout << optim.size() << endl;
    for(int i=0; i<optim.size(); i++){
        cout << get<0>(optim[i]) + 1 << endl;
        //cout << get<0>(get<1>(optim[i])) << " " << endl;
        //cout << get<1>(get<1>(optim[i])) << "\n" << endl;
    }
}




int main(){
    respuesta();
    return 0;
}