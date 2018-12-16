#ifndef PHYSICS_SHAPES_H
#define PHYSICS_SHAPES_H

#include <vector>
#include "vectors.h"

class Polygon {
private:
    std::vector<Point*> vertices;
    std::vector<Vector> edges;
    std::vector<Vector> axes;

    void construct_edges();     // constructing edges and their normals (axes) by connecting vertices
    void construct_verts();     // spawn vertices based off of num_vertices
    void construct_centroid();  // boost geometry lib to find centroid of vertex positions

public:
    Point *pos;
    double radius;
    double orientation;
    int num_vertices;

    explicit Polygon(std::vector<Point*>& verts);
    explicit Polygon(Point *p = new Point, int nv = 4, double rad = 1, double ort = 0);

    std::vector<Point*>& get_verts() {return vertices;}
    std::vector<Vector>& get_edges() {return edges;}
    std::vector<Vector>& get_axes() {return axes;}
    bool is_upright();
    void shift(const Vector& vec, float dt = 0);
    void rotate(double angle = 0, bool rotate_by = false);
    virtual Vector projection(const Vector& axis) const;    // projecting shape onto an axis
};

class Circle : public Polygon {
public:
    explicit Circle(Point *p = new Point, double rad = 1) : Polygon(p, 0, rad) {}
    Vector projection(const Vector& axis) const override;   // simply project circles radius onto axis
};

bool collision(Polygon& a, const Polygon& b);

#endif
