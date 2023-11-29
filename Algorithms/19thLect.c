/*
14.11.23:

LEFTMOST(n):
    if n == NULL
        ERROR
    if n.left == NULL
        retrieval 

whatever man

Today we did graphs
there are three ways to represent graphs
you can represent with a list of nodes and a list of connections

you can represent with a matrix
 - which is like you have a numNodes * numNodes matrix and just put a 1 if there is a connection between and a 0 if not
 - so you only need a triangle actually but if its directed then you need the whole matrix

you can represent with an adjacentcy list
 - which is like each node gets a list which has the nodes that it is adjacent to in the lists


lets do Breadthe first search.
BFS(G, source) - where G is an adjacentcy list of the graph, and s is a starting node
    for every vertex in G
        vertex.color = WHITE
        vertex.distance = inf // distance from source (we wanna find the shortest distance)
        vertex.predecessor = NULL // predecessor (???)
    source.color = GREY
    source.distance = 0
    source.predecessor = NULL
    queue = new priorityQueue // all places exploring (???)
    queue.add(source) // add source to places exploring
    while (!queue.isEmpty())
        explore = queue.remove() // remove since we're done with this one (btw it's sorted by distance, but also btw this makes no difference (for BFS at least))
        for every vertex in explore.adjacent
            if (vertex.color == WHITE) // if we haven't seen this guy yet
                vertex.color = GREY // SEEN
                vertex.distance = explore.distance + 1 // distance from source updated via predecessor
                vertex.predecessor = explore // came from explore
                queue.add(vertex)
        explore.color = BLACK // symbolises that we have put each of the adjacent vertices in the queue (not needed)
    // once we get here we have visited all reachable nodes from the source node

This feels like djikstra but with every node weight is 1
this also also feels like djikstra because i think this is the dijkstra implementation of BFS
*/

#include <stdio.h>

int main(int argc, char *argv[]) {

}