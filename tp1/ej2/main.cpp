#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
long long n = 3;
long long m = 100000;
vector<bool> restos;
vector<long long> v;
long long r = 0;


bool operacionmodrec(long long sum, long long i){
    if (i == n) {
        return (sum % m == r);
    }
    else{
        return (operacionmodrec(sum + v[i], i+1)) || (operacionmodrec(sum - v[i], i+1) )|| (operacionmodrec(sum * v[i],i+1)) || (operacionmodrec(pow(sum,v[i]),i+1));
    }
}


int restoModm(long long n, long long div){
    if(n>=0){
        return n%div;
    } else{
        return n%div + div;
    }
};

long long potencia_mod(long long base, long long exponente) {
    if (exponente == 0) {
        return 1;
    } else {
        long long temp = potencia_mod(base, exponente / 2);
        long long resultado = (temp * temp) % m;
        if (exponente % 2 != 0) {
            resultado = (resultado * base) % m;
            return resultado;
        }else {
            return resultado;
        }
    }
}


bool esrModm(long long r){
    return restos[r];
}
void operacionmodimp(vector<bool> &restos){
    vector<bool> aux(m, false);
    for(long long i = 1; i < v.size(); i++){
        for(long long j=0; j < restos.size(); j++){
            if(restos[j]){
                aux[restoModm((j+v[i]) , m)] = true;
                aux[restoModm((j-v[i]) , m)] = true;
                aux[restoModm((j*v[i]) , m)] = true;
                aux[restoModm(static_cast<long long>(potencia_mod(j,v[i]))  , m)] = true;
            }
        }
        restos = aux;
        aux = vector<bool> (m, false);
    }
    if(esrModm(r)){
        cout << "Si" << endl;
    } else {
        cout << "No" << endl;
    }
    return;
}


void leer_input(){
    long long casos; long long longitud; long long mod_r; long long divisor; vector<long long> vec;
    cin>> casos;
    for(long long i=0; i<casos; i++){
        cin >> longitud >> mod_r >> divisor;
        n = longitud;
        r = mod_r;
        m = divisor;
        for(long long j=0; j<longitud; j++) {
            long long temp;
            cin >> temp;
            vec.push_back(temp);
        }
        v = vec;
        vec = {};
        vector<bool> vec_false(m,false);
        restos = vec_false;
        restos[restoModm(v[0],m)] = true;
        operacionmodimp(restos);

    }
}

int main() {
    leer_input();
    //cout << restoModm(-1001, 5) << endl;
    return 0;
}