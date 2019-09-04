/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Yoonpyo Koo
*
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include "avl_tree.h"

/* Include more if you need */
#include <list>
#include <iterator>
#include <algorithm>
#include <cctype>
//#include <ctime>

using namespace std;
/*
/* Use these functions to replace words in a string.
* Make sure you add -std=c++11 option when you compile.
*/
void replace_all(string& str, string& from, string& to) {

	std::regex reg1("^" + from + " ");
	str = string(std::regex_replace(str, reg1, to + " "));

	std::regex reg2(" " + from + " ");
	str = string(std::regex_replace(str, reg2, " " + to + " "));
	str = string(std::regex_replace(str, reg2, " " + to + " "));

	std::regex reg3("^" + from + "$");
	str = string(std::regex_replace(str, reg3, to));

	std::regex reg4(" " + from);
	str = string(std::regex_replace(str, reg4, " " + to));

	std::regex reg5(" " + from + " ");
	str = string(std::regex_replace(str, reg5, " " + to));

	std::regex reg6("^" + from);
	str = string(std::regex_replace(str, reg6, to + " "));
}

/* Use this function to execute insensitve word comparing.
* This function compare words by converting to uppercase.
*/

int main(int argc, char* argv[])
{
	// 1st arg: input file name, 2nd arg: output file name

	/* T_start = the time that reciever starts */
	//time_t start1, start2, end1, end2;
	//time(&start1);

	// STEP 1: �ܾ���� �а�, AVLTree�� �����ϴ� ����
	if (argc != 3) {
		cout << "Invalid input format." << endl;
	}

	ifstream myfile;
	myfile.open(argv[1], fstream::in);

	// list of string to store each line
	list<string> line_list;
	string line;

	// put lines into line list
	while (getline(myfile, line)) {
		line_list.push_back(line);
	}

	// line list�� ��ȸ�ϴ� �ݺ���, line_it.
	list<string>::iterator line_it = line_list.begin();

	int line_number = 1;

	AVLTree<list<int>> avlt;

	// �� line list element�� �����ؼ� �� line���� word�� �̾Ƴ���.
	// �� �ܾ tree�� �����Ѵ�.
	// ���������� �ش� ��忡 ������ line number�� �����Ѵ�.
	for (line_it; line_it != line_list.end(); ++line_it) {

		istringstream delimiter(*line_it);

		// �̾Ƴ� �ܾ ���� word�� ����
		while (delimiter) {
			string word;
			delimiter >> word;

			// �ش� ���� �� line�̶�� �������� ����.
			if (word == "") {
				continue;
			}

			avlt.insert(word);
			avlt.search(word)->value->push_back(line_number);
		}

		// next line number
		line_number++;
	}

	//time(&end1);

	//cout << "Running Time for inserting all words in AVL Tree: " << difftime(end1, start1) << " s" << endl;

	// ����ڷκ��� Command�� �޾�, input file�� ���� ��ü �۾� �ǽ�.

	string command, word1, word2;

	do {

		cin >> command;

		if (command == "R") {

			cin >> word1 >> word2;

			//time(&start2);

			// ��ü�� ���ڿ� ��ü�� ���ڸ� �빮�ڷ� ����� �ٸ� ������ ����
			string u_word1(word1);
			transform(u_word1.begin(), u_word1.end(), u_word1.begin(), ::toupper);

			string u_word2(word2);
			transform(u_word2.begin(), u_word2.end(), u_word2.begin(), ::toupper);

			cout << endl;

			if (avlt.is_external(avlt.search(word1))) {
				cout << "There's no given word in the input file" << endl;
			}

			// ���� ���� �ܾ �ΰ� ��ü�Ϸ� �ߴٸ�, ���� �޽��� ǥ��.
			else if (u_word1.compare(u_word2) == 0) {
				cout << "Error: replacing words are the same." << endl;
			}

			else {
				// ��ü�� ���ڸ� tree�� �����ϰ�
				// ��ü�Ǳ� ���� word�� ������ �ִ� ���� line ������ ���� �޾ƿ�.
				// �� ���� ��ü�� word�� list���� ����
				
				avlt.insert(word2);
				AVLNode<list<int>>* word2_node = avlt.search(word2);
				*(word2_node->value) = *(avlt.search(word1)->value);

				avlt.remove(word1);

				// ��ü�� ���ڰ� �־�� �ϴ� line�� ���� list�� ��ȸ�ϴ� �ݺ��� line_num_it
				list<int>* num_list = word2_node->value;
				list<int>::iterator num_it = num_list->begin();
				int pre_index = 0;

				// value�� ����� int�� �������� �ش��ϴ� line�� ã�ư�
				for (num_it; num_it != num_list->end(); num_it++) {

					if (*num_it == 0) {
						break;
					}

					// ���� num_list�� ���� ���Ұ� �� ���� ������, �� ���� �پ� ����
					// ���� �� ������ ���� �ܾ �� ���� ó���ϱ� ����.
					if (*num_it == pre_index) {
						continue;
					}

					//pre_index update;
					pre_index = *num_it;

					// line_it�� line_list�� �������� �ΰ�,
					// num_it�� �����ϴ� line number���� 1�� �� ��ŭ �ݺ��� �̵�. 
					line_it = line_list.begin();
					advance(line_it, *num_it - 1);

					// ��ü�� �ܾ �ִ� line�� ã�Ҵ�.
					istringstream rep_delimiter(*line_it);

					cout << "< " << *line_it << endl;

					// delimits with whitespace
					while (rep_delimiter) {

						// �ش� ���� �ܾ���� �ϳ��ϳ� �̾�, �ٸ� ������ �빮�ڷ� ����
						string word;
						rep_delimiter >> word;

						string u_word(word);
						transform(u_word.begin(), u_word.end(), u_word.begin(), ::toupper);

						if (u_word.compare(u_word1) == 0) {

							replace_all(*line_it, word, word2);

						}
					}

					cout << "> " << *line_it << endl;
					cout << endl;

				}

				//  ��� line number�� ��ȸ�� �Ŀ���, �ݵ�� line_it�� ���ڸ��� �������ƾ� ��
				line_it = line_list.begin();
			}
			
			//time(&end2);

			//cout << "It took " << difftime(end2, start2) << " s to replace word in AVL Tree." << endl;
		}
		else if (command == "Q") {
			break;
		}
		else {
			cout << "Wrong input." << endl;
		}
	} while (command != "Q");

	// outputfile�� �ۼ�

	line_it = line_list.begin();

	ofstream outfile(argv[2]);

	for (line_it; line_it != line_list.end(); line_it++) {
		outfile << *line_it << endl;
	}

	return 0;

}