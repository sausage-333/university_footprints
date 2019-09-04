#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>

#include "double_list.h"

using namespace std;

/* DO NOT CHANGE INCLUDED HEADERS */

int main(int argc, char* argv[])
{
  /* 1st arg: input file name , 2nd arg: output file name */

  /* T_start = the time that reciever starts */
	time_t start, end;
	time(&start);

	if (argc == 3) {
		ifstream myfile;

		// open 1st argument
		myfile.open(argv[1], fstream::in);

		// list containing file's message
		double_list* dll_ptr = new double_list;

		string line;
		// get line with delimiter "\n"
		while (getline(myfile, line)) {
			istringstream mystream(line);
			string str;
			string data[3];
			int i = 0;

			// If line is space, or enter or tab, do nothing and go to next line
			if (line == "\n" || line == "\t" || line == " ") {
				continue;
			}

			// get single string with delimiter "\n"
			while (getline(mystream, str, '\t')) {
				data[i] = str;
				i++;
			}

			int data1;
			istringstream heystream(data[0]);
			heystream >> data1;

			int data2;
			istringstream theystream(data[1]);
			theystream >> data2;

			string data3(data[2]);

			// put first element anyway
			if (dll_ptr->d_list_empty()) {
				dll_ptr->d_list_insert_front(new d_list_elem(data1, data2, data3));
			}

			else {
				// variables for head->tail direction 
				d_list_elem* traversal_ptr = dll_ptr->d_list_front();
				d_list_elem* dll_tail = dll_ptr->d_list_tail();

				// variables for tail->head direction
				d_list_elem* re_traversal_ptr = dll_ptr->d_list_back();
				d_list_elem* dll_head = dll_ptr->d_list_head();

				// traversal_ptr and re_traversal_ptr is a pointer for new element's inserting poistion

				int front_data1 = dll_ptr->d_list_get_data1(traversal_ptr);
				int back_data1 = dll_ptr->d_list_get_data1(re_traversal_ptr);

				int front_data2 = dll_ptr->d_list_get_data2(traversal_ptr);
				int back_data2 = dll_ptr->d_list_get_data2(re_traversal_ptr);

				// elements for  applying head -> tail direction algorithm 
				// head -> tail direction algorithm seeks inserting position with increasing order

				// data1 is closer to front's one
				if ((data1 - front_data1 < back_data1 - data1) ||
					// data1: front != back, and data1 is close to back as same as front 
					((data1 - front_data1 == back_data1 - data1) && (front_data1 != back_data1)) ||
					// data1: front == back, and data2 is closer to front's one
					((front_data1 == back_data1) && ((data2 - front_data2) <= (back_data2 - data2)))) {

					// head -> tail direction algorithm 
					while (traversal_ptr != dll_tail) {

						int current_data1 = dll_ptr->d_list_get_data1(traversal_ptr);
						d_list_elem* next_ptr = dll_ptr->d_list_next(traversal_ptr);

						// message number: new element > traversal_ptr
						if (data1 > current_data1) {

							// traversal_ptr == tail
							if (next_ptr == dll_tail) {
								dll_ptr->d_list_insert_back(new d_list_elem(data1, data2, data3));
								break;
							}

							// traversal_ptr != tail
							else {
								traversal_ptr = next_ptr;
							}
						}

						// message number: new element < traversal_ptr
						else if (data1 < current_data1) {
							dll_ptr->d_list_insert_before(traversal_ptr, new d_list_elem(data1, data2, data3));
							break;
						}

						// message number: new element == traversal_ptr
						else {

							// packet number: new element > traversal_ptr
							if (data2 > dll_ptr->d_list_get_data2(traversal_ptr)) {

								// traversal_ptr != tail
								if (next_ptr == dll_tail) {
									dll_ptr->d_list_insert_back(new d_list_elem(data1, data2, data3));
									break;
								}

								// traversal_ptr != tail
								else {
									traversal_ptr = next_ptr;
								}
							}

							// packet number: new element < traversal_ptr
							else if (data2 < dll_ptr->d_list_get_data2(traversal_ptr)) {
								dll_ptr->d_list_insert_before(traversal_ptr, new d_list_elem(data1, data2, data3));
								break;
							}

							// packet number: new element == traversal_ptr
							else {
								d_list_elem* old = traversal_ptr;
								traversal_ptr = new d_list_elem(data1, data2, data3);
								dll_ptr->d_list_replace(old, traversal_ptr);
								break;
							}
						}
					}
				}
				
				// rest elements are applying tail -> head direction alrgorithm
				// tail -> head direction algorithm seeks inserting position with decreasing order
				else {

					// tail -> head direction alrgorithm
					while (re_traversal_ptr != dll_head) {

						int current_data1 = dll_ptr->d_list_get_data1(re_traversal_ptr);
						d_list_elem* prev_ptr = dll_ptr->d_list_prev(re_traversal_ptr);

						// message number: new element < re_traversal_ptr
						if (data1 < current_data1) {

							// re_traversal_ptr == tail
							if (prev_ptr == dll_head) {
								dll_ptr->d_list_insert_front(new d_list_elem(data1, data2, data3));
								break;
							}

							// re_traversal_ptr != tail
							else {
								re_traversal_ptr = prev_ptr;
							}
						}

						// message number: new element > re_traversal_ptr
						else if (data1 > current_data1) {
							dll_ptr->d_list_insert_after(re_traversal_ptr, new d_list_elem(data1, data2, data3));
							break;
						}

						// message number: new element == re_traversal_ptr

						else {
							
							// packet number: new element < re_traversal_ptr
							if (data2 < dll_ptr->d_list_get_data2(re_traversal_ptr)) {

								// re_traversal_ptr == tail
								if (prev_ptr == dll_head) {
									dll_ptr->d_list_insert_front(new d_list_elem(data1, data2, data3));
									break;
								}

								// re_traversal_ptr != tail
								else {
									re_traversal_ptr = prev_ptr;
								}
							}

							// packet number: new element > re_traversal_ptr
							else if (data2 > dll_ptr->d_list_get_data2(re_traversal_ptr)) {
								dll_ptr->d_list_insert_after(re_traversal_ptr, new d_list_elem(data1, data2, data3));
								break;
							}

							// packet number: new element == re_traversal_ptr
							else {
								d_list_elem* old = re_traversal_ptr;
								re_traversal_ptr = new d_list_elem(data1, data2, data3);
								dll_ptr->d_list_replace(old, re_traversal_ptr);
								break;
							}
						}
					}
				}
			}
		}

		// Now elements in single linked list is sorted in increasing order
		
		// traversal_ptr2 is pointer for making new output file
		// trv_next_ptr is traversal_ptr2's next pointer 
		d_list_elem* traversal_ptr2 = dll_ptr->d_list_front();
		d_list_elem* trv_next_ptr;

		// output file stream outfile object named as 2nd arg
		ofstream outfile(argv[2]);

		// do nothing for emtpy file
		if (dll_ptr->d_list_empty()) { }

		else {

			int start_message_number = dll_ptr->d_list_get_data1(traversal_ptr2);
			int start_packet_number = dll_ptr->d_list_get_data2(traversal_ptr2);

			// check message number of list's head
			outfile << "- Message " << dll_ptr->d_list_get_data1(traversal_ptr2) << endl;

			// make warning messages if message not starts with packet number 1
			if (start_packet_number != 1) {
				for (int i = 1; i < start_packet_number; i++) {
					outfile << "WARNING: packet " << i << " of message "
						<< start_packet_number << " is missing" << endl;
				}
			}

			d_list_elem* dll_tail = dll_ptr->d_list_tail();

			// do this iteration until just before to list's tail
			while (dll_ptr->d_list_next(traversal_ptr2) != dll_tail) {

				// file always writes message contents after all packet error handling is done
				outfile << dll_ptr->d_list_get_data3(traversal_ptr2) << endl;

				trv_next_ptr = dll_ptr->d_list_next(traversal_ptr2);

				int message_number = dll_ptr->d_list_get_data1(traversal_ptr2);
				int packet_number = dll_ptr->d_list_get_data2(traversal_ptr2);

				int next_message_number = dll_ptr->d_list_get_data1(trv_next_ptr);
				int next_packet_number = dll_ptr->d_list_get_data2(trv_next_ptr);

				// (x,y) -> message number is x, packet number is y

				// For the case of non-error increasement
				// ex) (1,1) -> (1,2)
				if (packet_number + 1 == next_packet_number) {

					traversal_ptr2 = trv_next_ptr;
				}

				// For the case of error increasement due to the missing packet
				// ex) (1,1) -> (1,x), x>2
				else if (message_number == next_message_number &&
						 packet_number + 1 != next_packet_number) {

					for (int i = packet_number + 1; i < next_packet_number; i++) {
						outfile << "WARNING: packet " << i << " of message "
							<< message_number << " is missing" << endl;
					}

					traversal_ptr2 = trv_next_ptr;

				}

				// For the case of next message number
				// ex) (1,1) -> (m,x), m>1, x can be non-1
				else if (message_number != next_message_number) {
					outfile << " - End Message " << message_number << endl;
					outfile << endl;
					outfile << "- Message " << next_message_number << endl;

					// make warning messages if message does not start with packet number 1
					if (next_packet_number != 1) {
						for (int i = 1; i < next_packet_number; i++) {
							outfile << "WARNING: packet " << i << " of message "
								<< next_packet_number << " is missing" << endl;
						}
					}

					traversal_ptr2 = trv_next_ptr;
				}

				continue;

			}

			// Write contents of list's tail
			outfile << dll_ptr->d_list_get_data3(traversal_ptr2) << endl;
			outfile << "- End Message " << dll_ptr->d_list_get_data1(traversal_ptr2) << endl;
			outfile << endl;
		}

		time(&end);

		// Record running time
		outfile << "Running Time: " << difftime(end, start) << " s" << endl;
	}

	else {
		cout << "Invalid input" << endl;
	}
  
  ///////////////////////////////////////////////////////
  //                                                   //
  //  DOUBLY LINKED LIST RECEIVER IMPLEMENTATION HERE  //
  //                                                   //
  ///////////////////////////////////////////////////////

  /* T_finish = the time that reciever finishes */

  /* Write to the output file "Running Time: (T_finish-T_start) s." */

	return 0;
}
