#include <cmath>
#include <cstring>
#include <iterator>
#include "polygon.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#define PI 3.14159265

using namespace std;
using namespace boost::geometry;

Polygon::Polygon(vector<Point*> &verts) : vertices(verts), num_vertices(int(verts.size())), orientation(0) {
    construct_edges();
    construct_centroid();
}

Polygon::Polygon(Point *p, int nv, double rad, double ort) : pos(p), num_vertices(nv), radius(rad), orientation(ort) {
    if (nv > 0) {
        construct_verts();

        if (orientation == 0 and !is_upright()) // if no given orientation and not upright, set upright at 270 degrees
            rotate(270);
        else
            rotate(orientation);

        construct_edges();
    }
}

void Polygon::construct_edges() {
    for (int i = 0; i < num_vertices; i++) {
        auto end_point = vertices[(i + 1) == num_vertices ? 0 : i + 1];
        Vector edge(vertices[i], end_point);

        edges.push_back(edge);
        auto norm = edge.normal();
        axes.push_back(norm);
    }
}

double rounded(double value) {
    return round(value * 10000.0) / 10000.0;
}

pair<double, double> get_components(double angle) {
    double x_component = rounded(cos(angle * PI / 180));
    double y_component = rounded(sin(angle * PI / 180));
    return make_pair(x_component, y_component);
}

Point* relative_spawn_point(double angle, Point *from, double distance) {
    auto components = get_components(angle);
    auto x_target = from->x + distance * components.first;
    auto y_target = from->y + distance * components.second;
    return new Point(x_target, y_target);
}

void Polygon::construct_verts() {   // TODO: try with different num_vertices
    double d_theta = 360.0 / num_vertices;

    for (int i = 1; i <= num_vertices; i++) {
        double angle = 360 - (i * d_theta);
        auto target = relative_spawn_point(angle, pos, radius);
        vertices.push_back(target);
    }
}

bool Polygon::is_upright() {
    if (!num_vertices)
        return true;

    vector<Point*>::iterator vert;

    for (vert = vertices.begin(); vert < vertices.end() - 1; vert++) {
        Vector face(*vert, *(vert + 1));
        auto face_norm = face.normal();

        if (face_norm.x_cmp == 0 and face_norm.y_cmp != 0)
            return true;
    }
    return false;
}

void Polygon::shift(const Vector& vec, float dt) {
    pos->x += vec.x_cmp * dt;
    pos->y += vec.y_cmp * dt;

    for (auto vert : vertices) {
        (*vert).x += vec.x_cmp * dt;
        (*vert).y += vec.y_cmp * dt;
    }
    construct_edges();
}

double find_direction(double x, double y) {
    double direction = rounded(atan2(y, x) * 180 / PI);
    direction = (direction < 0) ? 360 + direction : direction;
    return direction;
}

void Polygon::rotate(double angle, bool rotate_by) {
    if (num_vertices > 1) {
        auto compass_head = midpoint(*vertices[0], *vertices[1]);
        Vector compass(pos, compass_head);

        double compass_dir = find_direction(compass.x_cmp, compass.y_cmp);
        double rotation = (rotate_by) ? angle : -(compass_dir - angle);
        orientation = rotation;

        vector<Point*>::iterator vert;
        for (vert = vertices.begin(); vert < vertices.end(); vert++) {
            Vector needle(pos, *vert);
            auto vert_direction = find_direction(needle.x_cmp, needle.y_cmp);
            auto target_direction = vert_direction + rotation;
            auto target_point = relative_spawn_point(target_direction, pos, radius);
            *vert = target_point;
        }
    }
}

void Polygon::construct_centroid() {
    typedef model::d2::point_xy<double> point_type;
    typedef model::polygon<point_type> polygon_type;

    point_type p;
    polygon_type poly;
    string coords = "POLYGON((";

    vector<Point*>::iterator vert;

    for (vert = vertices.begin(); vert < vertices.end(); vert++) {
        coords += to_string((*vert)->x) + " " + to_string((*vert)->y) + ", ";

        if (vert + 1 == vertices.end())
            coords += to_string((*vertices.begin())->x) + " " + to_string((*vertices.begin())->y);
    }
    coords += "))";

    read_wkt(coords, poly);
    centroid(poly, p);

    pos = new Point(p.get<0>(), p.get<1>());
}

Vector Polygon::projection(const Vector& axis) const {
    Vector screen(new Point, new Point(1));
    double min = dot(screen, Vector(axis.tail, vertices[0]));
    double max = min;

    for (auto vert : vertices) {
        double p = dot(screen, Vector(axis.tail, vert));

        if (p < min)
            min = p;
        else if (p > max)
            max = p;
    }
    double range = magnitude(max - min, 0) / 2;
    Vector projected(new Point(pos->x - range), new Point(pos->x + range));
    return projected;
}

Vector Circle::projection(const Vector& axis) const {
    Vector projected(new Point(pos->x - radius), new Point(pos->x + radius));
    return projected;
}

bool collision(Polygon& a, const Polygon& b) {
    if (a.num_vertices == 0 and b.num_vertices == 0) {
        double r = a.radius + b.radius;
        r *= r;
        double x_dist = pow(a.pos->x - b.pos->x, 2);
        double y_dist = pow(a.pos->y - b.pos->y, 2);
        return r > (x_dist + y_dist);
    }

    for (auto axis : a.get_axes()) {
        auto a_proj = a.projection(axis);
        auto b_proj = b.projection(axis);

        if (!overlap(a_proj, b_proj))
            return false;
    }
    return true;
}

