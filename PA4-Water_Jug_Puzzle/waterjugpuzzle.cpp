/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Adam Anikiej and Jack Byrne
 * Date        : 10/16/2021
 * Description : Solves the water jug problem using BFS.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
			a(_a), b(_b), c(_c), directions(_directions), parent(nullptr) {
	}

	//~State() {
	//	delete parent;
	//}

	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << directions << " (" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

/**
 * Method used for verifying if command line arguments are valid, if not then print appropriate error.
 * checking for validity includes:
 * argument is number
 * jug goal is less than or equal to jug capacity
 * total jug goal must equal to jug C capacity
 */
bool validArgument(char *const arguments[]) {
	char letters[3] = { 'A', 'B', 'C' };

	//check if arguments are valid numbers
	//go through each argument
	for (int i = 1; i < 7; i++) {
		//scan through whole argument and make sure each character is a digit
		for (size_t j = 0; j < strlen(arguments[i]); j++) {
			if (!isdigit(arguments[i][j])) { //check if number
				if (i < 3) { //capacity
					cerr << "Error: Invalid capacity '" << arguments[i]
							<< "' for jug " << letters[(i - 1) % 3] << "."
							<< endl;
				} else { //goal
					cerr << "Error: Invalid goal '" << arguments[i]
							<< "' for jug " << letters[(i - 1) % 3] << "."
							<< endl;
				}
				return false;
			}
		}
	}
	//check to make sure capacities aren't zero
	for (int i = 1; i < 4; i++) {
		if (stoi(arguments[i]) == 0) {
			cerr << "Error: Invalid capacity '0' for jug " << letters[i-1] << "." << endl;
			return false;
		}
	}

	//arguments are valid numbers, check for validity of capacities
	//check to see if their goal state is less than capacity
	for (int i = 1; i < 4; i++) {
		if (stoi(arguments[i]) < stoi(arguments[i + 3])) {
			cerr << "Error: Goal cannot exceed capacity of jug "
					<< letters[i - 1] << "." << endl;
			return false;
		}
	}

	//arguments have valid capacities, check for total capacity
	int sum = 0;
	for (int i = 4; i < 7; i++) {
		sum += stoi(arguments[i]);
	}
	if (sum != stoi(arguments[3])) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return false;
	}

	//arguments are completely valid
	return true;
}

/*
 * Format if success:
 * Initial state. (0, 0, 8)
 * Pour 5 gallons from C to B. (0, 5, 3)
 * Pour 3 gallons from B to A. (3, 2, 3)
 * Pour 3 gallons from A to C. (0, 2, 6)
 *
 * Format for failure:
 * No solution.
 */

/**
 * Actual method for breadth first search algorithm on water jug puzzle
 * takes in 6 integers for capacities and goals of jugs
 * prints result accordingly, with first being first
 */
void waterJug(int capA, int capB, int capC, int goalA, int goalB, int goalC) {

	//creating 2d array (connections) of size (A+1)(B+1) used for storing connected states
	State ***connections = new State**[capA + 1];
	//insert array into each row of connections to complete creation of 2d array
	for (int i = 0; i < capA + 1; i++) {
		//create an arr of pointers for each row
		connections[i] = new State*[capB + 1];
		//for loop for filling each spot of arr with nullptrs
		for (int j = 0; j < capB + 1; j++) {
			connections[i][j] = nullptr;
		}
	}

	//vector used for storing result
	vector<State*> result;

	//queue used for breadth first search
	queue<State*> toExplore;

	stack<State*> found;

	//put starting state into queue
	State *initial = new State(0, 0, capC, "Initial state.");
	toExplore.push(initial);

	//put starting state into connections
	connections[0][0] = initial;

	//main bfs loop
	while (!toExplore.empty()) {
		State *current = toExplore.front();
		toExplore.pop();

		//check to see if current state is goal state
		if (current->a == goalA && current->b == goalB && current->c == goalC) {
			//store into results the path of states
			result.push_back(current);
			State *temp = current->parent;

			while (temp != nullptr) {
				result.push_back(temp);
				temp = temp->parent;

			}

			//printing solution in correct order (reverse of result)
			for (int i = result.size() - 1; i >= 0; i--) {
				cout << result[i]->to_string() << endl;
			}

			//delete 2d array connections
			for (int i = 0; i < capA + 1; i++) {
				delete[] connections[i];
				//for (int j = 0 ; j < capB + 1; j++)
				//{
					
				//}
			}
			delete[] connections;

			while(!found.empty()){
				State *top = found.top();
				found.pop();
				delete top;
			}

			delete initial;

			return;
		}


		//1) Pour from C to A
		if ((current->c != 0) && (current->a != capA)) {
			State *c2a;
			string dir = "";

			if (current->c >= capA - current->a) {
				//pouring into a until a full
				if (capA - current->a == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from C to A.";
				} else {
					dir = "Pour " + to_string((capA - current->a)) +  " gallons from C to A.";
				}
				c2a = new State(capA, current->b, current->c - (capA - current->a), dir);
			} else {
				//else (pouring into a until c empty)
				if (current->c == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from C to A.";

				} else {
					dir = "Pour " + to_string(current->c) + " gallons from C to A.";
				}
				c2a = new State(current->a + current->c, current->b, 0, dir);
			}
			//Check if this state has already been made. if no, push state
			if (connections[c2a->a][c2a->b] == nullptr) {
				found.push(c2a);
				connections[c2a->a][c2a->b] = c2a;
				c2a->parent = current;
				toExplore.push(c2a);
			}else{
				delete c2a;
			}
		}

		//2)Pour from B to A
		//if (current->b >= capA - current->a) {
		//pour til a is full
		// State(capA, current->b-(capA-current->a),current->c)
		//pour til b is empty
		// State(current->a+current->b, 0, current->c)
		if ((current->b != 0) && (current->a != capA)) {
			State *b2a;
			string dir = "";

			if (current->b >= capA - current->a) {
				//pouring into a until a full
				if (capA - current->a == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from B to A.";
				} else {
					dir = "Pour " + to_string((capA - current->a)) + " gallons from B to A.";
				}
				b2a = new State(capA, current->b - (capA - current->a), current->c, dir);
			} else {
				//else (pouring into a until b empty)
				if (current->b == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from B to A.";
				} else {
					dir = "Pour " + to_string(current->b)
							+ " gallons from B to A.";
				}
				b2a = new State(current->a + current->b, 0, current->c, dir);
			}
			//Check if this state has already been made. if no, push state
			if (connections[b2a->a][b2a->b] == nullptr) {
				found.push(b2a);
				connections[b2a->a][b2a->b] = b2a;
				b2a->parent = current;
				toExplore.push(b2a);
			}else{
				delete b2a;
			}
		}

		//3)Pour from C to B
		//if (current->c >= capB - current->b) {
		//pour til b is full
		// State(current->a, capB ,current->c-(capb-current->b))
		//pour til c is empty
		// State(current->a, current->b+current->c, 0)
		if ((current->c != 0) && (current->b != capB)) {
			State *c2b;
			string dir = "";

			if (current->c >= capB - current->b) {
				//pouring into b until b full
				if (capB - current->b == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from C to B.";
				} else {
					dir = "Pour " + to_string((capB - current->b))
							+ " gallons from C to B.";
				}
				c2b = new State(current->a, capB,
						current->c - (capB - current->b), dir);
			} else {
				//else (pouring into b until c empty)
				if (current->c == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from C to B.";

				} else {
					dir = "Pour " + to_string(current->c)
							+ " gallons from C to B.";
				}
				c2b = new State(current->a, current->b + current->c, 0, dir);
			}
			//Check if this state has already been made. if no, push state
			if (connections[c2b->a][c2b->b] == nullptr) {
				found.push(c2b);
				connections[c2b->a][c2b->b] = c2b;
				c2b->parent = current;
				toExplore.push(c2b);
			}else{
				delete c2b;
			}
		}

		//4)Pour from A to B
		//if (current->a >= capB - current->b) {
		//pour till b is full
		// State(current->a - (capB-current->b), capB ,current->c)
		//pour till a is empty
		// State(0, current->b+current->a, current->c)
		if ((current->a != 0) && (current->b != capB)) {
			State *a2b;
			string dir = "";
			if (current->a >= capB - current->b) {
				//pouring into a until b full
				if (capB - current->b == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from A to B.";
				} else {
					dir = "Pour " + to_string((capB - current->b)) + " gallons from A to B.";
				}
				a2b = new State(current->a - (capB - current->b), capB,	current->c, dir);
			} else {
				//else (pouring into b until a empty)
				if (current->a == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from A to B.";

				} else {
					dir = "Pour " + to_string(current->a) + " gallons from A to B.";
				}
				a2b = new State(0, current->b+current->a, current->c, dir);
			}
			//Check if this state has already been made. if no, push state
			if (connections[a2b->a][a2b->b] == nullptr) {
				found.push(a2b);
				connections[a2b->a][a2b->b] = a2b;
				a2b->parent = current;
				toExplore.push(a2b);
			}else{
				delete a2b;
			}
		}

		//5)Pour from B to C
		//if (current->b >= capC - current->c) {
		//pour till c is full
		// State(current->a, current->b-(capC-current->c),capC)
		//pour till b is empty
		// State(current->a, 0, current->b+current->c)
		if ((current->b != 0) && (current->c != capC)) {
			State *b2c;
			string dir = "";
			if (current->b >= capC - current->c) {
				//pouring into a until a full
				if (capC - current->c == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from B to C.";
				} else {
					dir = "Pour " + to_string((capC - current->c)) + " gallons from B to C.";
				}
				b2c = new State(current->a, current->b - (capC - current->c), capC, dir);
			} else {
				//else (pouring into a until b empty)
				if (current->b == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from B to C.";

				} else {
					dir = "Pour " + to_string(current->b) + " gallons from B to C.";
				}
				b2c = new State(current->a, 0, current->b + current->c, dir);
			}
			//Check if this state has already been made. if no, push state
			if (connections[b2c->a][b2c->b] == nullptr) {
				found.push(b2c);
				connections[b2c->a][b2c->b] = b2c;
				b2c->parent = current;
				toExplore.push(b2c);
			}else{
				delete b2c;
			}
		}

		//6)Pour from A to C
		//if (current->a >= capC - current->c) {
		//pour til b is full
		// State(current->a - (capC-current->c), current->b ,capC)
		//pour til a is empty
		// State(0, current->b, current->c+current->a)
		if ((current->a != 0) && (current->c != capC)) {
			State *a2c;
			string dir = "";
			if (current->a >= capC - current->c) {
				//pouring into a until a full
				if (capC - current->c == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from A to C.";
				} else {
					dir = "Pour " + to_string((capC - current->c)) + " gallons from A to C.";
				}
				a2c = new State(current->a - (capC - current->c), current->b, capC, dir);
			} else {
				//else (pouring into a until b empty)
				if (current->a == 1) {
					//pouring a gallon
					dir = "Pour 1 gallon from A to C.";

				} else {
					dir = "Pour " + to_string(current->a) + " gallons from A to C.";
				}
				a2c = new State(0, current->b, current->c + current->a, dir);
			}
			//Check if this state has already been made. if no, push state
			if (connections[a2c->a][a2c->b] == nullptr) {
				found.push(a2c);
				connections[a2c->a][a2c->b] = a2c;
				a2c->parent = current;
				toExplore.push(a2c);
			}else{
				delete a2c;
			}
		}
	}

	delete initial;
	
	cout << "No solution." << endl;

	return;
}

int main(int argc, char *const argv[]) {
	//check if there is exactly 7 arguments (including ./fileName)
	if (argc != 7) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	//validate command line arguments
	if (!validArgument(argv)) {
		return 1;
	}

	//run water jug algorithm
	waterJug(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));

	return 0;
}
