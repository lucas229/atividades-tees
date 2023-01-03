#include <iostream>
#include <vector>

using namespace std;

typedef struct Maquina {
    string nome;
    int cores;
    int ram;
} Maquina;

void imprimirMatriz(vector <vector <int>> matriz) {
    for(int i = 0; i < matriz.size(); i++) {
        for(int j = 0; j < matriz[i].size(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int m;
    cin >> m;
    vector <Maquina> maquinas(m);
    for(int i = 0; i < m; i++) {
        cin >> maquinas[i].nome;
        cin >> maquinas[i].ram;
        cin >> maquinas[i].cores;
    }

    int n;
    cin >> n;
    vector <Maquina> maquinasVirtuais(n);
    for(int i = 0; i < n; i++) {
        cin >> maquinasVirtuais[i].nome;
        cin >> maquinasVirtuais[i].ram;
        cin >> maquinasVirtuais[i].cores;
    }

    int cont = m + 1;
    vector <vector <int>> matriz;
    for(int i = 0; i < m; i++) {
        vector <int> v;
        for(int j = 0; j < n; j++) {
            v.push_back(cont++);
        }
        matriz.push_back(v);
    }

    // 1
    cout << "* #variable= " << m * n + m << " #constraint= " << "TODO" << endl;
    cout << "min:";
    for(int i = 1; i <= m; i++) {
        cout << " +1 x" << i;
    }
    cout << " ;" << endl;

    int somaRam = 0, somaCores = 0;
    for(int i = 0; i < n; i++) {
        somaRam += maquinasVirtuais[i].ram;
        somaCores += maquinasVirtuais[i].cores;
    }

    // 2
    for(int i = 0; i < m; i++) {
        cout << "+" << maquinas[i].ram << " x" << i + 1 << " ";
    }
    cout << ">= " << somaRam << ";" << endl;

    // 3
    for(int i = 0; i < m; i++) {
        cout << "+" << maquinas[i].cores << " x" << i + 1 << " ";
    }
    cout << ">= " << somaCores << ";" << endl;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cout << "+" << maquinasVirtuais[j].ram << " ~x" << matriz[i][j] << " ";
        }
        cout << "+" << maquinas[i].ram << " x" << i + 1;
        cout << " >= " << somaRam << ";" << endl;
    }
    return 0;
}