/*
 * Skeleton code for project 4 in EE205 2018 FALL KAIST
 * Created by Joonki Hong
 */

#include "ADT_graph.h"
#include <iostream>

using namespace std;

/*
 * Tips!!!!
 *
 * 1. Search 'YOUR CODE GOES HERE' to find where to implement.
 * 2. Use commented Debug to get the insight of adjacency list structure.
 * 3. You can compile this file by 'g++ -c ADT_graph.cpp'.
 * 4. You can compile with main.cpp by 'g++ main.cpp ADT_graph.cpp' after you fill the blanks.
 */


/*
 * I know that this project is a little bit tough, but I believe you can do this!!!
 * Feel free to ask TA!!!
 */


    // _    ____ _____   _   _           _
   // / \  |  _ \_   _| | \ | | ___   __| | ___
  // / _ \ | | | || |   |  \| |/ _ \ / _` |/ _ \
 // / ___ \| |_| || |   | |\  | (_) | (_| |  __/
// /_/   \_\____/ |_|___|_| \_|\___/ \__,_|\___|
                // |_____|

/*************************** ADT_Node ***************************/

/* Get node name */
template <class T>
string ADT_Node<T>::get_node_name(void) const {
	return node_name;
}

/* Get node value */
template <class T>
T ADT_Node<T>::get_node_value(void) const {
	return node_value;
}

/* Add new incidence collection */
template <class T>
int ADT_Node<T>::add_incidence(void){
	incidence = new ADT_Incidence<T>;   // Make new I(node)
	return 1;
}

/* Remove incidence */
template <class T>
int ADT_Node<T>::remove_incidence(void){
	delete incidence;	// Delete new I(node)
	return 1;
}

/* erase one edge from incidence list */
template <class T>
int ADT_Node<T>::erase_edge_from_incidence(ADT_Edge<T>* edge) {
	// *incidence.remove_incidence_list(edge)
	incidence->remove_incidence_list(edge);
	return 1;
}

/* return the begining of incidence list */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::get_begin(void){
	return incidence->get_begin();
}

/* return the end of incidence list */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::get_end(void){
	return incidence->get_end();
}

/* Call add_incidence_list in incidence collection */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::add_incidence_list(ADT_Edge<T>* edge){
	return incidence->add_incidence_list(edge);
}

/* Save the node position information */
template <class T>
int ADT_Node<T>::add_nodelist_info(typename list<ADT_Node<T>*>::iterator node_position){
	this->node_position = node_position;
	return 1;
}

/* Basic functionality of ADT_Node */
template <class T>
list<ADT_Edge<T>*> ADT_Node<T>::incidentEdges(void) {
	/* use incidentEdges in incidence list */
	// Return an edge list of the edges incident on the node

	return incidence->incidentEdges();

	/*
	 * YOUR CODE GOES HERE
	 */
}

template <class T>
int ADT_Node<T>::isAdjacentTo(string node_name) {
	/* use isAdjacentTo() function in incidence list	 */

	return incidence->isAdjacentTo(node_name);
	
	/*
	 * YOUR CODE GOES HERE
	 */
}

/* Constructor, initializing the node name and the node value, add new incidence collcetion*/
template <class T>
ADT_Node<T>::ADT_Node(string node_name, T node_value) {

	this->node_name = node_name;
	this->node_value = node_value;
	add_incidence();
	cluster.insert(node_name);

	/* Debug */
	//cout << "Test2: node name "<< get_node_name()<<", node_value "<< get_node_value() << endl << endl;
}


// New Function
/* Set path as node_path */
template <class T>
int ADT_Node<T>::set_path(string node_path) {
	this->path = node_path;
	return 1;
}

/* Get node's path */
template <class T>
string ADT_Node<T>::get_path(void) {
	return path;
}

/* Clear node's path */
template <class T>
int ADT_Node<T>::clear_path(void) {
	path.clear();
	return 1;
}

/* Set node value as infinity */
template <class T>
int ADT_Node<T>::set_node_value(T node_value) {
	this->node_value = node_value;
	return 1;
}

/* Get Cluster */
template <class T>
set<string> ADT_Node<T>::get_cluster(void) {
	return cluster;
}

/* Set Cluster */
template <class T>
int ADT_Node<T>::set_cluster(set<string> node_cluster) {
	this->cluster = node_cluster;
	return 1;
}

/* Initialize Cluster */
template <class T>
int ADT_Node<T>::initialize_cluster(void) {
	cluster.clear();
	cluster.insert(node_name);
	return 1;
}

 // ___            _     _
// |_ _|_ __   ___(_) __| | ___ _ __   ___ ___
 // | || '_ \ / __| |/ _` |/ _ \ '_ \ / __/ _ \
 // | || | | | (__| | (_| |  __/ | | | (_|  __/
// |___|_| |_|\___|_|\__,_|\___|_| |_|\___\___|

           // _ _           _   _
  // ___ ___ | | | ___  ___| |_(_) ___  _ __
 // / __/ _ \| | |/ _ \/ __| __| |/ _ \| '_ \
// | (_| (_) | | |  __/ (__| |_| | (_) | | | |
 // \___\___/|_|_|\___|\___|\__|_|\___/|_| |_|

/*************************** Incidence Collection ***************************/

/* Add new edge connection in the incidence collection */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::add_incidence_list(ADT_Edge<T>* edge) {
	return incidence_list.insert(incidence_list.end(), edge); // pointer will be replaced later
}

/* Remove an edge connection in the incidence collection */
template <class T>
int ADT_Incidence<T>::remove_incidence_list(ADT_Edge<T>* edge) {
	// list의 원소 중 edge와 참조하는 값이 같은 원소를 제거
	incidence_list.remove(edge);
	return 1;
}

template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::get_begin(void){
	return incidence_list.begin();
}

template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::get_end(void){
	return incidence_list.end();
}


template <class T>
int ADT_Incidence<T>::isAdjacentTo(string node_name) {
	/* check through incidence list for input node_name  */
	/* return 1 if you find it return 0 if you don't find it  */

	for (typename list<ADT_Edge<T>*>::iterator incidence_list_it = this->get_begin();
									  incidence_list_it != this->get_end(); incidence_list_it++) {
		// 반복자가 참조하는 것이 참조하는 것의 멤버변수 first_node가 참조하는 것의 멤버변수 node_name

		ADT_Node<T> first_node = (*incidence_list_it)->get_first_node();
		ADT_Node<T> second_node = (*incidence_list_it)->get_second_node();

		if (first_node.get_node_name() == node_name
				|| second_node.get_node_name() == node_name) {
			return 1;
		}
	}

	return 0;

	/*
	 * YOUR CODE GOES HERE
	 */

}

template <class T>
list<ADT_Edge<T>*> ADT_Incidence<T>::incidentEdges(void) {
	/* return list of incident edges */
	
	return incidence_list;

	/*
	 * YOUR CODE GOES HERE
	 */
}



    // _    ____ _____   _____    _
   // / \  |  _ \_   _| | ____|__| | __ _  ___
  // / _ \ | | | || |   |  _| / _` |/ _` |/ _ \
 // / ___ \| |_| || |   | |__| (_| | (_| |  __/
// /_/   \_\____/ |_|___|_____\__,_|\__, |\___|
                // |_____|          |___/
/*************************** ADT_Edge ***************************/

/* Get edge name */
template <class T>
string ADT_Edge<T>::get_edge_name(void) const {
	return edge_name;
}

/* Get edge value */
template <class T>
T ADT_Edge<T>::get_edge_value(void) const {
	return edge_value;
}

/* Get first node */
template <class T>
ADT_Node<T> ADT_Edge<T>::get_first_node(void) {

	// 포인터가 아닌 객체 자체를 반환하네...
	return *first_node;
}

/* Get second node */
template <class T>
ADT_Node<T> ADT_Edge<T>::get_second_node(void) {
	return *second_node;
}

/* Save pointer to the incidence collection of the first vertex and the second vertex */
template <class T>
int ADT_Edge<T>::add_incidence_info(typename list<ADT_Edge<T>*>::iterator first_incidence_position,
									typename list<ADT_Edge<T>*>::iterator second_incidence_position) {
	this->first_incidence_position = first_incidence_position;
	this->second_incidence_position = second_incidence_position;
	return 1;
}

/* Save the edge position information */
template <class T>
int ADT_Edge<T>::add_edgelist_info(typename list<ADT_Edge<T>*>::iterator edge_position) {
	this->edge_position = edge_position;
	return 1;
}

template <class T>
list<ADT_Node<T>*> ADT_Edge<T>::endVertices(void) {
	/* return a list that have pointer to the first node and second node of the edge */
	
	// first node는 앞에, second node는 뒤에 삽입
	list<ADT_Node<T>*>* nodes_list = new list<ADT_Node<T>*>;
	nodes_list->push_front(first_node);
	nodes_list->push_back(second_node);

	return *nodes_list;

	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
string ADT_Edge<T>::opposite(string node_name) {
	/* return the opposite node of given vertex in string */
	/* if given vertex is not included in this edge return 0 */
	/* e.g. for edge A-B, given A, return B */
	/* e.g. for edge A-B, given C, return 0 */

	if (first_node->get_node_name() == node_name) {
		return second_node->get_node_name();
	}

	else if (second_node->get_node_name() == node_name) {
		return first_node->get_node_name();
	}

	else {
		return string("0");
	}

	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Edge<T>::isAdjacentTo(string edge_name) {
	/* check that the given edge is adjacent with first end node */
	/* check that the given edge is adjacent with second end node */
	/* return 1 if it is adjacent return 0 if not */

	// 공통의 vertex를 가지는지 확인한다.


	typename list<ADT_Edge<T>*>::iterator first_inci_edge_it = first_node->get_begin();
	typename list<ADT_Edge<T>*>::iterator second_inci_edge_it = second_node->get_begin();

	// 첫번째 노드의 주변 edge를 가리키는 포인터 리스트(Incidence List)의 반복자
	for (first_inci_edge_it = first_node->get_begin(); 
		 first_inci_edge_it != first_node->get_end();  first_inci_edge_it++) {

		if ((*first_inci_edge_it)->get_edge_name() == edge_name) {
			return 1;
		}
	}

	// 두번째 노드의 주변 edge를 가리키는 포인터 리스트의 반복자
	for (second_inci_edge_it = second_node->get_begin();
		 second_inci_edge_it != second_node->get_end(); second_inci_edge_it++) {

		if ((*second_inci_edge_it)->get_edge_name() == edge_name) {
			return 1;
		}
	}

	return 0;

	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Edge<T>::isIncidentOn(string node_name) {
	/* return 1 if given node is incident, return 0 if not  */
	/* check the first end node and the second end node  */

	if (first_node->get_node_name() == node_name ||
		second_node->get_node_name() == node_name) {
		return 1;
	}

	return 0;


	/*
	 * YOUR CODE GOES HERE
	 */
}


/* Constuctor, initializing edge name, edge value, and vertex name */
template <class T>
ADT_Edge<T>::ADT_Edge(string edge_name, T edge_value, ADT_Node<T> *first_node, ADT_Node<T> *second_node) {

	list<ADT_Edge<T>*> temp_list;

	this->edge_name = edge_name;
	this->edge_value = edge_value;
	this->first_node = first_node;
	this->second_node = second_node;

	/* Debug */
	//cout << "Test5: edge name "<< get_edge_name() <<", edge value " <<get_edge_value() << endl <<endl;
}


    // _    ____ _____   _   _           _      _ _     _
   // / \  |  _ \_   _| | \ | | ___   __| | ___| (_)___| |_
  // / _ \ | | | || |   |  \| |/ _ \ / _` |/ _ \ | / __| __|
 // / ___ \| |_| || |   | |\  | (_) | (_| |  __/ | \__ \ |_
// /_/   \_\____/ |_|___|_| \_|\___/ \__,_|\___|_|_|___/\__|
                // |_____|
/*************************** ADT_Nodelist ***************************/

/* Add new node in the nodelist */
template <class T>
typename list<ADT_Node<T>*>::iterator ADT_Nodelist<T>::add_node_list(ADT_Node<T> *vertex) {
	return node_list.insert(node_list.end(),vertex);
}

/* Remove a node in the nodelist */
template <class T>
int ADT_Nodelist<T>::remove_node_list(ADT_Node<T> *vertex) {
	node_list.remove(vertex);
	return 1;
}


template <class T>
ADT_Node<T>* ADT_Nodelist<T>::search_vertex(string vertex) {
	/* return pointer to a node that has given node name */
	/* if there is no such node, return NULL */

	for (node_iter = node_list.begin(); node_iter != node_list.end(); node_iter++) {
		if ((*node_iter)->get_node_name() == vertex) {
			return *node_iter;
		}
	}

	return NULL;

	/*
	 * YOUR CODE GOES HERE
	 */
}

template <class T>
int	ADT_Nodelist<T>::print_all_vertices(void){
	/* print all vertices' name in the nodelist */

	//cout << "------Print all vertices------" << endl;

	for (node_iter = node_list.begin(); node_iter != node_list.end(); node_iter++) {
		cout << (*node_iter)->get_node_name() << endl;
		}

	//cout << "------Printing all vertices is done------" << endl;

	return 1;

	/*
	 * YOUR CODE GOES HERE
	 */
}

/* Return node list */
template <class T>
list<ADT_Node<T>*> ADT_Nodelist<T>::get_node_list(void) {
	return node_list;
}

// New Method
/* Clear all nodes' path*/
template <class T>
int	ADT_Nodelist<T>::clear_node_path(void) {

	for (node_iter = node_list.begin(); node_iter != node_list.end(); node_iter++) {
		(*node_iter)->clear_path();
	}

	return 1;

}

/* Set all node value to given node_value */
template <class T>
int	ADT_Nodelist<T>::set_all_node_value(T node_value) {

	for (node_iter = node_list.begin(); node_iter != node_list.end(); node_iter++) {
		(*node_iter)->set_node_value(node_value);
	}

	return 1;

}




    // _    ____ _____   _____    _            _ _     _
   // / \  |  _ \_   _| | ____|__| | __ _  ___| (_)___| |_
  // / _ \ | | | || |   |  _| / _` |/ _` |/ _ \ | / __| __|
 // / ___ \| |_| || |   | |__| (_| | (_| |  __/ | \__ \ |_
// /_/   \_\____/ |_|___|_____\__,_|\__, |\___|_|_|___/\__|
                // |_____|          |___/
/*************************** ADT_Edgelist ***************************/

/* Add new edge in the edgelist */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Edgelist<T>::add_edge_list(ADT_Edge<T> *edge) {
	return edge_list.insert(edge_list.end(), edge);
}

/* Remove a edge in the edgelist */
template <class T>
int ADT_Edgelist<T>::remove_edge_list(ADT_Edge<T> *edge) {
	edge_list.remove(edge);
	return 1;
}


template <class T>
ADT_Edge<T>* ADT_Edgelist<T>::search_edge(string edge) {
	/* return pointer to certain edge that has given edge name */
	/* if there is no such edge, return NULL */

	for (edge_iter = edge_list.begin(); edge_iter != edge_list.end(); edge_iter++) {
		if ((*edge_iter)->get_edge_name() == edge) {
			return *edge_iter;
		}
	}

	return NULL;

	/*
	 * YOUR CODE GOES HERE
	 */
}

template <class T>
int	ADT_Edgelist<T>::print_all_edges(void){
	/* print all edges' name in the edgelist */

	//cout << "------Print all edges------" << endl;

	for (edge_iter = edge_list.begin(); edge_iter != edge_list.end(); edge_iter++) {
		cout << (*edge_iter)->get_edge_name() << endl;
	}

	//cout << "------Printing all edges is done------" << endl;

	return 1;

	/*
	 * YOUR CODE GOES HERE
	 */

}
/* Return edge list */
template <class T>
list<ADT_Edge<T>*> ADT_Edgelist<T>::get_edge_list(void) {
	return edge_list;
}


    // _    ____ _____   ____                 _
   // / \  |  _ \_   _| / ___|_ __ __ _ _ __ | |__
  // / _ \ | | | || |  | |  _| '__/ _` | '_ \| '_ \
 // / ___ \| |_| || |  | |_| | | | (_| | |_) | | | |
// /_/   \_\____/ |_|___\____|_|  \__,_| .__/|_| |_|
                // |_____|             |_|

/*************************** ADT_Graph ***************************/

template <class T>
int ADT_Graph<T>::vertices(void) {
	// Graph에 있는 모든 vertices 출력
	// 1. 노드리스트 -> 반복자 돌며 노드 이름 구해오기

	ADT_nodelist->print_all_vertices();

	return 1;

	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Graph<T>::edges(void) {

	ADT_edgelist->print_all_edges();

	return 1;

	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Graph<T>::insertVertex(string node_name, T node_value) {

	/* 1. make new node object */
	/* 2. add new node object to nodelist */
	/* 3. add nodelist info to node object */

	ADT_Node<T>* new_vertex = new ADT_Node<T>(node_name, node_value);

	
	typename list<ADT_Node<T>*>::iterator node_iterator = ADT_nodelist->add_node_list(new_vertex);

	new_vertex->add_nodelist_info(node_iterator); 
	

	//new_vertex->add_nodelist_info(ADT_nodelist->add_node_list(new_vertex));



	/*
	 * YOUR CODE GOES HERE
	 */

	/* Debug */
	//cout << "Test3: node iterator is working??? " << (*node_iterator)->get_node_name() << endl << endl;
}


template <class T>
int ADT_Graph<T>::insertEdge(string vertex_name1, string vertex_name2, string edge_name, T edge_value) {

	ADT_Node<T> *first_node, *second_node;
	typename list<ADT_Edge<T>*>::iterator edge_iterator, first_edge_iterator, second_edge_iterator;

	/* 1. Find corresponding ADT_Node with vertex name */
	/* 2. Make new edge and add it to edge list */
	/* 3. Add edge to incidence collection of the first and second vertex */
	/* 4. Add reverse connection to incidence collection */

	first_node = ADT_nodelist->search_vertex(vertex_name1);
	second_node = ADT_nodelist->search_vertex(vertex_name2);

	ADT_Edge<T>* new_edge = new ADT_Edge<T>(edge_name, edge_value, first_node, second_node);

	edge_iterator = ADT_edgelist->add_edge_list(new_edge);

	first_edge_iterator = first_node->add_incidence_list(new_edge);
	second_edge_iterator = second_node->add_incidence_list(new_edge);

	new_edge->add_edgelist_info(edge_iterator);
	new_edge->add_incidence_info(first_edge_iterator, second_edge_iterator);

	/*
	 * YOUR CODE GOES HERE
	 */

	/* Debug */
	//cout << "Test4: search_vertex??? "<< first_node->get_node_name() <<" "<< second_node->get_node_name() << endl <<endl;
	//cout << "Test6: edge iterator is working ??? "<< (*edge_iterator)->get_edge_name() <<" "<< (*edge_iterator)->get_edge_value() << endl <<endl;

	return 1;
}


template <class T>
int ADT_Graph<T>::eraseVertex(string node_name) {
	/* 1. Use search_vertex() to find corresponding node pointer */
	/* 2. Erase all edges in incidence collection */
	/* 3. Remove node from nodelist */
	/* 4. Remove node */

	ADT_Node<T>* removing_node = ADT_nodelist->search_vertex(node_name);

	list<ADT_Edge<T>*> incident_list = removing_node->incidentEdges();

	// incidence_list의 반복자가 참조하는 것은 edge의 포인터
	// 각 반복자가 순회하면서...
	for (typename list<ADT_Edge<T>*>::iterator incident_list_it = incident_list.begin();
		incident_list_it != incident_list.end(); incident_list_it++) {
		
		// edge_list에 있는 해당 edge 정보를 지움
		ADT_edgelist->remove_edge_list(*incident_list_it);

		// 주어진 노드의 반대 쪽 노드를 찾음
		ADT_Node<T>* opposite_node
			= ADT_nodelist->search_vertex((*incident_list_it)->opposite(node_name));

		// 그 노드의 incidence list에서 해당 edge를 지움
		opposite_node->erase_edge_from_incidence(*incident_list_it);

		// 해당 edge 자체를 지움
		delete *incident_list_it;
	}

	// Incident list 지움
	removing_node->remove_incidence();

	// 노드 리스트에서 노드 지움
	ADT_nodelist->remove_node_list(removing_node);

	// 노드 자체를 지움
	delete removing_node;


	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Graph<T>::eraseEdge(string edge_name) {
	/* find correstponding edge and call eraseEdge agian */

	this->eraseEdge(ADT_edgelist->search_edge(edge_name));

	return 1;

	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Graph<T>::eraseEdge(ADT_Edge<T>* erase_edge) {

	/* 1. Erase edge in the first node incidence collection */
	/* 2. Erase edge in the second node incidence collection */
	/* 3. Erase edge from the edgelist */
	/* 4. Erase edge  */

	// edge -> first_node -> incidence_list
	
	// remove_incidecec_list

	ADT_Node<T> first_node = erase_edge->get_first_node();
	ADT_Node<T> second_node = erase_edge->get_second_node();

	first_node.erase_edge_from_incidence(erase_edge);
	second_node.erase_edge_from_incidence(erase_edge);

	ADT_edgelist->remove_edge_list(erase_edge);

	delete erase_edge;

	/*
	 * YOUR CODE GOES HERE
	 */
}

template <class T>
ADT_Nodelist<T> ADT_Graph<T>::get_ADT_nodelist(void) {
	return *ADT_nodelist;
}

template <class T>
ADT_Edgelist<T> ADT_Graph<T>::get_ADT_edgelist(void) {
	return *ADT_edgelist;
}

template <class T>
ADT_Graph<T>::ADT_Graph(string graph_name) {
	this->graph_name = graph_name;
	ADT_nodelist = new ADT_Nodelist<T>;
	ADT_edgelist = new ADT_Edgelist<T>;

	/* Debug */
	//cout<<"Test1: graph name is "<<graph_name<<endl<<endl;

}

template class ADT_Graph<int>;
template class ADT_Node<int>;
template class ADT_Edge<int>;
template class ADT_Edgelist<int>;
template class ADT_Nodelist<int>;