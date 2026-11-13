#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

char huruf(int i) {
    return 'A' + i;
}

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void printAdjMatrix() {
        cout << "  ";
        for (int i = 0; i < V; i++) {
            cout << huruf(i) << " ";
        }
        cout << endl;
        for (int i = 0; i < V; i++) {
            cout << huruf(i) << " ";
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bfs(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> titikVisit;

        visited[startVertex] = true;
        titikVisit.push(startVertex);

        while (!titikVisit.empty()) {
            int currentVertex = titikVisit.front();
            titikVisit.pop();
            cout << huruf(currentVertex) << " ";

            for (int i = 0; i < V; i++) {
                if (adjMatrix[currentVertex][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    titikVisit.push(i);
                }
            }
        }
        cout << endl;
    }

    void dfs(int startVertex) {
        vector<bool> visited(V, false);
        dfsUntil(startVertex, visited);
        cout << endl;
    }

    void dfsUntil(int currentVertex, vector<bool>& visited) {
        visited[currentVertex] = true;
        cout << huruf(currentVertex) << " ";

        for (int i = 0; i < V; i++) {
            if (adjMatrix[currentVertex][i] != 0 && !visited[i]) {
                dfsUntil(i, visited);
            }
        }
    }

    void dijkstra(int source, int tujuan) {
        vector<int> distance(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> visited(V, false);
        distance[source] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    int newDistance = distance[u] + adjMatrix[u][v];

                    if (newDistance < distance[v]) {
                        distance[v] = newDistance;
                        parent[v] = u;
                    }
                }
            }
        }

        cout << "Jarak terpendek dari " << huruf(source) << " :" << endl;
        for (int i = 0; i < V; i++) {
            if (distance[i] == INT_MAX)
                cout << huruf(i) << " : Tidak terjangkau" << endl;
            else
                cout << huruf(i) << " : " << distance[i] << endl;
        }

        cout << "--------------------" << endl;
        if (distance[tujuan] == INT_MAX) {
            cout << "Tujuan tidak terjangkau" << endl;
            return;
        }

        vector<int> rute;
        for (int v = tujuan; v != -1; v = parent[v]) {
            rute.push_back(v);
        }

        cout << "Rute         : ";
        for (int i = rute.size() - 1; i >= 0; i--) {
            cout << huruf(rute[i]);
            if (i > 0) cout << " -> ";
        }
        cout << endl;
        cout << "Total jarak  : " << distance[tujuan] << endl;
    }
};

int main() {
    Graph graph(6);

    // A=0, B=1, C=2, D=3, E=4, F=5
    graph.addEdge(0, 1, 4);   // A-B
    graph.addEdge(0, 2, 2);   // A-C
    graph.addEdge(1, 2, 1);   // B-C
    graph.addEdge(1, 3, 5);   // B-D
    graph.addEdge(1, 4, 3);   // B-E
    graph.addEdge(2, 3, 8);   // C-D
    graph.addEdge(2, 4, 6);   // C-E
    graph.addEdge(3, 4, 2);   // D-E
    graph.addEdge(3, 5, 4);   // D-F
    graph.addEdge(4, 5, 3);   // E-F

    cout << "=== ADJACENCY MATRIX ===" << endl;
    graph.printAdjMatrix();

    char awal, akhir;
    cout << endl << "=== INPUT RUTE ===" << endl;
    cout << "Lokasi (A-F)" << endl;
    cout << "Vertex awal   : ";
    cin >> awal;
    cout << "Vertex tujuan : ";
    cin >> akhir;

    if (awal >= 'a' && awal <= 'f') awal = awal - 32;
    if (akhir >= 'a' && akhir <= 'f') akhir = akhir - 32;

    if (awal < 'A' || awal > 'F' || akhir < 'A' || akhir > 'F') {
        cout << "Vertex tidak valid" << endl;
        return 0;
    }

    int start = awal - 'A';
    int tujuan = akhir - 'A';

    cout << endl << "=== BFS dari " << awal << " ===" << endl;
    graph.bfs(start);

    cout << endl << "=== DFS dari " << awal << " ===" << endl;
    graph.dfs(start);

    cout << endl << "=== DIJKSTRA " << awal << " ke " << akhir << " ===" << endl;
    graph.dijkstra(start, tujuan);

}