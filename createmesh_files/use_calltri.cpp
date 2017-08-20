#include <iostream>
#include "calltri.h"

int main() {

MeshGeneration m;

m.input_polygon_vertices({{0.0, 0.0}, {0.0, 3.0}, {3.0, 0.0}, {3.0, 3.0}});
m.input_holes(1, {1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 2.0, 2.0}, {1.5, 1.5}, 5, {0, 1, 4, 6, 6, 7, 7, 5, 5, 4});
/*
m.input_polygon_vertices({0.0, 0.0, 1.0, 0.0, 1.0, 10.0, 0.0, 10.0});
m.input_pointattributelist(1,{0.0,1.0,11.0,10.0});
m.input_pointmarkerlist({0,2,0,0});
m.input_regionlist(1,{0.5,5.0,7.0,0.1});
*/
m.basic_triangulation(true);
//m.tri_areaconstraintlist({3.0,1.0});
//m.refined_triangulation(false);

m.refined_triangulation(true);
return 0;

}
