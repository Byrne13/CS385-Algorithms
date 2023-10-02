/*******************************************************************************
 * Name        : shortestpaths.h
 * Author      : Adam Anikiej and Jack Byrne
 * Version     : 1.0
 * Date        : 11/29/2021
 * Description : Implementation of Floyd's Algorithm for All-Pairs Shortest-Paths.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <limits>

using namespace std;

const long INFINITY = numeric_limits<long>::max(); //finds largest possible long

/**
 * Determines the length of a long number (the number of digits in the number)
 */
int len(long num) {
	if (num == 0)
		return 1;
	int length = 0;
	while (num > 0) {
		num /= 10;
		length++;
	}
	return length;
}

/**
 * Displays the matrix on the screen formatted as a table.
 */
void display_table(vector<vector<long>> &matrix, const string &label, const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix.size(); j++) {
            long cell = matrix[i][j];
            if (cell < INFINITY && cell > max_val) {

                max_val = matrix[i][j];
            }
        }
    }

    int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(matrix.size()), max_val));
    cout << ' ';
    for (size_t j = 0; j < matrix.size(); j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (size_t i = 0; i < matrix.size(); i++) {
        cout << static_cast<char>(i + 'A');
        for (size_t j = 0; j < matrix[0].size(); j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INFINITY) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}


void print_path(vector<vector<long>> matrix, int i, int j) {
	if (matrix[i][j] == INFINITY) {
		cout << (char)(i + 65) << " -> " << (char)(j + 65);
		return;
	} else {
		long intermediate = matrix[i][j];
		if (matrix[i][intermediate] == INFINITY && matrix[intermediate][j] == INFINITY) {
			cout << (char)(i + 65) << " -> " << (char)(intermediate + 65) << " -> " << (char)(j + 65);
		} else if (matrix[i][intermediate] == INFINITY && matrix[intermediate][j] != INFINITY) {
			cout << (char)(i + 65) << " -> ";
			print_path(matrix, intermediate, j);
		} else if (matrix[i][intermediate] != INFINITY && matrix[intermediate][j] == INFINITY) {
			print_path(matrix, i, intermediate);
			cout << " -> " << (char)(j + 65);
		} else {
			print_path(matrix, i, intermediate);
			cout << " -> ";
			if (matrix[intermediate][j] != INFINITY) {
				print_path(matrix, matrix[intermediate][j], j);
			} else {
				cout << (char)(j + 65);
			}
		}

	}
}

int main(int argc, const char *argv[]) {
	//create adjacency matrix of all 0s of size vertex_count
	vector<vector<long>> distance_matrix;

	//make sure right amount of command line arguments exist
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}
	//create ifstream object
	ifstream input_file(argv[1]);
	//make sure file exists
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	input_file.exceptions(ifstream::badbit);
	string line;
	try {
		unsigned int line_number = 1;
		int vertex_count;
		while (getline(input_file, line)) {
			//see if first input is correct
			if (line_number == 1) {
				try {
					if (stoi(line) < 1 || stoi(line) > 26) {
						cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
						return 1;
					}
					vertex_count = stoi(line);
				} catch (exception &err) {
					cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
					return 1;
				}
				distance_matrix.resize(vertex_count);
				for (int i = 0; i < vertex_count; i++) {
					distance_matrix[i] = vector<long>(vertex_count);
				}

			} else {
				//create string stream of current line
				stringstream ss(line);
				string s;
				int component_count = 0;
				int first_vertex;
				int second_vertex;
				int weight;
				while (getline(ss, s, ' ')) {
					//see if first component is valid
					try {
						if (component_count == 0 && (s.length() != 1 || s[0] < 65 || s[0] > 65 + vertex_count - 1)) {
							cerr << "Error: Starting vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count-1) << "." << endl;	
							return 1;
						}
					} catch (exception &err) {
						cerr << "Error: Starting vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count-1) << "." << endl;
						return 1;
					}
					//see if second component is valid
					try {
						if (component_count == 1 && (s.length() != 1 || s[0] < 65 || s[0] > 65 + vertex_count - 1)) {
							cerr << "Error: Ending vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count-1) << "." << endl;
							return 1;
						}
					} catch (exception &err) {
						cerr << "Error: Ending vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count-1) << "." << endl;
						return 1;
					}
					//see if third component is valid
					try {
						if (component_count == 2 && stoi(s) < 1) {
							cerr << "Error: Invalid edge weight '" << s << "' on line " << line_number << "." << endl;
							return 1;
						}
					} catch (exception &err) {
						cerr << "Error: Invalid edge weight '" << s << "' on line " << line_number << "." << endl;
						return 1;
					}
					if (component_count == 0) {
						first_vertex = int(s[0]);
					} else if (component_count == 1) {
						second_vertex = int(s[0]);
					} else if (component_count == 2) {
						weight = stoi(s);
					}

					component_count++;
				}
				//see if each line has 3 components
				if (component_count != 3) {
					cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
					return 1;
				}
				int row = first_vertex - 65;
				int col = second_vertex - 65;
				distance_matrix[row][col] = weight;
			}
			++line_number;
		}
		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}
	long matrix_size = distance_matrix.size();
	//making weights in matrix that are at zero and not on diagonal and setting them to infinity
	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (i !=j && distance_matrix[i][j] == 0)
				distance_matrix[i][j] = INFINITY;
		}
	}

	//make two copies of distance matrix for generating path lengths matrix and intermediate vertices matrix
	vector<vector<long>> path_lengths_matrix(matrix_size);
	for (int i = 0; i < matrix_size; i++) {
		path_lengths_matrix[i] = vector<long>(matrix_size);
	}

	vector<vector<long>> intermediate_vertices_matrix(matrix_size);
	for (int i = 0; i < matrix_size; i++) {
		intermediate_vertices_matrix[i] = vector<long>(matrix_size);
	}

	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			path_lengths_matrix[i][j] = distance_matrix[i][j];
			intermediate_vertices_matrix[i][j] = INFINITY;
		}
	}

	//Floyd's algorithm for shortest paths page 338 in textbook
  	for (int k = 0; k < matrix_size; k++) {
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
				if (path_lengths_matrix[i][k] == INFINITY || path_lengths_matrix[k][j] == INFINITY ){
					continue;
				}
				long sum = path_lengths_matrix[i][k] + path_lengths_matrix[k][j];
				// D[i,j] = min{D[i, j], D[i, k] + D[k, j ]}	
				if (sum < path_lengths_matrix[i][j]){
					path_lengths_matrix[i][j] = sum;
					intermediate_vertices_matrix[i][j] = k;
				}
			}
		}
	  }

	//printing matrices
	display_table(distance_matrix, "Distance matrix:", false);
	display_table(path_lengths_matrix, "Path lengths:", false);
	display_table(intermediate_vertices_matrix, "Intermediate vertices:", true);


	//Display Paths	
	for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
			char orig_vert = 65 + i; //ascii value of capital A
			char dest_vert = 65 + j;
			long distance = path_lengths_matrix[i][j];

			if(distance != INFINITY){ 
				cout << orig_vert << " -> " << dest_vert << ", distance: " << distance << ", path: ";
				if (i != j) {
					//if the path is direct and doesn't use intermediate matrix
					if (intermediate_vertices_matrix[i][j] == INFINITY) {
						cout << orig_vert << " -> " << dest_vert << endl;
					} else {
						//print out path that was traversed using the intermediate matrix
						print_path(intermediate_vertices_matrix, i, j);
						cout << endl;
					}
				} else {
					cout << orig_vert << endl;
				}
			}else{	
				cout << orig_vert << " -> " << dest_vert << ", distance: infinity, path: none" << endl;
			}
		}
	}
	//No pointers to delete
}

