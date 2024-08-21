#include <iostream>
#include <string>

using namespace std;

#define INF 99999

template <typename T>
/* class Graph{
public:
	Graph(const vector<T>& nodes) : nodes(nodes) {
		int n = nodes.size();
		adjMatrix.resize(n, vector<int>(n, numeric_limits<int>::max()));
		for (int i = 0; i < n; ++i) {
			adjMatrix[i][i] = 0; // Distancia del nodo a sí mismo es 0
		}
	} aguantae la prada
}; */

void printSolution(int** dist, int V, int** local, string* nameLocations)
{
	cout << "The following matrix shows the shortest "
		"distances"
		" between every pair of vertices \n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
				<< " ";
			else
				cout << dist[i][j] << "   ";
		}
		cout << endl;
	}


	// Imprimir matriz locations
	cout << "La matriz de recorrido es: " << endl;
	int aux = 0;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			aux = local[i][j];
			cout << nameLocations[aux - 1] << " ";
		}
		cout << endl;
	}
}


void dijkstra(int src, int finalNode, int** graph, int V, string* nameLocations) {
	// Declaración de arrays necesarios para la lógica
	int* finalDistance = new int[V];
	bool* visited = new bool[V];

	// Inicialización de arrays
	for (int i = 0; i < V; i++) {
		finalDistance[i] = INF;
		visited[i] = false;
	}

	// Inicialización nodo 0
	finalDistance[src] = 0;

	bool finished = false;

	int u = src;

	while (!finished) {
		int minDist = INF;

		// Localizar el nodo de menor distancia temporal de los nodos no visitados
		for (int i = 0; i < V; i++) {
			if (!visited[i] && finalDistance[i] < minDist && finalDistance[i]) {
				minDist = finalDistance[i];
				u = i;
			}
		}

		// Confirmar distancia final de u
		visited[u] = true;

		// Actualizar distancia temporal de nodos adyacentes aún no visitados
		for (int i = 0; i < V; i++) {
			if (graph[u][i] != INF && !visited[i]) {
				if (finalDistance[i] > finalDistance[u] + graph[u][i]) {
					finalDistance[i] = finalDistance[u] + graph[u][i];
				}
			}
		}

		// Verificar si ya se visitaron todos los nodos
		finished = true; // Suponemos que hemos terminado
		for (int i = 0; i < V; i++) {
			if (!visited[i]) { // Si hay un nodo no visitado, continuamos
				finished = false;
				break;
			}
		}
	}

	// Imprimir distancia de nodo raiz seleccionado, a nodo final seleccionado
	cout << "Distancia final a la ciudad seleccionada" << endl;
	cout << nameLocations[src] << "->" << nameLocations[finalNode] << ": " << finalDistance[finalNode] << endl;

	// Falta agregar:
	// Verificacion de indices que ingresa el usuario para que sean validos (insercion en el main)
	// Resta para conocer el recorrido que se hace para obtener la distancia minima entre src y finalNode

	// Imprimir las distancias finales desde el nodo 0
	cout << "Distancias finales desde la ciudad " << nameLocations[src] << " al resto de ciudades." << endl;
	for (int i = 0; i < V; i++) {
		cout << nameLocations[i] << "->" << finalDistance[i] << endl;
	}

	// Liberar memoria
	delete[] finalDistance;
	delete[] visited;
}


int main() {
	// Se pide al usuario ingresar cantidad de nodos
	int nodes;
	cout << "Ingrese la cantidad de nodos: ";
	cin >> nodes;

	int** graph = new int* [nodes];
	// Declaracion de la matriz
	for (int i = 0; i < nodes; i++) {
		graph[i] = new int[nodes];
	}

	string* nameLocations = new string[nodes];
	for (int i = 0; i < nodes; i++) {
		cout << "Ingrese el nombre de la ciudad " << i << endl;
		cin >> nameLocations[i];
	}


	// Inicializar matriz con valores 0
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			graph[i][j] = 0;
		}
	}

	// Llenar la matriz por encima de la diagonal principal

	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			if (i != j)
			{
				if (graph[i][j] == 0)
				{
					int distancia;
					cout << "Ingrese la distancia entre el nodo " << nameLocations[i] << " y el nodo " << nameLocations[j] << ": ";
					cin >> distancia;
					if (distancia == 0)
					{
						graph[i][j] = INF;
						graph[j][i] = INF;
					}
					else
					{
						graph[i][j] = distancia;
						graph[j][i] = distancia;
					}
				}
			}
		}
	}
	// imprimir graph
	int finalNode = 0, src = 0;

	cout << "Indica el indice de tu nodo raiz" << endl;
	cin >> src;
	cout << "Indica el indice del nodo final" << endl;
	cin >> finalNode;
	
	dijkstra(src, finalNode, graph, nodes, nameLocations);

	return 0;
}
	