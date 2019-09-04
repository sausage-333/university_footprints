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

	// STEP 1: 단어들을 읽고, AVLTree에 저장하는 과정
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

	// line list를 순회하는 반복자, line_it.
	list<string>::iterator line_it = line_list.begin();

	int line_number = 1;

	AVLTree<list<int>> avlt;

	// 각 line list element를 참조해서 각 line마다 word를 뽑아낸다.
	// 각 단어를 tree에 삽입한다.
	// 마지막으로 해당 노드에 등장한 line number를 삽입한다.
	for (line_it; line_it != line_list.end(); ++line_it) {

		istringstream delimiter(*line_it);

		// 뽑아낸 단어를 변수 word에 저장
		while (delimiter) {
			string word;
			delimiter >> word;

			// 해당 줄이 빈 line이라면 삽입하지 않음.
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

	// 사용자로부터 Command를 받아, input file의 글자 대체 작업 실시.

	string command, word1, word2;

	do {

		cin >> command;

		if (command == "R") {

			cin >> word1 >> word2;

			//time(&start2);

			// 대체될 문자와 대체할 문자를 대문자로 만들어 다른 변수에 저장
			string u_word1(word1);
			transform(u_word1.begin(), u_word1.end(), u_word1.begin(), ::toupper);

			string u_word2(word2);
			transform(u_word2.begin(), u_word2.end(), u_word2.begin(), ::toupper);

			cout << endl;

			if (avlt.is_external(avlt.search(word1))) {
				cout << "There's no given word in the input file" << endl;
			}

			// 만약 같은 단어를 두고 대체하려 했다면, 에러 메시지 표시.
			else if (u_word1.compare(u_word2) == 0) {
				cout << "Error: replacing words are the same." << endl;
			}

			else {
				// 대체할 문자를 tree에 삽입하고
				// 대체되기 전의 word가 가지고 있던 등장 line 정보를 복사 받아옴.
				// 그 다음 대체될 word는 list에서 삭제
				
				avlt.insert(word2);
				AVLNode<list<int>>* word2_node = avlt.search(word2);
				*(word2_node->value) = *(avlt.search(word1)->value);

				avlt.remove(word1);

				// 대체할 문자가 있어야 하는 line이 적힌 list를 순회하는 반복자 line_num_it
				list<int>* num_list = word2_node->value;
				list<int>::iterator num_it = num_list->begin();
				int pre_index = 0;

				// value에 저장된 int를 바탕으로 해당하는 line에 찾아감
				for (num_it; num_it != num_list->end(); num_it++) {

					if (*num_it == 0) {
						break;
					}

					// 만약 num_list의 다음 원소가 전 원소 같으면, 그 경우는 뛰어 넘음
					// 여러 번 등장한 같은 단어를 한 번에 처리하기 때문.
					if (*num_it == pre_index) {
						continue;
					}

					//pre_index update;
					pre_index = *num_it;

					// line_it을 line_list의 시작점에 두고,
					// num_it이 참조하는 line number에서 1을 뺀 만큼 반복자 이동. 
					line_it = line_list.begin();
					advance(line_it, *num_it - 1);

					// 대체할 단어가 있는 line을 찾았다.
					istringstream rep_delimiter(*line_it);

					cout << "< " << *line_it << endl;

					// delimits with whitespace
					while (rep_delimiter) {

						// 해당 줄의 단어들을 하나하나 뽑아, 다른 변수에 대문자로 저장
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

				//  모든 line number를 순회한 후에는, 반드시 line_it를 제자리에 돌려놓아야 함
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

	// outputfile에 작성

	line_it = line_list.begin();

	ofstream outfile(argv[2]);

	for (line_it; line_it != line_list.end(); line_it++) {
		outfile << *line_it << endl;
	}

	return 0;

}