#include "WGraphDijkstra.h"

int main() {
    WGraphMST g;
    g.load("wgraph.txt");
    g.display("Weighted Graph");

    cout << "MST By Kruskal's Algorithm" << endl;
    g.Kruskal();

    cout << "\nMST By Prim's Algorithm (from A):" << endl;
    g.Prim(0);

    WGraphDijkstra dg;
    dg.load("wgraph.txt");
    cout << "\nShortest Path from A:" << endl;
    dg.ShortestPath(0);

    return 0;
}
