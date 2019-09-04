#include <iostream>
#include "student.h"

// included intentionally by code developer
#include <string>
#include <sstream>

// //****************************************************************
// //                   REQUIRED FUNCTIONALITY IN PROJECT
// //****************************************************************

// 1. You need to implement every detail of the function defined below
// 2. You additionally need to implement getInfo methods in each classes.
// 3. You additionally need to implement 'operator overloading' with '==' which compares two students whether all the members are the same


//************************************** Manager Implementation

Manager::Manager()
	: student_number(0) {}


int Manager::add_student(std::string name, int stunum, std::string labname)
{
  // Adds Grad_Student object with given argument
  // Returns the total number of objects in the student array after adding

  if (student_number == MAX_STUDENT_NUMBER) {
      std::cout << "Number of stored students has been maximum. Please delete some students if you want to add more." << std::endl;

	  std::cout << student_number << std::endl;
	  std::cout << "add graduate student DONE" << std::endl;

	  return student_number;
  }

  for (int index = 0; index < student_number; index++) {
      if (*student_list[index] == Grad_Student(name, stunum, labname)) {
		  std::cout << index + 1 << "th student is same as your input!" << std::endl
				    << "Adding student is denied." << std::endl;

		  std::cout << student_number << std::endl;
		  std::cout << "add graduate student DONE" << std::endl;

		  return student_number;
	  }
  }

  student_list[student_number++] = new Grad_Student(name, stunum, labname);

  std::cout << student_number << std::endl;
  std::cout << "add graduate student DONE" << std::endl;
  
  return student_number;
};


int Manager::add_student(std::string name, int stunum, int freshmenclass)
{
  // Creates Undergrad_Student object with given argument
  // Returns the total number of objects in the student array after adding

  if (student_number == MAX_STUDENT_NUMBER) {
	  std::cout << "Number of stored students has been maximum. Please delete some students if you want to add more." << std::endl;

	  std::cout << student_number << std::endl;
	  std::cout << "add undergraduate student DONE" << std::endl;

	  return student_number;
  }

  for (int index = 0; index < student_number; index++) {
      if (*student_list[index] == Undergrad_Student(name, stunum, freshmenclass)) {
	      std::cout << index + 1 << "th student is same as your input!" << std::endl
					<< "Adding student is denied." << std::endl;

		  std::cout << student_number << std::endl;
		  std::cout << "add undergraduate student DONE" << std::endl;

		  return student_number;
	  }
  }

  student_list[student_number++] = new Undergrad_Student(name, stunum, freshmenclass);

  std::cout << student_number << std::endl;
  std::cout << "add undergraduate student DONE" << std::endl;

  return student_number;
};

// You need to implement operator overloading and use it in compare_student

bool Manager::compare_student(int index, std::string name, int stunum, int freshmenclass)
{
  // Compares whether the object with given index argument in the student array is the same to Undergrad_Student object with given arguments followed by index.
  // Returns true if they are the same, false otherwise
  
  if (index > student_number) {
	  std::cout << "There's no such many students in program." << std::endl;
	  std::cout << "There are currently" << student_number << "students' in this program." << std::endl;

	  std::cout << "false" << std::endl;
	  std::cout << "compare to undergraduate student DONE" << std::endl;

	  return false;
  }

  if (*student_list[index - 1] == Undergrad_Student(name, stunum, freshmenclass)){
      std::cout << "It matches!" << std::endl;

	  std::cout << "true" << std::endl;
      std::cout << "compare to undergraduate student DONE" << std::endl;
      
	  return true;
  }

  else {
      std::cout << "It doesn't match!" << std::endl;

	  std::cout << "false" << std::endl;
	  std::cout << "compare to undergraduate student DONE" << std::endl;
	  
	  return false;
  }
};


bool Manager::compare_student(int index, std::string name, int stunum, std::string labname)
{
  // Compares whether the (index argument)th object in the student array is the same to Grad_Student object with given given argument follwed by index.
  // Returns true if they are the same, false otherwise


	if (index <= 0) {
		std::cout << "You should input positive integer for index." << std::endl;

		std::cout << "false" << std::endl;
		std::cout << "compare to graduate student DONE" << std::endl;

		return false;
  }


  if (index > student_number) {
      std::cout << "There's no such many students in program." << std::endl;
	  std::cout << "There are currently " << student_number << " students in this program." << std::endl;

	  std::cout << "false" << std::endl;
	  std::cout << "compare to graduate student DONE" << std::endl;

	  return false;
  }

  if (*student_list[index - 1] == Grad_Student(name, stunum, labname)){
      std::cout << "It matches!" << std::endl;

	  std::cout << "true" << std::endl;
	  std::cout << "compare to graduate student DONE" << std::endl;

	  return true;
  }

  else {
      std::cout << "It doesn't match!" << std::endl;

	  std::cout << "false" << std::endl;
	  std::cout << "compare to graduate student DONE" << std::endl;

	  return false;
  }
};


int Manager::find_student(std::string name, int stunum, std::string labname)
{
  // Finds the Grad_Student object in the student array which is the same to Grad_Student object with given argument
  // This method should print all the information about matched object
  // Returns index of matched object (index of first object = 1), 0 if there's no match

  for (int index = 0; index < student_number; index++) {
      if (*student_list[index] == Grad_Student(name, stunum, labname)){
	      std::cout << index + 1 << "th student is same as your input!" << std::endl;
		  student_list[index]->get_info();

		  std::cout << index + 1 << std::endl;
		  std::cout << "find graduate student DONE" << std::endl;

		  return index + 1;
	  }
  }

  std::cout << "Cannot find graduate student!" << std::endl;

  std::cout << 0 << std::endl;
  std::cout << "find graduate student DONE" << std::endl;
  
  return 0;
};


int Manager::find_student(std::string name, int stunum, int freshmenclass)
{
  // Finds the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument
  // This method should prints all the information about matched object
  // Returns index of matched object (index of first object = 1), 0 if there's no match

  for (int index = 0; index < student_number; index++){
      if (*student_list[index] == Undergrad_Student(name, stunum, freshmenclass)){
			std::cout << index + 1 << "th student is same as your input!" << std::endl;
			student_list[index]->get_info();

			std::cout << index + 1 << std::endl;
			std::cout << "find undergraduate student DONE" << std::endl;
			
			return index + 1;
	  }
  }
  
  std::cout << "Cannot find undergraduate student!" << std::endl;

  std::cout << 0 << std::endl;
  std::cout << "find undergraduate student DONE" << std::endl;

  return 0;

};


int Manager::delete_student(std::string name, int stunum, std::string labname)
{
  // Deletes the Grad_Student object in the student array which is the same to Grad_Student object with given argument, does nothing if there's no matching
  // Returns the total number of objects in the student array after deleting
 for (int index = 0; index < student_number; index++){
	  if (*student_list[index] == Grad_Student(name, stunum, labname)){

		  std::string last_name = student_list[student_number - 1]->get_name();
		  int last_stu_num = student_list[student_number - 1]->get_stu_num();
		  std::string last_special_info = student_list[student_number - 1]->get_special_info();

		  delete student_list[index];
		  std::cout << index + 1 << "th student is deleted!" << std::endl;

		  if (::check_number(last_special_info) == true){  // undergraduate case
			  
			  std::stringstream strstream(last_special_info);
			  int int_last_special_info;
			  strstream >> int_last_special_info;
			  
		      student_list[index] = new Undergrad_Student(last_name, last_stu_num, int_last_special_info);
		  }
		  else {  // graduate case
		    student_list[index] = new Grad_Student(last_name, last_stu_num, last_special_info);
		  }
		  
		  delete student_list[student_number - 1];
		  student_number--;

		  std::cout << student_number << std::endl;
		  std::cout << "delete graduate student DONE" << std::endl;

		  return student_number;
	  }
 }

 std::cout << "None of the student was found with given input" << std::endl;

 std::cout << student_number << std::endl;
 std::cout << "delete graduate student DONE" << std::endl;
 
 return student_number;
};


int Manager::delete_student(std::string name, int stunum, int freshmenclass)
{
 // Deletes the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument, does nothing if there's no matching
 // Returns the total number of objects in the student array after deleting
	for (int index = 0; index < student_number; index++) {
		if (*student_list[index] == Undergrad_Student(name, stunum, freshmenclass)) {

			std::string last_name = student_list[student_number - 1]->get_name();
			int last_stu_num = student_list[student_number - 1]->get_stu_num();
			std::string last_special_info = student_list[student_number - 1]->get_special_info();

			delete student_list[index];
			std::cout << index + 1 << "th student is deleted!" << std::endl;

			if (::check_number(last_special_info) == true){  // undergraduate case
			  
				std::stringstream strstream(last_special_info);
				int int_last_special_info;
				strstream >> int_last_special_info;
				
				student_list[index] = new Undergrad_Student(last_name, last_stu_num, int_last_special_info);
			}
			else {  // graduate case
			  student_list[index] = new Grad_Student(last_name, last_stu_num, last_special_info);
			}	

			delete student_list[student_number - 1];
			student_number--;

			std::cout << student_number << std::endl;
			std::cout << "delete undergraduate student DONE" << std::endl;
			
			return student_number;
		}
	}

 std::cout << "None of the student was found with given input" << std::endl;
 
 std::cout << student_number << std::endl;
 std::cout << "delete undergraduate student DONE" << std::endl;

 return student_number;

};


int Manager::print_all()
{
  // Prints the all the information of existing object in the student array
  // Returns the total number of objects in the student array
  
 for (int index = 0; index < student_number; index++) {
		student_list[index]->get_info();
 }

 std::cout << student_number << std::endl;
 std::cout << "print all DONE" << std::endl;

 return student_number;
}


int Manager::get_student_number() const
{
	return student_number;
}


Manager::~Manager() {
	for (int index = 0; index < student_number; index++) {
		delete student_list[index];
		std::cout << "erased " << index + 1 << "th times!" << std::endl;
	}
}


//************************************** Student Implementation

Student::Student(const std::string& name_string, int num)
	: name(name_string), stu_num(num) {
	// actually Student instance cannot be created in runtime becaust it is abstract class 
}


std::string Student::get_name() const {
	return name;
}


int Student::get_stu_num() const {
	return stu_num;
}


//************************************** Grad_Student Implementation

Grad_Student::Grad_Student(const std::string& name_string, int num, const std::string& lab_name_string)
	:Student(name_string, num), lab_name(lab_name_string) {}

void Grad_Student::get_info() const {
	std::cout << "Graduate Student" << std::endl
			  << "Name: " << name << std::endl
			  << "ID number: " << stu_num << std::endl
		      << "Lab name:" << lab_name << std::endl;
}

std::string Grad_Student::get_special_info() const {
	return lab_name;
}

//************************************** Undergrad_Student Implementation

Undergrad_Student::Undergrad_Student(const std::string& name_string, int num, int class_num)
	:Student(name_string, num), freshmen_class(class_num) {}

void Undergrad_Student::get_info() const {
	std::cout << "Undergraduate Student" << std::endl 
			  << "Name: " << name << std::endl
			  << "ID number: " << stu_num << std::endl
			  << "Class number: " << freshmen_class << std::endl;
}

std::string Undergrad_Student::get_special_info() const {
	int ref_freshmen_class = freshmen_class;

	std::ostringstream ss;
	ss << ref_freshmen_class;
	
	return ss.str();
}

bool operator==(const Student& x, const Student& y)
{
	// operating overloading part. 
	// Check whether two students x, y have same information or not. 
	// Return true if two students are same, false otherwise.
	// p.s. this function must be used in at least "find_student ()" and "compare_student ()"

	if (x.get_special_info() == y.get_special_info() &&
		x.get_name() == y.get_name() &&
		x.get_stu_num() == y.get_stu_num()) {
		return true;
	}

	else {
		return false;
	}
}


bool check_alphabet(std::string& str) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) == false) { // check whether not number

			return false;
		}
	}
	return true;
}

// check all string letters are numbers
bool check_number(std::string& str){
  if ((str[0] >= '0' && str[0] <= '9') or str[0] == '-'){ // check first character whether it's 0~9 or minus or not

    for (unsigned int i = 1; i < str.size(); i++){
      if((str[i] >= '0' && str[i] <= '9') == false) { // check whether not number
		return false;
      }
    }
  }
  else {
    return false;
  }
  return true;
}
