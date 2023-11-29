/*
21.11.23:

Topological sort
Application of BFS, DFS
Minimum spanning trees

Dynamic programming:
 - often asked to minimise or maximise a property
 - but also often the return value is not that minimum or maximum it's a state of the problem that produces that min or max

I wasn't paying any attention
Minium spanning trees, it's like a subgraph that goes from node A to node B
actually that might be wrong I don't exactly know

Topological sort:
So it takes in a directed graph and returns
an array of nodes where each node comes before the last one
thats hard to explain so if the graph was this


A -> B -> C
|    |
V    V
D -> F

Then a valid top sort return would be
[A, B, D, C, F]
or
[A, D, B, F, C]

there are often multiple correct outputs to a topological sort of a given graph
also topological sort cannot be applied to graphs with one or more cycles

Strongly connected components can be collapsed into one vertex
strongly connected means that from any node in the component, you can get to any other node
so really you can do topological sort with cycles in graphs, as long as you collapse
the cycles into a single vertex

Kruskal's algorithm
 - We grow a minimum spanning tree as a collection of smaller trees
 - Create a forest
 - repeatedly select the lowest weight edge that joins disconnected trees in the forest

We create a tree that SPANS the graph built out of only the smallest edges
we just keep adding edges until we know all of the nodes are connected
we also don't add edges between already connected trees

Okay so a minimum spanning tree means ???
I guess it means we just get rid of some of the edges
we make sure all nodes are still connected to all others (that were before)

Oh so the goal of a minimum spanning tree is that if you add up all the edge weights
it's the smallest that it can be to still span the whole graph

So we want all nodes to be connected with the shortest cumulative edge weights

Prim's algorithm
 - here's the sudo code

PRIM(G, w, r) (G - graph, w - weights list, r - root node)
    for each vertex in G
        vertex.key = inf
        vertex.pred = NULL
    r.key = 0
    let Q be a Priority Queue (min heap)
    Q.append(r)
    while (!Q.isEmpty())
        u = EXTRACT-MIN(Q) // pops off of Q and returns the min value in Q
        for each vertex in G.adjlist[u]
            if vertex is in Q and w[u][vertex] < vertex.key
                vertex.pred = u
                v.key = w[u][vertex]

I don't even know what this returns
oh I guess it just mutates the graph into a min span graph

So also this only spans the area that r is connected to, so if theres disconnected segments
then it won't get those i mean you can't span over there anyway

both of their runtimes are "similar"
no concrete runtimes (?)

it depends on how you set up your data structures

kruskal's algorithm also depends on what data structure you use, but a disjoint set forest is
a popular choice which yields a runtime of idfk she didn't say

but both are about O(|E| lg |V|)
idk what E or V is
oh its probably edges and vertices, number of

*/

int main(int argc, char *argv[]) {

}