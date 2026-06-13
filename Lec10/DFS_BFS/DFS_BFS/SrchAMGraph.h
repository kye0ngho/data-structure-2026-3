#pragma once
#include "AdjMatGraph.h"
#include "CircularQueue.h"

class SrchAMGraph : public AdjMatGraph {
    bool visited[MAX_VTXS];
public:
    void resetVisited() {
        for (int i = 0; i < MAX_VTXS; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }
    void DFS(int v) {
        visited[v] = true;
        printf("%c ", getVertex(v));
        for (int w = 0; w < size; w++) {
            if (isLinked(v, w) && !visited[w])
                DFS(w);
        }
    }
    void BFS(int v) {
        CircularQueue Q;
        visited[v] = true;
        printf("%c ", getVertex(v));
        Q.enqueue(v);
        while (!Q.isEmpty()) {
            int u = Q.dequeue();
            for (int w = 0; w < size; w++) {
                if (isLinked(u, w) && !visited[w]) {
                    visited[w] = true;
                    printf("%c ", getVertex(w));
                    Q.enqueue(w);
                }
            }
        }
    }
};
