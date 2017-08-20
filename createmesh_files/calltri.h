#ifndef CALLTRI_H 
#define CALLTRI_H

/* If SINGLE is defined when triangle.o is compiled, it should also be       */
/*   defined here.  If not, it should not be defined here.                   */

/* #define SINGLE */
#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif /* not SINGLE */


#include <iostream>
#include <vector>
#define ANSI_DECLARATORS
#include <stdio.h>

extern "C" {
#include "triangle.h"
}

class MeshGeneration {
 
 struct triangulateio in, mid, out, vorout;

 public:

  MeshGeneration();

  void input_polygon_vertices( std::vector< std::vector<REAL> >);
  void input_holes(std::vector< std::vector< std::vector<REAL> > >, std::vector<REAL> );
  void input_pointattributelist( int, std::vector<REAL> );
  void input_pointmarkerlist( std::vector<int> );
  //void input_segmentmarkerlist( std::vector<REAL> );
  void input_regionlist( int, std::vector<REAL> );
  void basic_triangulation(bool);
  void tri_areaconstraintlist(std::vector<REAL>);
  void refined_triangulation(bool);
  struct triangulateio GetInstance();
  void report(struct triangulateio *io, int markers, int reporttriangles, int reportneighbors, int reportsegments,
             int reportedges, int reportnorms);
  template<class var>
  void assign(std::vector<var>, var *); 

  ~MeshGeneration();

};

#endif

