#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <algorithm>

using namespace std;

struct hashFunction{
	bool operator()(const pair<int,int>& other) const{
		return other.first && other.second;
	}
};

//Nodos van desde posicion [0...N-1] para simplicidad del ejercicio
class Graph{
	private:
		int numVertex;
		vector<unordered_set<int> > graph;
		unordered_set< pair<int,int> , hashFunction> setOfEdges;

	public:
		Graph(const int numVertex){
			this->numVertex = numVertex;
			this->graph.resize(numVertex);
		}

		void addEdge(const int u, const int v){
			if(u == v || u >= numVertex || v >= numVertex || u < 0 || v < 0)
				return;
			this->graph[u].insert(v);
			this->graph[v].insert(u);
			this->setOfEdges.insert(make_pair(u,v));
			this->setOfEdges.insert(make_pair(v,u));
		}

		void removeEdge(int u , int v){
			if(u == v || u >= numVertex || v >= numVertex || u < 0 || v < 0)
				return;
			this->graph[u].erase(v);
			this->graph[v].erase(u);
			this->setOfEdges.erase(make_pair(u,v));
			this->setOfEdges.erase(make_pair(v,u));
		}

		void printEdges(){
			unordered_set<pair<int,int> , hashFunction>::iterator it;
			for(it = setOfEdges.begin() ; it != setOfEdges.end() ; it++){
				cout << "(" << it->first << "," << it->second << ")" << endl;
			}
			cout << endl;
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
};



int main(){

	int numVertex = 5;
	Graph graph = Graph(numVertex);

	graph.addEdge(0,1);
	graph.addEdge(0,2);
	graph.addEdge(0,3);
	graph.addEdge(0,4);
	graph.addEdge(1,2);
	graph.addEdge(2,3);
	graph.addEdge(3,4);

	graph.printGraph();
	graph.printEdges();


	return 0;
}