/*******************************************************************************
 * Name    : Jack Byrne
 * Author  : Brian S. Borowski
 * Version : 1.0
 * Date    : September 1, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

double sqrt(double num, double epsilon) {
	if (num < 0) {
			return numeric_limits<double>::quiet_NaN();
		}

	if (num == 0 or num == 1) {
			return num;
		}

	double last_guess = num;
	double next_guess;
	bool valid = 1;
	while (valid) {
		next_guess = .5 *(last_guess + (num / last_guess));
		if (abs(last_guess - next_guess) < epsilon) {
					valid = 0;
				}
		last_guess = next_guess;
	}
	return next_guess;
}

int main(int argc, char *argv[]) {

	double x,e;

	if (argc > 3 or argc < 2) {
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	    }

	istringstream iss;
	iss.str(argv[1]);
	if (!(iss >> x)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}
	else{
		e = .0000001;
	    }
	iss.clear();

	if (argc == 3) {
			iss.str(argv[2]);
			if (!(iss >> e) or e <= 0) {
				cerr << "Error: Epsilon argument must be a positive double." << endl;
				return 1;
			}
		}

	cout << fixed <<setprecision(8) << sqrt(x,e) << endl;
	return 0;
}

