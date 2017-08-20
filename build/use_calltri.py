import createmesh  

# set degug = 0 if you do not want to print the output of triangulation 
debug = 1
mod = createmesh.Meshgeneration() 
ans = createmesh.Meshgeneration() 

# polygon vertices in counter clockwise direction 
mod.input_polygon_vertices([[0.0, 0.0], [3.0, 0.0], [3.0, 3.0], [0.0, 3.0]])

# hole vertices in clockwise direction 
mod.input_holes([ [[1.0, 1.0],[1.0, 2.0],[2.0, 2.0],[2.0, 1.0]] ], [1.5, 1.5])

mod.basic_triangulation(debug)   

mod.refined_triangulation(debug) 

ans = mod.GetInstance()        

l = ans.pointlist()  

print(l)

