#include <cmath>
#include "vectors.h"

using namespace std;

double magnitude(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

double determinant(double a, double b, double c, double d) {
    return (a * d) - (b * c);
}

bool Vector::operator==(const Vector& other) const {
    return x_cmp == other.x_cmp and y_cmp == other.y_cmp;
}

Vector Vector::normal() const {
    auto inverse = 1 / mag;
    Vector normalized = inverse * (this->perpendicular());
    return normalized;
}

Vector Vector::perpendicular() const {
    auto normal_tail = midpoint(*tail, *head);
    auto normal_head = new Point(normal_tail->x - y_cmp, normal_tail->y + x_cmp);
    Vector norm(normal_tail, normal_head);
    return norm;
}

double dot(const Vector& a, const Vector& b) {
    return a.x_cmp * b.x_cmp + a.y_cmp * b.y_cmp;
}

bool colinear_intersection(const Point *p, const Point *q, const Point *r) {
    return q->x <= fmax(p->x, r->x) and q->x >= fmin(p->x, r->x) and
    q->y <= fmax(p->y, r->y) and q->y >= fmin(p->y, r->y);

}

/*
 * 0 - colinear
 * 1 - clockwise
 * 2 - counter clockwise
 */
int point_orientation(const Point *p, const Point *q, const Point *r) {
    auto val = (q->y - p->y) * (r->x - q->x) - (q->x - p->x) * (r->y - q->y);

    if (val == 0) return 0;

    return (val > 0) ? 1 : 2;
}

bool overlap(const Vector& a, const Vector& b) {
    auto orient1 = point_orientation(a.tail, a.head, b.tail);
    auto orient2 = point_orientation(a.tail, a.head, b.head);
    auto orient3 = point_orientation(b.tail, b.head, a.tail);
    auto orient4 = point_orientation(b.tail, b.head, a.head);

    // general case
    if (orient1 != orient2 and orient3 != orient4)
        return true;

    // special colinear cases
    if (orient1 == 0 and colinear_intersection(a.tail, b.tail, a.head)) return true;

    if (orient2 == 0 and colinear_intersection(a.tail, b.head, a.head)) return true;

    if (orient3 == 0 and colinear_intersection(b.tail, a.tail, b.head)) return true;

    return orient4 == 0 and colinear_intersection(b.tail, a.head, b.head);

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

