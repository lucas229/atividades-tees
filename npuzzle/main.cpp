#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;
int tamanho;


typedef struct estado
{
    vector <int> state;
    string sequencia;
} estado;


void printCurrent(vector <int> V, int tamanho){
    cout << "================";
    for(int i=0; i<V.size(); i++){
        if(i%tamanho == 0)
            cout << endl;
        cout << " " << V[i] << " ";
    }
    cout << endl;
}

bool verifyCompletion(vector <int> V){
    for(int i=0; i<V.size(); i++){
        if(V[i] != i)
            return false;
    }
    return true;
}

vector <estado> possibleMoves(estado V, int tamanho){
	vector <estado> moves;
    for(int i=0; i<V.state.size(); i++){
        int line = i / tamanho;
        int column = i % tamanho;
        if(V.state[i] == 0){
            if(line != 0) {
                // Cima
                estado novo = {V.state, V.sequencia+"C"};
                iter_swap(novo.state.begin() + i, novo.state.begin() + i - tamanho);
			    moves.push_back(novo);
            }
            if (line != tamanho-1){
                // Baixo
                estado novo = {V.state, V.sequencia+"B"};
                iter_swap(novo.state.begin() + i, novo.state.begin() + i + tamanho);
			    moves.push_back(novo);
            } 
            if (column != 0) {
                // Esquerda
                estado novo = {V.state, V.sequencia+"E"};
                iter_swap(novo.state.begin() + i, novo.state.begin() + i-1);
			    moves.push_back(novo);
            }
            if (column != tamanho-1) {
                // Direita
                estado novo = {V.state, V.sequencia+"D"};
                iter_swap(novo.state.begin() + i, novo.state.begin() + i+1);
			    moves.push_back(novo);
            }
            
        }
    }
	return moves;
}

bool verifySeen(vector <int> state, vector <vector <int>> seen) {
	for(vector <int> v: seen) {
		if(equal(state.begin(), state.end(), v.begin())){
			return true;
        }
	}
	return false;
}

int distancia(estado est) {
    int dist = 0;
    for(int i = 0; i < tamanho * tamanho; i++) {
        if(est.state[i] != 0){
            int line = i / tamanho;
            int column = i % tamanho;
            int originalLine = est.state[i] / tamanho;
            int originalColumn = est.state[i] % tamanho;
            dist += abs(line - originalLine) + abs(column - originalColumn);
        }
    }
    return dist;
}

struct compare
{
    bool operator()(const estado & a, const estado & b)
    {
        return distancia(a) + a.sequencia.size() > distancia(b) + b.sequencia.size();
    }
};

estado solve(vector <int> puzzle, int tamanho) {
	vector <vector <int>> seen{puzzle};
	priority_queue <estado, vector<estado>, compare> queue;
    estado base = {puzzle, ""};
    queue.push(base);
	while(queue.size() > 0) {
		estado current = queue.top();
		queue.pop();

        cout << "Profundidade: " << current.sequencia.size() << endl;

		if (verifyCompletion(current.state)) {
			return current;
		}
		for (estado neighbour: possibleMoves(current, tamanho)) {
			if (!verifySeen(neighbour.state, seen)) {
				seen.push_back(neighbour.state);
				queue.push(neighbour);
			}
		}
	}

    estado est;
    est.sequencia = "";
    return est;
}

int main(){
	
    cout << "Digite o tamanho da matrix" << endl;
    cin >> tamanho >> tamanho;

	vector <int> E(tamanho * tamanho);

    for(int i=0; i<E.size(); i++){
        cin >> E[i];
    }

	estado solution = solve(E, tamanho);
	printCurrent(solution.state, tamanho);
    cout << endl << "Movimentos necessários: " << solution.sequencia.size() << endl;
	cout << "Sequência: " << solution.sequencia << endl;
    return 0;
}

