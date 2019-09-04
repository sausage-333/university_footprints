#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>

#include "single_list.h"

using namespace std;

/* DO NOT CHANGE INCLUDED HEADERS */

int main(int argc, char* argv[]) {
  /* 1st arg: input file name , 2nd arg: output file name */
	time_t start, end;
	time(&start);

	if (argc == 3) {
		ifstream myfile;

		// open 1st argument
		myfile.open(argv[1], fstream::in);

		// list containing file's message
		single_list* first_sll_ptr = new single_list;

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
			if (first_sll_ptr->list_empty()) {
				first_sll_ptr->list_insert_front(new list_elem(data1, data2, data3));
			}

			else {

				// traversal_ptr will point to position which new element should be inserted or replaced  
				list_elem* traversal_ptr = first_sll_ptr->list_head();

				while (traversal_ptr != NULL) {

					// message number: new element > traversal_ptr
					if (data1 > first_sll_ptr->list_get_data1(traversal_ptr)) {

						// traversal_ptr == tail
						if (first_sll_ptr->list_next(traversal_ptr) == NULL) {
							first_sll_ptr->list_insert_after(traversal_ptr, new list_elem(data1, data2, data3));
							break;
						}

						// traversal_ptr != tail
						else {
							traversal_ptr = first_sll_ptr->list_next(traversal_ptr);
						}
					}

					// message number: new element < traversal_ptr
					else if (data1 < first_sll_ptr->list_get_data1(traversal_ptr)) {
						first_sll_ptr->list_insert_before(traversal_ptr, new list_elem(data1, data2, data3));
						break;
					}

					// message number: new element == traversal_ptr
					else {

						// packet number: new element > traversal_ptr
						if (data2 > first_sll_ptr->list_get_data2(traversal_ptr)) {

							// traversal_ptr != tail
							if (first_sll_ptr->list_next(traversal_ptr) == NULL) {
								first_sll_ptr->list_insert_after(traversal_ptr, new list_elem(data1, data2, data3));
								break;
							}

							// traversal_ptr != tail
							else {
								traversal_ptr = first_sll_ptr->list_next(traversal_ptr);
							}
						}

						// packet number: new element < traversal_ptr
						else if (data2 < first_sll_ptr->list_get_data2(traversal_ptr)) {
							first_sll_ptr->list_insert_before(traversal_ptr, new list_elem(data1, data2, data3));
							break;
						}

						// packet number: new element == traversal_ptr
						else {
							list_elem* old = traversal_ptr;
							traversal_ptr = new list_elem(data1, data2, data3);
							first_sll_ptr->list_replace(old, traversal_ptr);
							break;
						}

					}

				}

			}

		}

		// Now elements in single linked list is sorted in increasing order

		// traversal_ptr2 is pointer for making new output file
		// trv_next_ptr is traversal_ptr2's next pointer 
		list_elem* traversal_ptr2 = first_sll_ptr->list_head();
		list_elem* trv_next_ptr;

		// output file stream outfile object named as 2nd arg
		ofstream outfile(argv[2]);

		// do nothing for emtpy file
		if (first_sll_ptr->list_empty()) { }

		else {

			// check message number of list's head
			outfile << "- Message " << first_sll_ptr->list_get_data1(traversal_ptr2) << endl;

			// make warning messages if message does not start with packet number 1
			if (first_sll_ptr->list_get_data2(traversal_ptr2) != 1) {
				for (int i = 1; i < first_sll_ptr->list_get_data2(traversal_ptr2); i++) {
					outfile << "WARNING: packet " << i << " of message "
						<< first_sll_ptr->list_get_data1(traversal_ptr2) << " is missing" << endl;
				}
			}

			// do this iteration until just before to list's tail
			while (first_sll_ptr->list_next(traversal_ptr2) != NULL) {

				// file always writes message contents after all packet error handling is done
				outfile << first_sll_ptr->list_get_data3(traversal_ptr2) << endl;

				trv_next_ptr = first_sll_ptr->list_next(traversal_ptr2);

				// (x,y) -> message number is x, packet number is y

				// For the case of non-error increasement
				// ex) (1,1) -> (1,2)
				if (first_sll_ptr->list_get_data2(traversal_ptr2) + 1
					== first_sll_ptr->list_get_data2(trv_next_ptr)) {

					traversal_ptr2 = first_sll_ptr->list_next(traversal_ptr2);
				}

				// For the case of error increasement due to the missing packet
				// ex) (1,1) -> (1,x), x>2
				else if (first_sll_ptr->list_get_data1(traversal_ptr2) == first_sll_ptr->list_get_data1(trv_next_ptr) &&
					(first_sll_ptr->list_get_data2(traversal_ptr2) + 1) != first_sll_ptr->list_get_data2(trv_next_ptr)) {
					
					for (int i = first_sll_ptr->list_get_data2(traversal_ptr2) + 1; i < first_sll_ptr->list_get_data2(trv_next_ptr); i++) {
						outfile << "WARNING: packet " << i << " of message " << first_sll_ptr->list_get_data1(traversal_ptr2) << " is missing" << endl;
					}

					traversal_ptr2 = first_sll_ptr->list_next(traversal_ptr2);
				}

				// For the case of next message number
				// ex) (1,1) -> (m,x), m>1, x can be non-1
				else if (first_sll_ptr->list_get_data1(traversal_ptr2) != first_sll_ptr->list_get_data1(trv_next_ptr)) {
					outfile << "- End Message " << first_sll_ptr->list_get_data1(traversal_ptr2) << endl;
					outfile << endl;
					outfile << "- Message " << first_sll_ptr->list_get_data1(trv_next_ptr) << endl;

					// make warning messages if message does not start with packet number 1
					if (first_sll_ptr->list_get_data2(trv_next_ptr) != 1) {
						for (int i = 1; i < first_sll_ptr->list_get_data2(trv_next_ptr); i++) {
							outfile << "WARNING: packet " << i << " of message " << first_sll_ptr->list_get_data1(trv_next_ptr) << " is missing" << endl;
						}
					}

					traversal_ptr2 = first_sll_ptr->list_next(traversal_ptr2);
				}
				continue;
			}

			// Write contents of list's tail
			outfile << first_sll_ptr->list_get_data3(traversal_ptr2) << endl;
			outfile << "- End Message " << first_sll_ptr->list_get_data1(traversal_ptr2) << endl;
			outfile << endl;

		}
		time(&end);

		// Record running time
		outfile << "Running Time: " << difftime(end, start) << " s" << endl;
	}

  ///////////////////////////////////////////////////////
  //                                                   //
  //  SINGLY LINKED LIST RECEIVER IMPLEMENTATION ABOVE //
  //                                                   //
  ///////////////////////////////////////////////////////

	else {
		cout << "Invalid input" << endl;
	}

	return 0;
}
