#include <iostream>
#include "contain.h"

using namespace std;

void simulate(container c) {
	int counter = 0;
	while (counter < 7) {
		auto current = c.get_head();
		while (current) {
			current->b->f();
			auto other = current->next;
			while (other) {
				other->b->f();
				other = other->next;
			}
			current = current->next;
		}
		cout << "---------------------" << endl;
		counter++;
	}
}

void print(body *b) {
	b->f();
}

int main() {
	body *c = new circle;
	body *r = new rectangle;
	body *p = new polygon;

	scan_collision(c, r);
	return 0;
}


