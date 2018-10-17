#include <iostream>

using namespace std;

struct circle;
struct rectangle;
struct polygon;

struct body {
	body() : pos(0), vel(0), accel(0) {}
	body(int p, int v, int a) : pos(p), vel(v), accel(a) {}
	int pos, vel, accel;

	virtual void f() = 0;
	virtual void collide(circle *c) = 0;
	virtual void collide(rectangle *r) = 0;
	virtual void collide(polygon *p) = 0;
};

struct circle : body {
	circle() : body(), radius(1) {}
	circle(int r, int p, int v, int a) : body(p, v, a), radius(r) {}
	int radius;

	void f() override {
		cout << "I am a circle" << endl;
	}

	void collide(circle *c) override {cout << "passed circle" << endl;}
	void collide(rectangle *r) override {cout << "passed rectangle" << endl;}
	void collide(polygon *p) override {cout << "passed polygon" << endl;}
};

struct rectangle : body {
	rectangle() : body(), length(1), width(1) {}
	rectangle(int l, int w, int p, int v, int a) : body(p, v, a), length(l), width(w) {}
	int length, width;

	void f() override {
		cout << "I am a rectangle" << endl;
	}

	void collide(circle *c) override {cout << "passed circle" << endl;}
	void collide(rectangle *r) override {cout << "passed rectangle" << endl;}
	void collide(polygon *p) override {cout << "passed polygon" << endl;}
};

struct polygon : body {
	polygon() : body(), edges(5) {}
	polygon(int e, int p, int v, int a) : body(p, v, a), edges(e) {}
	int edges;

	void f() override {
		cout << "I am a polygon" << endl;
	}

	void collide(circle *c) override {cout << "passed circle" << endl;}
	void collide(rectangle *r) override {cout << "passed rectangle" << endl;}
	void collide(polygon *p) override {cout << "passed polygon" << endl;}
};

void scan_collision(body *a, body *b) {
	auto b_type = dynamic_cast<circle*>(b);

	if (b_type) 
		a->collide(b_type);
	else {
		auto b_type = dynamic_cast<rectangle*>(b);

		if (b_type)
			a->collide(b_type);
		else {
			auto b_type = dynamic_cast<polygon*>(b);
			a->collide(b_type);
		}
	}
}


