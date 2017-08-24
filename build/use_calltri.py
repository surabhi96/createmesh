import createmesh  

# set degug = 0 if you do not want to print the output of triangulation 
debug = 1
mod = createmesh.Meshgeneration() 
ans = createmesh.Meshgeneration() 

# polygon vertices in counter clockwise order
mod.input_polygon_vertices([[0.0, 0.0], [3.0, 0.0], [3.0, 3.0], [0.0, 3.0]])

# Input hole vertices as first argument and any point inside a hole as the second 
# argument of the function. Hole vertices are to be given in clockwise order.
# Each hole is described by the vertices in a list of list and all the holes 
# vertices are enclosed within a list of list of lists. Mention any random point 
# inside every hole as a list of lists.
mod.input_holes([ [[1.0, 1.0],[1.0, 2.0],[2.0, 2.0],[2.0, 1.0]] ], [ [1.5, 1.5] ])

mod.basic_triangulation(debug)   

mod.refined_triangulation(debug) 

ans = mod.GetInstance()        

l = ans.pointlist()  

print(l)



