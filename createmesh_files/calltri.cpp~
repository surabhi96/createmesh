#include "calltri.h"

MeshGeneration::MeshGeneration() {

  in.numberofpoints = 0;
  in.pointlist = nullptr;
  in.numberofholes = 0;
  in.holelist = nullptr;
  in.segmentlist = nullptr;
  in.pointattributelist = nullptr;
  in.numberofpointattributes = 0;
  in.pointmarkerlist = nullptr;
  in.segmentmarkerlist = nullptr;
  in.regionlist = nullptr;
  in.numberofregions = 0;
  in.numberofsegments = 0;

  mid.pointlist = nullptr;             /* Not needed if -N switch used. */
  mid.pointattributelist = nullptr;    /* Not needed if -N switch used or number of point attributes is zero: */
  mid.pointmarkerlist = nullptr;       /* Not needed if -N or -B switch used. */
  mid.trianglelist = nullptr;          /* Not needed if -E switch used. */
  mid.triangleattributelist = nullptr; /* Not needed if -E switch used or number of triangle attributes is zero: */
  mid.neighborlist = nullptr;          /* Needed only if -n switch used. */
  mid.segmentlist = nullptr;           /* Needed only if segments are output (-p or -c) and -P not used: */
  mid.segmentmarkerlist = nullptr;     /* Needed only if segments are output (-p or -c) and -P and -B not used: */
  mid.edgelist = nullptr;              /* Needed only if -e switch used. */
  mid.edgemarkerlist = nullptr;        /* Needed if -e used and -B not used. */
  mid.trianglearealist = nullptr;

  vorout.pointlist = nullptr;          /* Needed only if -v switch used. */
  vorout.pointattributelist = nullptr; /* Needed only if -v switch used and number of attributes is not zero: */
  vorout.edgelist = nullptr;           /* Needed only if -v switch used. */
  vorout.normlist = nullptr;           /* Needed only if -v switch used. */

  /* Make necessary initializations so that Triangle can return a triangulation in `out'. */                                   

  out.pointlist = nullptr;             /* Not needed if -N switch used. */
  out.pointattributelist = nullptr;    /* Not needed if -N switch used or number of attributes is zero: */ 
  out.trianglelist = nullptr;          /* Not needed if -E switch used. */
  out.triangleattributelist = nullptr; /* Not needed if -E switch used or number of triangle attributes is zero: */ 
}

void MeshGeneration::input_polygon_vertices( std::vector< std::vector<REAL> > PolygonVertices ) {

  std::vector<REAL> PointList;
  for (int i = 0; i < PolygonVertices.size(); i++) {
    for (int j = 0; j < 2; j++)
      PointList.push_back(PolygonVertices[i][j]);
  }

  in.numberofpoints = PointList.size()/2;
  in.pointlist = new REAL[in.numberofpoints * 2];
  assign(PointList, in.pointlist);
}

void MeshGeneration::input_holes(std::vector< std::vector< std::vector<REAL> > > InputHoles,  
                                 std::vector<REAL> HoleList) { 

  size_t prev_size = in.numberofpoints * 2;
  in.numberofholes = InputHoles.size();
  std::vector<REAL> HoleVertices;
  std::vector<int> SegmentList;
  for (int i = 0; i < InputHoles.size(); i++) {
    for (int j = 0; j < InputHoles[0].size(); j++) {
      SegmentList.push_back(in.numberofpoints + j);
      if (j < InputHoles[0].size() - 1) 
        SegmentList.push_back(in.numberofpoints + j + 1);
      else
        SegmentList.push_back(in.numberofpoints);
      for (int k = 0; k < 2; k++) 
        HoleVertices.push_back(InputHoles[i][j][k]);
    }
  }
  
  REAL * temp = new REAL[prev_size + HoleVertices.size()];
  for (size_t s = 0; s < prev_size; s++)
    *(temp+s) = *(in.pointlist+s);
  for (size_t s = 0; s < HoleVertices.size(); s++)
    *(temp+s+prev_size) = HoleVertices[s];
  delete [] in.pointlist;
  in.pointlist = temp;
  temp = nullptr;
  in.numberofpoints += HoleVertices.size()/2;
  
  in.holelist = new REAL[in.numberofholes * 2];
  assign(HoleList, in.holelist);

  in.numberofsegments = SegmentList.size()/2;
  in.segmentlist = new int[in.numberofsegments * 2];
  assign(SegmentList, in.segmentlist);
}

void MeshGeneration::input_pointattributelist( int NumberofPointAttributes, std::vector<REAL> PointAttributeList ) {

  in.numberofpointattributes = NumberofPointAttributes; 
  in.pointattributelist = new REAL[in.numberofpoints * in.numberofpointattributes];
  assign(PointAttributeList, in.pointattributelist);
}

void MeshGeneration::input_pointmarkerlist( std::vector<int> PointMarkerList ) {

  in.pointmarkerlist = new int[in.numberofpoints];
  assign(PointMarkerList, in.pointmarkerlist);
}
/*
void MeshGeneration::input_segmentmarkerlist( std::vector<REAL> SegmentMarkerList ) {

  in.segmentmarkerlist = new int[in.numberofsegments];
  assign(SegmentMarkerList, in.segmentmarkerlist);   
}
*/
void MeshGeneration::input_regionlist(int NumberofRegions, std::vector<REAL> RegionList ) {

  in.numberofregions = NumberofRegions;
  in.regionlist = new REAL[in.numberofregions * 4];
  assign(RegionList, in.regionlist);
}

void MeshGeneration::basic_triangulation(bool DEBUG) {
 
  /*   Triangulate the points.  Switches are chosen to read and write a  */
  /*   PSLG (p), preserve the edges of convex hull (c), number everything from  */
  /*   zero (z),  assigns a regional attribute to each triangle that identifies what segment-bounded region it belongs to.  (A), and  */
  /*   produce an edge list of triangulation (e), a Voronoi diagram (v), and a triangle */
  /*   neighbor list(a list of triangles neighbouring each triangle) (n). */

  triangulate("pczevnBQ", &in, &mid, &vorout); /* add -B switch if you are not considering pointmarkerlist --- pczevnBQ*/
  if (DEBUG) {
    std::cout << "Input point set: "<< '\n';
    report(&in, 0, 0, 0, 0, 0, 0); /* set second argument to 0 if you aren't considering pointmarkerlist */
    std::cout << "Initial triangulation:" << '\n';
    report(&mid, 0, 1, 1, 1, 1, 0);
    std::cout << "Initial Voronoi diagram: " << '\n';
    report(&vorout, 0, 0, 0, 0, 1, 1);
  }
  
 // return mid;
}


void MeshGeneration::tri_areaconstraintlist(std::vector<REAL> TriangleAreaList) {
  /* Attach area constraints to the triangles in preparation for refining the triangulation */   
  /* Set in.trianglearealist to nullptr if you don't want to consider trianglearealist and  */
  /* remove -a switch in the triangulate function call.                                     */ 
    
  mid.trianglearealist = new REAL[mid.numberoftriangles]; 
  assign(TriangleAreaList, mid.trianglearealist);
}

void MeshGeneration::refined_triangulation(bool DEBUG) {

  /* Refine the triangulation according to the attached */ 
  /* triangle area constraints.                         */

  triangulate("pqrzBPQ", &mid, &out, nullptr);  /* Remove -a switch if you are not considering trianglearealist---przBPQ */

  if (DEBUG) {
    std::cout << "Refined triangulation: " << '\n';
    report(&out, 0, 1, 0, 0, 0, 0);
  }

  //return out;
}

struct triangulateio MeshGeneration::GetInstance() {
  return out;
}

template<class var>
void MeshGeneration::assign(std::vector<var> initialisedlist, var * inputlist) {
  for (size_t i = 0; i < initialisedlist.size(); i++) {
      *(inputlist+i) = initialisedlist[i]; 
  }
}

void MeshGeneration::report(struct triangulateio *io, int markers, int reporttriangles, int reportneighbors, int reportsegments,
            int reportedges, int reportnorms)
{
  int i, j;

  for (i = 0; i < io->numberofpoints; i++) {
    std::cout << "Point :" << i << "     ";
    for (j = 0; j < 2; j++) {
      std::cout << io->pointlist[i * 2 + j] << "     ";
    }
    if (io->numberofpointattributes > 0) {
      std::cout << "   attributes :";
    }
    for (j = 0; j < io->numberofpointattributes; j++) {
      std::cout << io->pointattributelist[i * io->numberofpointattributes + j];
    }
    if (markers) {
      std::cout << "   marker :" << io->pointmarkerlist[i] << '\n';
    } else {
      std::cout << '\n';
    }
  }
  std::cout << "\n";

  if (reporttriangles || reportneighbors) {
    for (i = 0; i < io->numberoftriangles; i++) {
      if (reporttriangles) {
        std::cout << "Triangle :" << i << " points:";
        for (j = 0; j < io->numberofcorners; j++) {
          std::cout << "    " << io->pointlist[2 * (io->trianglelist[i * io->numberofcorners + j]) + 0];
          std::cout << "    " << io->pointlist[2 * (io->trianglelist[i * io->numberofcorners + j]) + 1];
        }
        if (io->numberoftriangleattributes > 0) {
          std::cout << "   attributes";
        }
        for (j = 0; j < io->numberoftriangleattributes; j++) {
          std::cout << "     " << io->triangleattributelist[i * io->numberoftriangleattributes + j];                                        
        }
        std::cout << "\n";
      }
      if (reportneighbors) {
        std::cout << "Triangle " << i << "  " << " neighbors:";
        for (j = 0; j < 3; j++) {
          std::cout << "    " << io->neighborlist[i * 3 + j];
        }
        std::cout << "\n";
      }
    }
    std::cout << "\n";
  }

  if (reportsegments) {
    for (i = 0; i < io->numberofsegments; i++) {
      std::cout << "Segment " << " " << i << " " << "points: ";
      for (j = 0; j < 2; j++) {
        std::cout << "    " << io->segmentlist[i * 2 + j];
      }
      if (markers) {
        std::cout << "   marker" << io->segmentmarkerlist[i] << '\n';
      } else {
        std::cout << "\n";
      }
    }
    std::cout << "\n";
  }

  if (reportedges) {
    for (i = 0; i < io->numberofedges; i++) {
      std::cout << "Edge " << i << "  points:";
      for (j = 0; j < 2; j++) {
        std::cout << "    " << io->edgelist[i * 2 + j];
      }
      if (reportnorms && (io->edgelist[i * 2 + 1] == -1)) {
        for (j = 0; j < 2; j++) {
          std::cout << "    ", io->normlist[i * 2 + j];
        }
      }
      if (markers) {
        std::cout << "   marker: " << io->edgemarkerlist[i] << '\n';
      } else {
        std::cout << "\n";
      }
    }
    std::cout << "\n";
  }
}

MeshGeneration::~MeshGeneration() {
  
  /* delete all allocated arrays, including those allocated by Triangle. */

  delete [] in.pointlist;
  delete [] in.pointattributelist;
  delete [] in.pointmarkerlist;
  delete [] in.holelist;
  delete [] in.regionlist;
  delete [] in.segmentlist;
  delete [] in.segmentmarkerlist;
  free(mid.pointlist);
  free(mid.pointattributelist);
  free(mid.pointmarkerlist);
  free(mid.trianglelist);
  free(mid.triangleattributelist);
  free(mid.trianglearealist);
  free(mid.neighborlist);
  free(mid.segmentlist);
  free(mid.segmentmarkerlist);
  free(mid.edgelist);
  free(mid.edgemarkerlist);
  free(vorout.pointlist);
  free(vorout.pointattributelist);
  free(vorout.edgelist);
  free(vorout.normlist);
  free(out.pointlist);
  free(out.pointattributelist);
  free(out.trianglelist);
  free(out.triangleattributelist);

}

