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
		// ���ڿ� ���� path�� source�� �����ϰ� ���� �������� ���� ����
	}
	
	while (!node_pq->empty()) {
		// ���� Top�� �ִ� ���Ҹ� ����: �긦 pivot vertex�� ����
		ADT_Node<int> pivot = node_pq->top();
		node_pq->pop();

		// Pivot Vertex�� �̸�, ��, ���
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

		// aux_pq�� ���Ҹ� ��� pop�ϸ鼭 ���� node�� ���� ��� relaxation�� �ǽ�
		while (!aux_pq.empty()) {
			ADT_Node<int> z = aux_pq.top();
			aux_pq.pop();			

			if (z.isAdjacentTo(pivot_name)) {

				// ���� Adjacent�ϴٸ�, �� ���� �հ� �ִ� edge�� �̸��� ã�� �� edge value�� ����.
				string edge_name;
				string z_node_name = z.get_node_name();

				// z�� ��� �̸��� ���ĺ� ���������� pivot���� ������ ���
				// Edge�� �̸�: "z pivot"
				if (z_node_name.compare(pivot_name) < 0) {

					edge_name = z_node_name;
					edge_name += " ";
					edge_name += pivot_name;
				}
				// z�� ��� �̸��� ���ĺ� ���������� pivot���� ������ ���
				// edge�� �̸�: "pivot z"
				else if (z_node_name.compare(pivot_name) > 0) {

					edge_name = pivot_name;
					edge_name += " ";
					edge_name += z_node_name;
				}

				int z_value = z.get_node_value();
				int edge_value = G->get_ADT_edgelist().search_edge(edge_name)->get_edge_value();

				// Relaxation
				if (pivot_value + edge_value < z_value) {

					// G���� z�� �̸��� �Ȱ��� �ش� vertex�� ã�ư� ����, ��� ���� �ٲ���� 
					G->get_ADT_nodelist().search_vertex(z_node_name)->set_node_value(pivot_value + edge_value);

					// rep_pq�� ���ŵ� ��带 �ֱ� ���� z�� �Ȱ��� update ����.
					z.set_node_value(pivot_value + edge_value);
					
					// Update new path
					string new_path = pivot_path;
					new_path += " ";
					new_path += z_node_name;

					(G->get_ADT_nodelist()).search_vertex(z_node_name)->set_path(new_path);
					z.set_path(new_path);
				}

			}
			// Relaxation ������ ������ rep_pq�� ������.
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

	// Priority Queue Q�� G�� ��� Edge ����
	priority_queue<ADT_Edge<int>, vector<ADT_Edge<int>>, greater<ADT_Edge<int>>> Q;
	priority_queue<ADT_Edge<int>, vector<ADT_Edge<int>>, greater<ADT_Edge<int>>> T;

	typename list<ADT_Edge<int>*>::iterator edge_iter;
	list<ADT_Edge<int>*> edge_list = G->get_ADT_edgelist().get_edge_list();

	for (edge_iter = edge_list.begin(); edge_iter != edge_list.end(); edge_iter++) {
		Q.push(**edge_iter);
	}

	// G�� vertex ���� ���ϱ�
	int vertex_num = G->get_ADT_nodelist().get_node_list().size();
	
	// T�� ���� ������ (G�� vertex ���� - 1)���� ���� ��
	while (T.size() < vertex_num - 1) {
		// Q���� ���� Top�� �ִ� ���Ҹ� ����. �� edge�� min_edge�� ����
		ADT_Edge<int> min_edge = Q.top();
		Q.pop();

		// min_edge�� �� vertex ����.
		ADT_Node<int> u = min_edge.get_first_node();
		ADT_Node<int> v = min_edge.get_second_node();

		string min_edge_name = min_edge.get_edge_name();

		// �� vertex�� cluster ��
		if (u.get_cluster() != v.get_cluster()) {
			T.push(min_edge);

			set<string> union_cluster = u.get_cluster();
			set<string> v_cluster = v.get_cluster();

			// �������� �׻� ����
			union_cluster.insert(v_cluster.begin(), v_cluster.end());

			typename set<string>::iterator set_iter;

			// Union Cluster�� �� ���ҿ� �ݺ��ڷ� ����
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

	// STEP 1: �Է� ���Ͽ� ���� Graph ������, graph �ν��Ͻ��� �����Ѵ�.
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

		// 3rd argument�� ����� node value ����
		sp_outfile << graph->get_ADT_nodelist().search_vertex(data[1])->get_path() <<
			" " << graph->get_ADT_nodelist().search_vertex(data[1])->get_node_value() << endl;

		// 3rd argument�� ����� node value ����

		(graph->get_ADT_nodelist()).clear_node_path();  // clear node path
	}


	// STEP 3: Perform Kruskal algorithm
	ofstream mst_outfile(argv[4]);

	priority_queue<ADT_Edge<int>, vector<ADT_Edge<int>>, greater<ADT_Edge<int>>> mst
		= kruskal(graph);

	// mst�� ��� ���� �� ���� ������
	while (mst.size() > 0) {

		// mst���� ���� Top�� �ִ� ���Ҹ� ����. �� edge�� min_edge�� ����
		ADT_Edge<int> min_edge = mst.top();
		mst.pop();

		mst_outfile << min_edge.get_edge_name() << " " << min_edge.get_edge_value() << endl;

	}

	delete graph;

	return 1;
}
