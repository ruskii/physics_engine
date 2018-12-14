#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::geometry;

int main() {
    typedef model::d2::point_xy<double> point_type;
    typedef model::polygon<point_type> polygon_type;

    polygon_type poly;
    read_wkt(
        "POLYGON((0.0 0.0, 0.0 4.0, 4.0 4.0, 4.0 0.0, 0.0 0.0))" , poly);

    point_type p;
    centroid(poly, p);

    double x = p.get<0>();
    double y = p.get<1>();

    std::cout << "centroid: " << dsv(p) << std::endl;
    std::cout << "x: " << x << "\ty: " << y << std::endl;

    return 0;
}
