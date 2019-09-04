#include "ADT_graph.h"  
/* #include "hello.h"  */
#include <iostream>
#include <string>

// Additionally included header file
#include <fstream>
#include <sstream>
#include <limits>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>

using namespace std;

bool operator<(const ADT_Node<int>& vertex1, const ADT_Node<int>& vertex2) {

	if (vertex1.get_node_value() < vertex2.get_node_value()) {
		return true;
	}

	if (vertex1.get_node_value() == vertex2.get_node_value()) {
		if (vertex1.get_node_name().compare(vertex2.get_node_name()) < 0) {
			return true;
		}
	}

	return false;
}

bool operator>(const ADT_Node<int>& vertex1, const ADT_Node<int>& vertex2) {

	if (vertex1.get_node_value() > vertex2.get_node_value()) {
		return true;
	}

	if (vertex1.get_node_value() == vertex2.get_node_value()) {
		if (vertex1.get_node_name().compare(vertex2.get_node_name()) > 0) {
			return true;
		}
	}

	return false;
}

// G: Pointer to the input graph, vertex: source node
int dijkstra(ADT_Graph<int>* G, string vertex) {

	if ((G->get_ADT_nodelist()).search_vertex(vertex) == NULL) {
		cout << "There's no such vertex in the graph" << endl;
		return 0;
	}

	// D[u] Initialization
	(G->get_ADT_nodelist()).set_all_node_value(numeric_limits<int>::max());
	(G->get_ADT_nodelist()).search_vertex(vertex)->set_node_value(0);
	// Path Initialization
	(G->get_ADT_nodelist()).search_vertex(vertex)->set_path(vertex);

	// Make the same node_list as G and priority queue, node_pq
	priority_queue<ADT_Node<int>, vector<ADT_Node<int>>, greater<ADT_Node<int>>>* node_pq
		= new priority_queue<ADT_Node<int>, vector<ADT_Node<int>>, greater<ADT_Node<int>>>;

	typename list<ADT_Node<int>*>::iterator node_iter;
	list<ADT_Node<int>*> node_list = G->get_ADT_nodelist().get_node_list();

	// Push the each vertices in the priority queue
	for (node_iter = node_list.begin(); node_iter != node_list.end(); node_iter++) {
		node_pq->push(**node_iter);
		// 각자에 대한 path는 source를 제외하고 아직 설정되지 않은 상태
	}
	
	while (!node_pq->empty()) {
		// 가장 Top에 있는 원소를 꺼냄: 얘를 pivot vertex라 하자
		ADT_Node<int> pivot = node_pq->top();
		node_pq->pop();

		// Pivot Vertex의 이름, 값, 경로
		string pivot_name = pivot.get_node_name();
		int pivot_value = pivot.get_node_value();
		string pivot_path = pivot.get_path();

		/* Debug */
		//cout << pivot_name << endl;
		//cout << pivot_value << endl;
		//cout << "Path of " << pivot_name << " is " << pivot_path << endl;
		
		// Make auxiliary priority queues
		priority_queue<ADT_Node<int>, vector<ADT_Node<int>>, greater<ADT_Node<int>>> aux_pq = *node_pq;
		priority_queue<ADT_Node<int>, vector<ADT_Node<int>>, greater<ADT_Node<int>>> rep_pq;

		// aux_pq의 원소를 계속 pop하면서 나온 node에 대해 모두 relaxation을 실시
		while (!aux_pq.empty()) {
			ADT_Node<int> z = aux_pq.top();
			aux_pq.pop();			

			if (z.isAdjacentTo(pivot_name)) {

				// 서로 Adjacent하다면, 그 둘을 잇고 있는 edge의 이름을 찾은 후 edge value를 얻자.
				string edge_name;
				string z_node_name = z.get_node_name();

				// z의 노드 이름이 알파벳 순서상으로 pivot보다 먼저인 경우
				// Edge의 이름: "z pivot"
				if (z_node_name.compare(pivot_name) < 0) {

					edge_name = z_node_name;
					edge_name += " ";
					edge_name += pivot_name;
				}
				// z의 노드 이름이 알파벳 순서상으로 pivot보다 나중인 경우
				// edge의 이름: "pivot z"
				else if (z_node_name.compare(pivot_name) > 0) {

					edge_name = pivot_name;
					edge_name += " ";
					edge_name += z_node_name;
				}

				int z_value = z.get_node_value();
				int edge_value = G->get_ADT_edgelist().search_edge(edge_name)->get_edge_value();

				// Relaxation
				if (pivot_value + edge_value < z_value) {

					// G에서 z와 이름의 똑같은 해당 vertex를 찾아간 다음, 노드 값을 바꿔버림 
					G->get_ADT_nodelist().search_vertex(z_node_name)->set_node_value(pivot_value + edge_value);

					// rep_pq에 갱신된 노드를 넣기 위해 z도 똑같이 update 해줌.
					z.set_node_value(pivot_value + edge_value);
					
					// Update new path
					string new_path = pivot_path;
					new_path += " ";
					new_path += z_node_name;

					(G->get_ADT_nodelist()).search_vertex(z_node_name)->set_path(new_path);
					z.set_path(new_path);
				}

			}
			// Relaxation 이후의 노드들을 rep_pq에 삽입함.
			rep_pq.push(z);
		}

		*node_pq = rep_pq;
	}

	delete node_pq;

	return 1;
}

bool operator<(const ADT_Edge<int>& edge1, const ADT_Edge<int>& edge2) {

	if (edge1.get_edge_value() < edge2.get_edge_value()) {
		return true;
	}

	if (edge1.get_edge_value() == edge2.get_edge_value()) {
		if (edge1.get_edge_name().compare(edge2.get_edge_name()) < 0) {
			return true;
		}
	}

	return false;
}

bool operator>(const ADT_Edge<int>& edge1, const ADT_Edge<int>& edge2) {

	if (edge1.get_edge_value() > edge2.get_edge_value()) {
		return true;
	}

	if (edge1.get_edge_value() == edge2.get_edge_value()) {
		if (edge1.get_edge_name().compare(edge2.get_edge_name()) > 0) {
			return true;
		}
	}

	return false;
}

priority_queue<ADT_Edge<int>, vector<ADT_Edge<int>>, greater<ADT_Edge<int>>> kruskal(ADT_Graph<int>* G) {
	
	// Elementary Cluster is defined in the node objects
	// Initialize Clusters
	typename list<ADT_Node<int>*>::iterator node_iter;
	list<ADT_Node<int>*> node_list = G->get_ADT_nodelist().get_node_list();

	for (node_iter = node_list.begin(); node_iter != node_list.end(); node_iter++) {
		(*node_iter)->initialize_cluster();
	}

	// Priority Queue Q에 G의 모든 Edge 넣음
	priority_queue<ADT_Edge<int>, vector<ADT_Edge<int>>, greater<ADT_Edge<int>>> Q;
	priority_queue<ADT_Edge<int>, vector<ADT_Edge<int>>, greater<ADT_Edge<int>>> T;

	typename list<ADT_Edge<int>*>::iterator edge_iter;
	list<ADT_Edge<int>*> edge_list = G->get_ADT_edgelist().get_edge_list();

	for (edge_iter = edge_list.begin(); edge_iter != edge_list.end(); edge_iter++) {
		Q.push(**edge_iter);
	}

	// G의 vertex 개수 구하기
	int vertex_num = G->get_ADT_nodelist().get_node_list().size();
	
	// T의 원소 개수가 (G의 vertex 개수 - 1)보다 작을 때
	while (T.size() < vertex_num - 1) {
		// Q에서 가장 Top에 있는 원소를 꺼냄. 그 edge를 min_edge라 하자
		ADT_Edge<int> min_edge = Q.top();
		Q.pop();

		// min_edge의 양 vertex 구함.
		ADT_Node<int> u = min_edge.get_first_node();
		ADT_Node<int> v = min_edge.get_second_node();

		string min_edge_name = min_edge.get_edge_name();

		// 각 vertex의 cluster 비교
		if (u.get_cluster() != v.get_cluster()) {
			T.push(min_edge);

			set<string> union_cluster = u.get_cluster();
			set<string> v_cluster = v.get_cluster();

			// 교집합은 항상 없음
			union_cluster.insert(v_cluster.begin(), v_cluster.end());

			typename set<string>::iterator set_iter;

			// Union Cluster의 각 원소에 반복자로 접근
			for (set_iter = union_cluster.begin(); set_iter != union_cluster.end(); set_iter++) {
				/* Debug */
				//cout << *set_iter << endl;

				G->get_ADT_nodelist().search_vertex(*set_iter)->set_cluster(union_cluster);
				
				//cout << "----" << endl;

			}

			//cout << "--------------------" << endl;

		}

	}

	return T;
}


int main(int argc, char* argv[]) {

	// 1st arg: Graph information
	// 2nd arg: Shortest path task problem
	// 3rd arg: answer of shortest path problem
	// 4th arg: answer of minimum spanning tree

	// STEP 1: 입력 파일에 적힌 Graph 정보로, graph 인스턴스에 삽입한다.
	if (argc != 5) {
		cout << "Invalid input format." << endl;
		return 1;
	}

	ifstream myfile;
	myfile.open(argv[1], fstream::in);

	// Read each line and insert vertecies
	// If line is empty line, then skip
	// If line has Edge, then start to insert edges

	ADT_Graph<int>* graph = new ADT_Graph<int>("GRAPH");
	string line;
	int line_number = 0;

	while (getline(myfile, line)) {

		if (line.compare("Node") == 0 || line.compare("\t") == 0 || line.compare("\n") == 0 || line.compare("") == 0) {
			//cout << "node or tab or enter or empty" << endl;
			line_number++;
			continue;
		}

		else if (line.compare("Edge") == 0) {
			line_number++;
			break;
		}

		else {
			//cout << line;

			graph->insertVertex(line, numeric_limits<int>::max());
			line_number++;
		}
	}

	line.clear();

	// Jump to edge line
	myfile.seekg(ios::beg);
	for (int i = 0; i < line_number + 1; i++) {
		myfile.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	while (getline(myfile, line)) {

		if (line == "Edge" || line == "\t" || line == "\n" || line == "") {
			continue;
		}

		istringstream line_stream(line);
		string str;
		string data[3];
		int i = 0;

		// get single string with delimiter ' '
		while (getline(line_stream, str, ' ')) {
			data[i] = str;
			i++;
		}

		// make edge_value integer
		int data2;
		istringstream intstream(data[2]);
		intstream >> data2;

		// edge_name format: "data0 data1"
		if (data[0].compare(data[1]) < 0) {

			string edge_name = data[0];
			edge_name += " ";
			edge_name += data[1];

			graph->insertEdge(data[0], data[1], edge_name, data2);
		}

		else if (data[0].compare(data[1]) > 0) {

			string edge_name = data[1];
			edge_name += " ";
			edge_name += data[0];

			graph->insertEdge(data[1], data[0], edge_name, data2);
		}

	}

	// STEP 2: Perform Dijikstra algorithm
	line.clear();
	ifstream taskfile;
	taskfile.open(argv[2], fstream::in);

	ofstream sp_outfile(argv[3]);

	while (getline(taskfile, line)) {

		// Skips for nothing
		if (line == "\t" || line == "\n" || line == "") {
			continue;
		}

		istringstream line_stream(line);
		string str;
		string data[2];
		int i = 0;


		// get single string with delimiter ' '
		while (getline(line_stream, str, ' ')) {
			data[i] = str;
			i++;
		}

		dijkstra(graph, data[0]); // input graph, source

		// 3rd argument에 결과와 node value 쓰기
		sp_outfile << graph->get_ADT_nodelist().search_vertex(data[1])->get_path() <<
			" " << graph->get_ADT_nodelist().search_vertex(data[1])->get_node_value() << endl;

		// 3rd argument에 결과와 node value 쓰기

		(graph->get_ADT_nodelist()).clear_node_path();  // clear node path
	}


	// STEP 3: Perform Kruskal algorithm
	ofstream mst_outfile(argv[4]);

	priority_queue<ADT_Edge<int>, vector<ADT_Edge<int>>, greater<ADT_Edge<int>>> mst
		= kruskal(graph);

	// mst의 모든 원소 다 꺼낼 때까지
	while (mst.size() > 0) {

		// mst에서 가장 Top에 있는 원소를 꺼냄. 그 edge를 min_edge라 하자
		ADT_Edge<int> min_edge = mst.top();
		mst.pop();

		mst_outfile << min_edge.get_edge_name() << " " << min_edge.get_edge_value() << endl;

	}

	delete graph;

	return 1;
}
