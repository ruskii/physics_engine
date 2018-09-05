#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <unistd.h>
#include "point.h"

using namespace std;

// Pythagorean theorem
double get_mag(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

/* Mathematical vector, contains 2 points - tail and head
   Consists of x and y components, calculated by subtracting tail from head
   Magnitude calculated by pythagorean theorem
*/
struct Vector {
    Vector() : tail(new Point), head(new Point), x_cmp(0), y_cmp(0), mag(0) {}
    Vector(Point *t, Point *h) : tail(t), head(h) {}
    ~Vector() = default;
    Point *tail;
    Point *head;
    double x_cmp = head->x - tail->x;
    double y_cmp = head->y - tail->y;
    double mag = get_mag(x_cmp, y_cmp);
};

Vector& operator+(Vector& a, Vector& b) {       // vector addition
    auto final_point = new Point(a.head->x + b.x_cmp, a.head->y + b.y_cmp);      // head of vector resulting from addition
    auto b2 = new Vector(a.head, final_point);       // creating "ghost" vector B
    Vector sum = Vector(a.tail, b2->head);      // result vector starts at a tail and ends at b2 head
    return sum;
}

// using += to increment an already existing vector	e.g: vec A += vec B
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

// Outputs vector x and y components as well as its magnitude
ostream& operator<<(ostream& os, Vector& vec) {
    string op = "x: " + to_string(vec.head->x) + " y: " + to_string(vec.head->y) \
    + "\nmag: " + to_string(vec.mag);
    os << op << endl;
    return os;
}

