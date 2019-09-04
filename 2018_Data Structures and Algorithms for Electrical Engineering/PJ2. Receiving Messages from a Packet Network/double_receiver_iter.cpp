#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "double_list_iter.h"

using namespace std;

/* YOU CAN CHANGE INCLUDED HEADERS ^0^ */

int main(int argc, char* argv[])
{
  /* 1st arg: input file name , 2nd arg: output file name */
	if (argc == 3) {

		ifstream myfile;

		// open 1st argument
		myfile.open(argv[1], fstream::in);

		// list containing file's message
		double_list dlist;

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

			// No need to sort or replace same message & packet number
			// Our goal is just finding 4th message exists 
			dlist.d_list_insert_front(new d_list_elem(data1, data2, data3));
		}

		// output file stream outfile object named as 2nd arg
		// variable name fout is used in given skeleton code
		ofstream fout(argv[2]);

		double_list::Iter p = find(dlist.begin(), dlist.end(), 4);
		if (p == dlist.end())
		{
			fout << "No 4th message" << endl;
		}
		else
		{
			fout << "4th message exists" << endl;
		}
	}

	else {
		cout << "Invalid input" << endl;
	}

  return 0;
}
