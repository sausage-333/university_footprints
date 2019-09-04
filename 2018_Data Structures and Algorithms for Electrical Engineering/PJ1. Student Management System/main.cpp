#include <iostream>
#include <stdexcept>
#include <string>
#include "student.h"

// included intentionally by code developer
#include <vector>
#include <sstream>

// //****************************************************************
// //                   MAIN FUNCTION IN PROJECT
// //****************************************************************


int main()
{
  char command;
  Manager myman;
  int isgrad;
  std::string name;
  int stunum;
  std::string labname;
  int freshmenclass;
  int index;
  bool isLast=true;


  while(isLast){
	std::cout << "\n\n\n*---------------------Welcome to Student Management System---------------------*" << std::endl;

	std::cout << "What do you want to do?\n1. Add student:a\n2. Compare student:c \n3. Find student:f\n4. Delete student:d\n5. Print all student:p\n6. Quit:q" << std::endl;

	// ******Modify here****** 
	//You need to handle wrong argument format
	std::string inputstring;
	std::getline(std::cin, inputstring);

	command = inputstring.c_str()[0];

		switch (command)
		{
		case 'a': {
			// Type of student you want to add (Graduate student or Undergraduate student)
			std::cout << "Add student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;

			// ******Modify here****** 
			//You need to handle wrong argument format

			std::string inputstra;
			std::getline(std::cin, inputstra);


			if (check_alphabet(inputstra)) {
				std::cout << "Invalid argument" << std::endl;
				break;
			}

			std::stringstream strstreama(inputstra);
			strstreama >> isgrad;

			// -----------------------------------------------------------

			if (isgrad == 1) {
				std::cout << "\nFormat: [name stunum labname]" << std::endl;

				// ******Modify here****** 
				//You need to handle wrong argument format

				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
						input_stream.push_back(input_string);
				}				


				if (input_stream.size() != 3) {
					std::cout << "Please input 3 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[0]) == false) {
					std::cout << "Please input only alphabets for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[1]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[2]) == false) {
					std::cout << "Please input only alphabets for labname." << std::endl;
					input_stream.clear();
					break;
				}


				name = input_stream[0];

				std::stringstream strstream(input_stream[1]);
				strstream >> stunum;

				labname = input_stream[2];

				input_stream.clear();
				myman.add_student(name, stunum, labname);
			}

			else if (isgrad == 0) {
				std::cout << "\nFormat: [name stunum freshmenclass] " << std::endl;

				// ******Modify here****** 
				//You need to handle wrong argument format

				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
					input_stream.push_back(input_string);
				}


				if (input_stream.size() != 3) {
					std::cout << "Please input 3 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[0]) == false) {
					std::cout << "Please input only alphabets for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[1]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[2]) == false) {
					std::cout << "Please input only numbers for freshmenclass." << std::endl;
					input_stream.clear();
					break;
				}


				name = input_stream[0];

				std::stringstream strstream(input_stream[1]);
				strstream >> stunum;

				std::stringstream strstream2(input_stream[2]);
				strstream2 >> freshmenclass;

				input_stream.clear();
				myman.add_student(name, stunum, freshmenclass);
			}
			else {
				std::cout << "Invalid Argument" << std::endl;
			}
		}break;


		case 'c': {
			std::cout << "Compare student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;

			// ******Modify here****** 
			//You need to handle wrong argument format
			std::string inputstra;
			std::getline(std::cin, inputstra);


			if (check_alphabet(inputstra)) {
				std::cout << "Invalid argument" << std::endl;
				break;
			}

			std::stringstream strstreama(inputstra);
			strstreama >> isgrad;

			if (isgrad == 1) {
				std::cout << "\nTarget student\nFormat: [index name stunum labname]" << std::endl;

				// ******Modify here****** 
				//You need to handle wrong argument format

				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
					input_stream.push_back(input_string);
				}


				if (input_stream.size() != 4) {
					std::cout << "Please input 4 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[0]) == false) {
					std::cout << "Please input only numbers for index." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[1]) == false) {
					std::cout << "Please input only numbers for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[2]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[3]) == false) {
					std::cout << "Please input only alphabets for labname." << std::endl;
					input_stream.clear();
					break;
				}


				std::stringstream strstream(input_stream[0]);
				strstream >> index;

				name = input_stream[1];

				std::stringstream strstream2(input_stream[2]);
				strstream2 >> stunum;

				labname = input_stream[3];

				input_stream.clear();
				myman.compare_student(index, name, stunum, labname);
			}

			else if (isgrad == 0) {
				std::cout << "\nTarget student\nFormat: [index name stunum freshmenclass] " << std::endl;


				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
					input_stream.push_back(input_string);
				}


				if (input_stream.size() != 4) {
					std::cout << "Please input 4 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[0]) == false) {
					std::cout << "Please input only numbers for index." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[1]) == false) {
					std::cout << "Please input only alphabets for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[2]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[3]) == false) {
					std::cout << "Please input only numbers for freshmenclass." << std::endl;
					input_stream.clear();
					break;
				}


				std::stringstream strstream3(input_stream[0]);
				strstream3 >> index;

				name = input_stream[1];

				std::stringstream strstream(input_stream[2]);
				strstream >> stunum;

				std::stringstream strstream2(input_stream[3]);
				strstream2 >> freshmenclass;


				myman.compare_student(index, name, stunum, freshmenclass);
			}
			else {
				std::cout << "Invalid Argument" << std::endl;
			}
		}break;

		case 'f': {
			std::cout << "Find student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;

			// ******Modify here****** 
			//You need to handle wrong argument format
			std::string inputstra;
			std::getline(std::cin, inputstra);


			if (check_alphabet(inputstra)) {
				std::cout << "Invalid argument" << std::endl;
				break;
			}

			std::stringstream strstreama(inputstra);
			strstreama >> isgrad;

			if (isgrad == 1) {
				std::cout << "\nFormat: [name stunum labname]" << std::endl;

				// ******Modify here****** 
				//You need to handle wrong argument format


				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
					input_stream.push_back(input_string);
				}


				if (input_stream.size() != 3) {
					std::cout << "Please input 3 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[0]) == false) {
					std::cout << "Please input only alphabets for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[1]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[2]) == false) {
					std::cout << "Please input only alphabets for labname." << std::endl;
					input_stream.clear();
					break;
				}

				name = input_stream[0];

				std::stringstream strstream(input_stream[1]);
				strstream >> stunum;

				labname = input_stream[2];

				input_stream.clear();
				myman.find_student(name, stunum, labname);
			}
			else if (isgrad == 0) {
				std::cout << "\nFormat: [name stunum freshmenclass]" << std::endl;

				// ******Modify here****** 
				//You need to handle wrong argument format
				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
					input_stream.push_back(input_string);
				}


				if (input_stream.size() != 3) {
					std::cout << "Please input 3 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[0]) == false) {
					std::cout << "Please input only alphabets for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[1]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[2]) == false) {
					std::cout << "Please input only numbers for freshmenclass." << std::endl;
					input_stream.clear();
					break;
				}

				name = input_stream[0];

				std::stringstream strstream(input_stream[1]);
				strstream >> stunum;

				std::stringstream strstream2(input_stream[2]);
				strstream2 >> freshmenclass;

				input_stream.clear();
				myman.find_student(name, stunum, freshmenclass);
			}
			else {
				std::cout << "Invalid Argument" << std::endl;
			}
		}break;


		case 'd': {
			std::cout << "Delete student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;

			// ******Modify here****** 
			//You need to handle wrong argument format

			std::string inputstra;
			std::getline(std::cin, inputstra);


			if (check_alphabet(inputstra)) {
				std::cout << "Invalid argument" << std::endl;
				break;
			}

			std::stringstream strstreama(inputstra);
			strstreama >> isgrad;

			if (isgrad == 1) {
				std::cout << "\nFormat: [name stunum labname]" << std::endl;

				// ******Modify here****** 
				//You need to handle wrong argument format
				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
					input_stream.push_back(input_string);
				}


				if (input_stream.size() != 3) {
					std::cout << "Please input 3 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[0]) == false) {
					std::cout << "Please input only alphabets for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[1]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[2]) == false) {
					std::cout << "Please input only alphabets for labname." << std::endl;
					input_stream.clear();
					break;
				}


				name = input_stream[0];

				std::stringstream strstream(input_stream[1]);
				strstream >> stunum;

				labname = input_stream[2];

				input_stream.clear();
				myman.delete_student(name, stunum, labname);
			}
			else if (isgrad == 0) {
				std::cout << "\nFormat: [name stunum freshmenclass]" << std::endl;

				// ******Modify here****** 
				//You need to handle wrong argument format
				std::string input_string;
				std::string end_of_stream;
				std::vector<std::string> input_stream;  // input vector stream

				std::getline(std::cin, end_of_stream);   // 사용자가 엔터 칠 때까지 입력함
				std::istringstream iss(end_of_stream);
				while (iss >> input_string) {
					input_stream.push_back(input_string);
				}


				if (input_stream.size() != 3) {
					std::cout << "Please input 3 parameters with whitespace." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_alphabet(input_stream[0]) == false) {
					std::cout << "Please input only alphabets for name." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[1]) == false) {
					std::cout << "Please input only numbers for stunum." << std::endl;
					input_stream.clear();
					break;
				}

				if (check_number(input_stream[2]) == false) {
					std::cout << "Please input only numbers for freshmenclass." << std::endl;
					input_stream.clear();
					break;
				}

				name = input_stream[0];

				std::stringstream strstream(input_stream[1]);
				strstream >> stunum;

				std::stringstream strstream2(input_stream[2]);
				strstream2 >> freshmenclass;

				input_stream.clear();
				myman.delete_student(name, stunum, freshmenclass);
			}
			else {
				std::cout << "Invalid Argument" << std::endl;
			}
		}break;

		case 'p': {
			std::cout << "Print all executed" << std::endl;
			myman.print_all();
		}break;

		case 'q': {
			std::cout << "Quit" << std::endl;
			isLast = false;
		}break;

		default: {
			std::cout << "Invalid argument" << std::endl;
		}break;
		}
	}
  return 0;
}