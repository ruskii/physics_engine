#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <unistd.h>
#include "point.h"
using namespace std;

struct Vector {
    Vector() : tail(new Point), head(new Point), x_cmp(0), y_cmp(0), mag(0) {}
    Vector(Point *t, Point *h) : tail(t), head(h) {}
    ~Vector() = default;
    Point *tail;
    Point *head;
    double x_cmp = head->x - tail->x;
    double y_cmp = head->y - tail->y;
    double mag = sqrt(pow(x_cmp, 2) + pow(y_cmp, 2));       // pyth theorem to get magnitude
	friend Vector& operator+(Vector& a, Vector& b);
    friend Vector& operator+=(Vector& a, Vector& b);
	friend Vector& operator-(Vector& a, Vector& b);
	friend Vector& operator*(double scalar, Vector& a);
	friend ostream& operator<<(ostream& os, Vector& vec);
};

double get_mag(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vector& operator+(Vector& a, Vector& b) {       // vector addition
    auto final_point = new Point(a.head->x + b.x_cmp, a.head->y + b.y_cmp);      // head of vector resulting from addition
    auto b2 = new Vector(a.head, final_point);       // creating "ghost" vector B
    Vector sum = Vector(a.tail, b2->head);      // result vector starts at a tail and ends at b2 head
    return sum;
}

Vector& operator+=(Vector& a, Vector& b) {
    auto final_point = new Point(a.head->x + b.x_cmp, a.head->y + b.y_cmp);
    auto b2 = new Vector(a.head, final_point);
    a = Vector(a.tail, b2->head);
    return a;
}

Vector& operator-(Vector& a, Vector& b) {
    auto final_point = new Point(a.head->x - b.x_cmp, a.head->y - b.y_cmp);
    auto b2 = new Vector(a.head, final_point);
    Vector diff = Vector(a.tail, b2->head);
    return diff;
}

Vector& operator-=(Vector& a, Vector& b) {
    auto final_point = new Point(a.head->x - b.x_cmp, a.head->y - b.y_cmp);
    auto b2 = new Vector(a.head, final_point);
    a = Vector(a.tail, b2->head);
    return a;
}

Vector& operator*(double scalar, Vector& a) {   // multiply vector by some scalar
    double nx = a.tail->x + scalar*a.x_cmp;
    double ny = a.tail->y + scalar*a.y_cmp;
    auto vp = new Point(nx, ny);
    Vector product = Vector(a.tail, vp);
    return product;
}

ostream& operator<<(ostream& os, Vector& vec) {
    string op = "x: " + to_string(vec.head->x) + " y: " + to_string(vec.head->y) \
    + "\nmag: " + to_string(vec.mag);
    os << op << endl;
    return os;
}

