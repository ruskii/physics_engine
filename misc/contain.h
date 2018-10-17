#include <iostream>
#include "shapes.h"

using namespace std;

struct element {
	explicit element(body *x) : b(x) {}
	body *b;
	element *next;
	element *prev;
};

class container {
private:
	element *head;
	element *tail;

public:
	container() = default;
	explicit container(body *x) {head = new element(x); tail = nullptr;}
	~container() = default;

	element* get_head() {return head;}
	element* get_tail() {return tail;}

	void append(body *x) {
		auto n = new element(x);

		if (!tail) {
			head->next = n;
			n->prev = head;
			tail = n;
			return;
		}
		tail->next = n;
		n->prev = tail;
		tail = n;
	}
};



