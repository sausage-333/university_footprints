// //***************************************************************
// //                   CLASS USED IN PROJECT
// //****************************************************************
#define MAX_STUDENT_NUMBER 300 // Maximum number of Student class pointers

class Student{
	// ******Modify here******
	// You need to properly define member variable in Student class
 private:

 protected:
	std::string name;
	int stu_num;

 public:
	// ******Modify here******
	// You need to implement get function which prints out every information about student argument in pure virtual function here
	Student(const std::string& name_string, int num);
	virtual void get_info() const = 0;  // pure virtual function
	virtual std::string get_special_info() const = 0;
	virtual std::string get_name() const ;
	virtual int get_stu_num() const ;
};

class Grad_Student: public Student{
	// ******Modify here******
	// You need to properly define member variable in Grad_Student class
 private:
	std::string lab_name;

 protected:

 public:	
	// ******Modify here******
	// You need to implement get function in detail
	Grad_Student(const std::string& name_string, int num, const std::string& lab_name_string);
	virtual void get_info() const;
	virtual std::string get_special_info() const;
};

class Undergrad_Student: public Student{
	// ******Modify here******
	// You need to properly define member variable in Undergrad_Student class
 private:
	 int freshmen_class;

 protected:

 public:
	// ******Modify here******
	// You need to implement get function in detail
	Undergrad_Student(const std::string& name_string, int num, int class_num);
	virtual void get_info() const;
	virtual std::string get_special_info() const;
};

bool operator==(const Student& x, const Student& y);
bool check_number(std::string& str);
bool check_alphabet(std::string& str);

class Manager {
	// ******Modify here******
	// You need to properly define member variable in Manager class
private:
	Student* student_list[MAX_STUDENT_NUMBER];
	int student_number; // number of student stored in array

protected:

public:
	// ******Modify here******
	// You need to implement every methods in Manager class
	Manager();
	int add_student(std::string name, int stunum, std::string labname);
	int add_student(std::string name, int stunum, int freshmenclass);
	bool compare_student(int index, std::string name, int stunum, std::string labname);
	bool compare_student(int index, std::string name, int stunum, int freshmenclass);
	int find_student(std::string name, int stunum, std::string labname);
	int find_student(std::string name, int stunum, int freshemenclass);
	int delete_student(std::string name, int stunum, std::string labname);
	int delete_student(std::string name, int stunum, int freshmenclass);
	int print_all();
	int get_student_number() const;
	~Manager();

};
