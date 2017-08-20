#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "calltri.h"

namespace py = pybind11;

PYBIND11_PLUGIN(createmesh) {

py::module mod("createmesh", "wrapping caltri");
/*
py::class_<triangulateio>(mod, "triangulateio")
  .def("pointlist", [] (triangulateio &self) {
    std::vector<REAL> list;
    list.reserve(self.numberofpoints * 2);
    for (int i = 0; i < (self.numberofpoints * 2); ++i)
       list.push_back(self.pointlist[i]);
    return list;
  });
*/

py::class_<triangulateio>(mod, "triangulateio")
  .def("pointlist", [] (triangulateio &self) {
    std::vector< std::vector< std::vector<REAL> > > list;
  
    //list.reserve(self.numberofpoints * 2);
    for (int i = 0; i < self.numberoftriangles; i++) {
      std::vector< std::vector<REAL> > list1;
      for (int j = 0; j < self.numberofcorners; j++) {
        std::vector<REAL> list2;
        for (int k = 0; k < 2; k++) {
          list2.push_back(self.pointlist[2 * (self.trianglelist[i * self.numberofcorners + j]) + k]);
        }
        list1.push_back(list2);
      }
      list.push_back(list1);
    }
    return list;
  });


// creates bindings for the C++ class MeshGeneration 
py::class_<MeshGeneration, std::shared_ptr<MeshGeneration>>(mod, "Meshgeneration") 
  .def(py::init<>())
  .def("input_polygon_vertices", &MeshGeneration::input_polygon_vertices)
  //.def("input_polygon_vertices", [](Meshgeneration &self, py::aray_t<REAL> arg){
  //  auto v = [&self](REAL arg) {return self.input_polygon_vertices(arg);})
  .def("input_holes", &MeshGeneration::input_holes)
  .def("input_pointattributelist", &MeshGeneration::input_pointattributelist)
  .def("input_pointmarkerlist", &MeshGeneration::input_pointmarkerlist)
  //.def("input_segmentmarkerlist", &MeshGeneration::input_segmentmarkerlist)
  .def("input_regionlist", &MeshGeneration::input_regionlist)
  .def("basic_triangulation", &MeshGeneration::basic_triangulation)
  .def("tri_areaconstraintlist", &MeshGeneration::tri_areaconstraintlist)
  .def("refined_triangulation", &MeshGeneration::refined_triangulation)
  .def("GetInstance", &MeshGeneration::GetInstance);

 return mod.ptr();
  
}



