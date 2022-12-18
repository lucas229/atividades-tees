#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <unordered_set>

using namespace std;

int tamanho;

typedef struct estado
{
    vector <int> state;
    string sequencia;
} estado;


void printCurrent(vector <int> &V){
    cout << "================";
    for(int i=0; i<V.size(); i++){
        if(i%tamanho == 0)
            cout << endl;
        cout << " " << V[i] << " ";
    }
    cout << endl;
}

size_t hashVector(vector <int> &v) {
    size_t seed = v.size();
    for(auto& i: v) {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

bool verifyCompletion(vector <int> V){
    for(int i=0; i<V.size(); i++){
        if(V[i] != i)
            return false;
    }
    return true;
}

vector <estado> possibleMoves(estado &V){
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

bool verifySeen(vector <int> &state, unordered_set <size_t> &seen) {
    if(seen.find(hashVector(state)) != seen.end()) {
        return true;
    }
	return false;
}

int distancia(estado &est) {
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
    bool operator()(estado & a, estado & b)
    {
        return distancia(a) + a.sequencia.size() > distancia(b) + b.sequencia.size();
    }
};

estado solve(vector <int> &puzzle) {
	unordered_set <size_t> seen{hashVector(puzzle)};
	priority_queue <estado, vector<estado>, compare> queue;
    estado base = {puzzle, ""};
    queue.push(base);

	while(queue.size() > 0) {
		estado current = queue.top();
		queue.pop();

        //cout << "Profundidade: " << current.sequencia.size() << endl;

		if (verifyCompletion(current.state)) {
			return current;
		}

        vector <estado> neighbours = possibleMoves(current);
		for (int i = 0; i < neighbours.size(); i++) {
			if (!verifySeen(neighbours[i].state, seen)) {
				seen.insert(hashVector(neighbours[i].state));
				queue.push(neighbours[i]);
			}
		}
	}

    estado est{vector <int>(), ""};
    return est;
}

int main(){	
    cin >> tamanho >> tamanho;

	vector <int> E(tamanho * tamanho);
    for(int i=0; i<E.size(); i++){
        cin >> E[i];
    }

	estado solution = solve(E);

	printCurrent(solution.state);
    cout << endl << "Movimentos necessários: " << solution.sequencia.size() << endl;
	cout << "Sequência: " << solution.sequencia << endl;
    return 0;
}
