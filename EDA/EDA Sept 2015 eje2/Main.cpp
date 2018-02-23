#include <iostream>
#include "List.h"
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>
#include "Queue.h"
#include "Stack.h"

using namespace std;

const int N = 5;
const int M = 6;

pair<int,int> rectangulo(int matriz[][M]) {

	pair<int, int> ret;
	int x = 0, y = 0;
	bool found = false;
	while (x < N && !found) {
		if (matriz[x][M-1] == 1)
			found = true;
		else 
			x++;
	}
	found = false;
	while (y < M && !found) {
		if (matriz[N-1][y] == 1)
			found = true;
		else
			y++;
	}
	return ret = make_pair(x, y);
}

int main() {

	int matriz[N][M];

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			if (x > 2 && y > 3)
				matriz[x][y] = 1;
			else
				matriz[x][y] = 0;
		}
	}

	pair<int, int> utopia = rectangulo(matriz);
	get<0>(utopia);

	system("pause");
}