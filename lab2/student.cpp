/*******************************************************************************
 * Name    : Jack Byrne
 * Author  : Brian S. Borowski
 * Version : 1.0
 * Date    : September 9, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Student {
	public:
		Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

		string full_name()const{
			return first_ + " " +last_;
		}
		int id()const{
			return id_;
		}
		float gpa()const{
			return gpa_;
		}
		void print_info()const{
			cout << full_name() <<", GPA: " << fixed << setprecision(2) << gpa() << ", ID: " << id() << endl;
		}


	private:
		string first_;
		string last_;
		float gpa_;
		int id_;
	};

vector<Student> find_failing_students(const vector<Student> &students) {
	vector<Student> failing_students;

    for(const auto &student : students) {
        if(student.gpa() < 1) {
            failing_students.push_back(student);
            }
        }
	//Iteratesthroughthestudentsvector,appendingeachstudentwhosegpais
	//lessthan1.0tothefailing_studentsvector.returnfailing_students;
	return failing_students;
}

/***TakesavectorofStudentobjectsandprintsthemtothescreen.*/
void print_students(const vector<Student> &students) {
    for(const auto &student : students) {
        student.print_info();
    }
	//Iteratesthroughthestudentsvector,callingprint_info()foreachstudent.
	}


// print_info() should print in the format (GPA has 2 decimal places):
// Bob Smith, GPA: 3.50, ID: 20146

/**
 * Allows the user to enter information for multiple students, then
 * find those students whose GPA is below 1.0 and prints them to the
 * screen.
 */

int main() {
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;
	do {
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;
		while (gpa < 0 || gpa > 4) {
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	} while (repeat == 'Y' || repeat == 'y');
	cout << endl << "All students:" << endl;
	print_students(students);


	cout << endl << "Failing students:";
    vector<Student> failing_students = find_failing_students(students);
    if(!(failing_students.empty())){
        cout << endl;
        print_students(failing_students);
    }
    else{
        cout << " None" << endl;
    }
	// TODO
	// Print a space and the word 'None' on the same line if no students are
	// failing.
	// Otherwise, print each failing student on a separate line.
	return 0;
}

