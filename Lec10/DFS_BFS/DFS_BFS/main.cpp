#include "SrchAMGraph.h"

int main() {
    SrchAMGraph g;
    g.load("graph.txt");

    printf("\n-- 인접 행렬 --\n");
    g.display();

    printf("\nDFS 탐색: ");
    g.resetVisited();
    g.DFS(0);
    printf("\n");

    printf("BFS 탐색: ");
    g.resetVisited();
    g.BFS(0);
    printf("\n");

    return 0;
}
