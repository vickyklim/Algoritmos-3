#include <vector>
#include<iostream>

using namespace std;

int n;
vector<vector<int>> cuadrado;
vector<vector<int>> solucion;
int kesima;
int contador = 0;
int suma_magica;
vector<bool> disponibles;
vector<int> sumaFilaAcum;
vector<int> sumaColAcum;
int sumaDiag1Acum = 0;
int sumaDiag2Acum = 0;


void leer_cuadrado(){
    int nxn; int elementok;
    //cout << "Ingresa el n: ";
    cin >> nxn >> elementok;
    //cout << " Ingresa el k: ";
    n = nxn;
    vector<bool> vale((n*n)+1,true);
    kesima = elementok;
    disponibles = vale;
    suma_magica = n*(n*n+1)/2;
    cuadrado = vector<vector<int>>(n, vector<int>(n, 0));
    sumaColAcum = vector<int>(n,0);
    sumaFilaAcum = vector<int>(n,0);
}
// CERR salida de control (?


void escribir_cuadrado(){
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) cout<<solucion[i][j]<<' ';
        cout<<'\n';
    }
}


vector<int> posibles(int i, int j){
    if(cuadrado[i][j] != 0){
        return {cuadrado[i][j]};
    }
    vector<bool> vale((n*n)+1,true);

    for (int row = 0; row < i; row++) {  //
        for (int col = 0; col < n; col++) {  //
            int num = cuadrado[row][col];  //
            vale[num] = false;
        }
    }
    for (int col = 0; col <= j; col++) {  //
        int num = cuadrado[i][col];  //
        vale[num] = false;
    }
    vector<int> res;
    for(int x = 1; x <= n*n; x++) if(vale[x]) res.push_back(x);
    return res;
}

/*
bool esFilaValida(int i,int j){
    bool res = true;
    int suma_temp = 0;
    if(j == n-1){
        for(int k = 0; k<n;k++){
            suma_temp += cuadrado[i][k];
        }
        if(suma_temp != suma_magica){
            res = false;
        }
    }
    return res;
}
*/
bool esFilaValida(int i, int j){
    if(sumaFilaAcum[i] >= suma_magica and j<n-1){
        return false;
    }
    if(sumaFilaAcum[i] != suma_magica and j==n-1){
        return false;
    }
    return true;
}

/*
bool esColumnaValida(int i,int j){
    bool res = true;
    int suma_temp = 0;
    if(i == n-1){
        for(int k = 0; k<n;k++){
            suma_temp += cuadrado[k][j];
        }
        if(suma_temp != suma_magica){
            res = false;
        }
    }
    return res;
}
*/
bool esColumnaValida(int i, int j){
    if(sumaColAcum[j] >= suma_magica and i<n-1){
        return false;
    }
    if(sumaColAcum[j] != suma_magica and i==n-1){
        return false;
    }
    return true;
}

/*
bool sonDiagValidas(int i,int j){
    bool res = true;
    int suma_temp = 0;
    if(i == n-1 && j== 0){
        for (int k = 0; k < n; k++) {
            int q = n - 1 - k;
            suma_temp += cuadrado[k][q];
        }
        if(suma_temp != suma_magica){
            res = false;
        }
    }
    else if(i == n-1 && j== n-1){
        for (int k = 0; k < n; k++) {
            suma_temp += cuadrado[k][k];
        }
        if(suma_temp != suma_magica){
            res = false;
        }
    }

    return res;
}
*/

bool sonDiagValidas(int i, int j){
    if(sumaDiag1Acum >=suma_magica and i!=n-1 and j!=n-1){
        return false;
    }
    if(sumaDiag1Acum != suma_magica and i==n-1 and j==n-1){
        return false;
    }
    if(sumaDiag2Acum >= suma_magica and i!=n-1 and j!=0){
        return false;
    }
    if(sumaDiag2Acum != suma_magica and i==n-1 and j==0){
        return false;
    }
    return true;
}

void cuadrados_solver(int i = 0, int j = 0){
    if (contador == kesima) return;
    if(i == n) { // Chequea cuando el iterador de las filas se pasa del indexado real, entonces pasó por todas las filas.
        contador += 1;
        // cout << contador << "\n" << endl;
        if(contador == kesima) {
            //printMatrix(cuadrado);
            solucion = cuadrado;
        }
        return;
    }

    int ip = i;
    int jp = j+1;
    if(jp == n) ip++, jp = 0;
    for(int disp=1; disp<disponibles.size(); disp++) {
        if (disponibles[disp]) {
            cuadrado[i][j] = disp;
            disponibles[disp] = false;
            sumaFilaAcum[i] += disp;
            sumaColAcum[j] += disp;
            if(i==j){
                sumaDiag1Acum += disp;
            }
            if(j==n-1-i){
                sumaDiag2Acum += disp;
            }
            if(esFilaValida(i,j) && esColumnaValida(i,j) && sonDiagValidas(i,j)) {

                cuadrados_solver(ip, jp);
            }
            sumaFilaAcum[i] -= disp;
            sumaColAcum[j] -= disp;
            if(i==j){
                sumaDiag1Acum -= disp;
            }
            if(j==n-1-i){
                sumaDiag2Acum -= disp;
            }
            disponibles[disp] = true;
        }
    }
    cuadrado[i][j] = 0;
}


int main() {
    leer_cuadrado();
    if((n==3 and kesima > 8) or (n==4 and kesima >7040)){
        cout << "-1"<< endl;
    }else{
        cuadrados_solver();
        escribir_cuadrado();
    }
    return 0;
}