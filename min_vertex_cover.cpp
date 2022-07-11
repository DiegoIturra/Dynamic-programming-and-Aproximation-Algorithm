#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <algorithm>

using namespace std;


//Nodos van desde posicion [0...N-1] para simplicidad del ejercicio
class Graph{
	private:
		int numVertex;
		vector<unordered_set<int> > graph; //lista de adyacencia
		vector<bool> visited;


		//Verifica que todas las incidencias esten vacias , si hay al menos una que contenga un vertice
		//Entonces devolver false
		bool isEmpty(vector<unordered_set<int> >& edges){
			for(int i=0 ; i<edges.size() ; i++){
				if(!edges[i].empty()){
					return false;
				}
			}
			return true;
		}

	public:
		Graph(const int numVertex){
			this->numVertex = numVertex;
			this->graph.resize(numVertex);
			this->visited.resize(numVertex,false);
		}


		void addEdge(const int u, const int v){
			if(u == v || u >= numVertex || v >= numVertex || u < 0 || v < 0)
				return;
			this->graph[u].insert(v);
			this->graph[v].insert(u);
		}


		void printGraph(){
			unordered_set<int>::iterator it;
			for(int i=0 ; i<graph.size() ; i++){
				cout << "Vertex " << i << " -> ";
				for(it = graph[i].begin() ; it != graph[i].end() ; it++){
					cout << *it << " ";
				}
				cout << endl;
			}
			cout << endl;
		}

		void aproxVertexCover(){
			unordered_set<int> coveredSet; //C
			vector<unordered_set<int> > uncoveredEdges = this->graph; //E

			int iterations = 0;

			while(!isEmpty(uncoveredEdges)){
				++iterations;
				//Tomar una arista cualquiera (u,v) de uncoveredEdges
				int u = -1;
				int v = -1;

				//mientras existan valores de (u,v) validos reintentar
				for(int i=0 ; i<numVertex ; i++){
					if(!visited[i]){
						u = i;
						visited[u] = true;

						//Verificar que al menos tenga un vecino al cual escoger
						if(!uncoveredEdges[u].empty()){
							v = *(uncoveredEdges[i].begin());
							visited[v] = true;
							break;
						}else{
							continue;
						}
					}
				}					


				cout << "Arista tomada: (" << u << "," << v << ")" << endl;


				//insertar arista (u,v) en coveredSet y eliminarla de uncoveredEdges
				coveredSet.insert(u);
				coveredSet.insert(v);
				uncoveredEdges[u].clear();
				uncoveredEdges[v].clear(); //Elimina adyacencia directa desde los vertices u,v

				//remover aristas incidentes tanto como a 'u' y a 'v' de uncoveredEdges
				for(int i=0 ; i<numVertex ; i++){
					if(!visited[i]){
						unordered_set<int>::iterator it;
						for(it = graph[i].begin() ; it != graph[i].end() ; it++){
							if(*it == u || *it == v){
								uncoveredEdges[i].erase(*it);
							}
						}
					}
				}
			}

			cout << "Numero de vertices en 2-aprox vertex cover: " << coveredSet.size() << endl;
		}
};



int main(){

	int numVertex = 7;
	
	//Ejemplo con vertex cover 2-aproximado = 6 y valor optimo = 3
	Graph graph1 = Graph(numVertex);
	graph1.addEdge(0,1);
	graph1.addEdge(1,2);
	graph1.addEdge(2,3);
	graph1.addEdge(2,4);
	graph1.addEdge(3,4);
	graph1.addEdge(4,5);
	graph1.addEdge(3,6);

	graph1.printGraph();
	graph1.aproxVertexCover();


	//Ejemplo en el cual vertex cover 2-aproximado = optimo con numero de vertices igual a 2
	numVertex = 6;
	Graph graph2 = Graph(numVertex);
	graph2.addEdge(0,1);
	graph2.addEdge(0,2);
	graph2.addEdge(0,3);
	graph2.addEdge(0,4);
	graph2.addEdge(0,5);
	graph2.printGraph();
	graph2.aproxVertexCover();
	


	//Cliques
	int numCliques = 5;
	numVertex = 11;
	
	int sizeOfclique;

	Graph graph = Graph(numVertex);

	while(numCliques--){

		//cout << "tamaño de clique: ";
		cin >> sizeOfclique;

		vector<int> setOfClique;
		int vertex;
		while(sizeOfclique--){
			//cout << "Elementos en clique: ";
			cin >> vertex;
			setOfClique.push_back(vertex);
		}

		for(int i=0 ; i<setOfClique.size() ; i++){
			for(int j=0 ; j<setOfClique.size() ; j++){
				if(setOfClique[i] != setOfClique[j]){
					graph.addEdge(setOfClique[i],setOfClique[j]);
				}
			}
		}
	}

	graph.printGraph();
	graph.aproxVertexCover();

	return 0;
}