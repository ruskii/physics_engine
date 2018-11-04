#include <iostream>
#include <cmath>
#include "vectors.h"

using namespace std;

double magnitude(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

double Vector::get_mag() const {return mag;}

bool Vector::operator==(const Vector& other) const {
    if (mag != other.mag)
        return false;
    return x_cmp == other.x_cmp and y_cmp == other.y_cmp;
}

Vector operator+(const Vector& a, const Vector& b) {
    auto final_point = new Point(a.head->x + b.x_cmp, a.head->y + b.y_cmp);
    auto ghost_vector = new Vector(a.head, final_point);
    Vector sum = Vector(a.tail, ghost_vector->head);
    return sum;
}

Vector operator+=(Vector& a, const Vector& b) {
    auto final_point = new Point(a.head->x + b.x_cmp, a.head->y + b.y_cmp);
    auto ghost_vector = new Vector(a.head, final_point);
    a = Vector(a.tail, ghost_vector->head);
    return a;
}

Vector operator-(const Vector& a, const Vector& b) {
    auto final_point = new Point(a.head->x - b.x_cmp, a.head->y - b.y_cmp);
    auto ghost_vector = new Vector(a.head, final_point);
    Vector diff = Vector(a.tail, ghost_vector->head);
    return diff;
}

Vector operator-=(Vector& a, const Vector& b) {
    auto final_point = new Point(a.head->x - b.x_cmp, a.head->y - b.y_cmp);
    auto ghost_vector = new Vector(a.head, final_point);
    a = Vector(a.tail, ghost_vector->head);
    return a;
}

Vector operator*(double scalar, const Vector& a) {
    double nx = a.tail->x + scalar * a.x_cmp;
    double ny = a.tail->y + scalar * a.y_cmp;
    auto vp = new Point(nx, ny);
    Vector product = Vector(a.tail, vp);
    return product;
}

ostream& operator<<(ostream& os, const Vector& vec) {
    string op = "x: " + to_string(vec.head->x) + " y: " + to_string(vec.head->y) \
    + "\nmag: " + to_string(vec.mag);
    os << op << endl;
    return os;
}

