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
    string sequence;
} estado;


void printCurrent(vector <int> &V){
    cout << "================";
    for(int i=0; i<V.size(); i++){
        if(i%tamanho == 0)
            cout << endl;
        cout << " ";
        if(V[i] < 10) {
            cout << "0";
        }
        cout << V[i] << " ";
    }
    cout << endl;
}

void printSolution(vector <int> V, string sequence) {
    int pos;
    for(int i = 0; i < V.size(); i++) {
        if(V[i] == 0) {
            pos = i;
            break;
        }
    }

    printCurrent(V);
    for(char c: sequence) {
        if(c == 'C') {
            iter_swap(V.begin() + pos, V.begin() + pos - tamanho);
            pos = pos - tamanho;
        } else if(c == 'B') {
            iter_swap(V.begin() + pos, V.begin() + pos + tamanho);
            pos = pos + tamanho;
        } else if(c == 'E') {
            iter_swap(V.begin() + pos, V.begin() + pos-1);
            pos = pos - 1;
        } else if(c == 'D'){
            iter_swap(V.begin() + pos, V.begin() + pos+1);
            pos = pos + 1;
        }
        printCurrent(V);
    }
}

size_t hashVector(vector <int> &V) {
    size_t seed = V.size();
    for(auto& i: V) {
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
                estado novo = {V.state, V.sequence+"C"};
                iter_swap(novo.state.begin() + i, novo.state.begin() + i - tamanho);
			    moves.push_back(novo);
            }
            if (line != tamanho-1){
                // Baixo
                estado novo = {V.state, V.sequence+"B"};
                iter_swap(novo.state.begin() + i, novo.state.begin() + i + tamanho);
			    moves.push_back(novo);
            } 
            if (column != 0) {
                // Esquerda
                estado novo = {V.state, V.sequence+"E"};
                iter_swap(novo.state.begin() + i, novo.state.begin() + i-1);
			    moves.push_back(novo);
            }
            if (column != tamanho-1) {
                // Direita
                estado novo = {V.state, V.sequence+"D"};
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
        // g() + h()
        return distancia(a) + a.sequence.size() > distancia(b) + b.sequence.size();
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

    printSolution(E, solution.sequence);
    cout << endl << "Número de movimentos: " << solution.sequence.size() << endl;
	cout << "Sequência: " << solution.sequence << endl;
    return 0;
}
