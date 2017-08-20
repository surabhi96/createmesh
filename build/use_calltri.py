import createmesh

mod=createmesh.Meshgeneration()

mod.input_polygon_vertices([[0.0, 0.0], [3.0, 0.0], [3.0, 3.0], [0.0, 3.0]])

mod.input_holes([ [[1.0, 1.0],[1.0, 2.0],[2.0, 2.0],[2.0, 1.0]] ], [1.5, 1.5])

mod.basic_triangulation(1)   

mod.refined_triangulation(1) 

ans = createmesh.Meshgeneration()  

ans = mod.GetInstance()        

l = ans.pointlist()  

print(l)


