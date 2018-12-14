#ifndef PHYSICS_SHAPES_H
#define PHYSICS_SHAPES_H

#include <vector>
#include "vectors.h"

class Polygon {
private:
    std::vector<Point*> vertices;
    std::vector<Vector> edges;
    std::vector<Vector> axes;

    void construct_edges();
    void construct_verts();
    void construct_centroid();
    void set_upright();

public:
    Point *pos;
    double radius;
    int num_vertices;

    explicit Polygon(std::vector<Point*>& verts);
    explicit Polygon(Point *p = new Point, int nv = 4, double rad = 1);

    std::vector<Point*>& get_verts() {return vertices;}
    std::vector<Vector>& get_edges() {return edges;}
    std::vector<Vector>& get_axes() {return axes;}
    bool is_upright();
    virtual Vector projection(const Vector& axis) const;
};

class Circle : public Polygon {
public:
    explicit Circle(Point *p = new Point, double rad = 1) : Polygon(p, 0, rad) {}
    Vector projection(const Vector& axis) const override;
};

bool collision(Polygon& a, const Polygon& b);

#endif
