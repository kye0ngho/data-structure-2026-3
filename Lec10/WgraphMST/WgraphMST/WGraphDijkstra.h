#pragma once
#include "WGraphMST.h"

class WGraphDijkstra : public WGraph {
private:
    int dist[MAX_VTXS];
    bool found[MAX_VTXS];

public:
    int chooseVertex() {
        int minDist = INF;
        int minPos = -1;

        for (int i = 0; i < size; i++) {
            if (!found[i] && dist[i] < minDist) {
                minDist = dist[i];
                minPos = i;
            }
        }

        return minPos;
    }

    void printDistance() {
        for (int i = 0; i < size; i++) {
            if (dist[i] >= INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << dist[i];
        }
        cout << endl;
    }

    void ShortestPath(int start) {
        for (int i = 0; i < size; i++) {
            dist[i] = getEdge(start, i);
            found[i] = false;
        }

        found[start] = true;
        dist[start] = 0;

        for (int i = 0; i < size - 1; i++) {
            cout << "step" << setw(2) << i + 1 << ":";
            printDistance();

            int u = chooseVertex();

            if (u == -1)
                break;

            found[u] = true;

            for (int w = 0; w < size; w++) {
                if (!found[w] && getEdge(u, w) < INF) {
                    if (dist[u] + getEdge(u, w) < dist[w]) {
                        dist[w] = dist[u] + getEdge(u, w);
                    }
                }
            }
        }

        cout << "Final :";
        printDistance();
    }
};
