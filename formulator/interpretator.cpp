#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    
    if(argc < 2){
        cout << "Usagem: " << argv[0] << "<saida do solver>" << endl;
        return 1;
    }
    int hw, vm;
    cout << "Insira a quantidade de Hardwares" << endl;
    cin >> hw;
    cout << "Insira a quantidade de Maquinas Virtuais" << endl;
    cin >> vm; 

    ifstream saidaSolver(argv[1]);
    string linha;
    // Le linha da saida do solver
    int count = 0;
    while (getline(saidaSolver, linha))
    {
        // Pega linhas que comecam com 'v'
        if(linha[0] == 'v') {
            string item;
            stringstream streamLinha(linha);
            // Le cada item da linha
            while(getline(streamLinha, item, ' ')) {
                if(item != "v"){
                    int pos = item.find("x");
                    string sub = item.substr(pos + 1);
            
                    int num = stoi(sub);
                    int nLinha = (num - hw - 1) / vm;
                    int nCol = (num - hw - 1) % vm;
                    
                    if(item[0] != '-' && num <= hw) {
                        cout << "Hardware " << sub << " ligado" << endl;
                    }
                    else if(item[0] != '-'){
                        cout << "Maquina " << nCol+1 << " alocada no Hardware " << nLinha+1 << endl;
                    }
                }
            }
        }
    }

    return 0;
}