#include <iostream>
#include "List.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

void invertirBase(Stack<int> &p, int n) {

	Stack<int> rep;
	Queue<int> loop;
	for (int i = 0; i < n; i++) {
		rep.push(p.top());
		p.pop();
	}
	while (!p.empty()) {
		loop.push_back(p.top());
		p.pop();
	}
	while (!loop.empty()) {
		p.push(loop.front());
		loop.pop_front();
	}
	while (!rep.empty()) {
		p.push(rep.top());
		rep.pop();
	}
}

int main() {

	Stack<int> p;
	p.push(1); p.push(2); p.push(3); p.push(4); p.push(5); p.push(6); p.push(7); p.push(8); p.push(9); p.push(10);

	cout << p.top() << endl;

	invertirBase(p, 7);

	while (!p.empty()) {
		cout << p.top() << " ";
		p.pop();
	}
	cout << endl;

	cout << endl;
	system("pause");
}