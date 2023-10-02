/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jack Byrne
 * Date        : 10/2/2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    //     // TODO: Return a vector of vectors of ints representing
//     // the different combinations of ways to climb num_stairs
//     // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways;
    vector<vector<int>> result;
    vector<int> blank;

    
    if (num_stairs <= 0){ //base case
        ways.push_back(blank);
    }
    else{
        if (num_stairs >= 1){ //for each condition, prepends to each result
            result = get_ways(num_stairs - 1);
            for (long unsigned int j=0; j < result.size(); j++){
                result[j].insert(result[j].begin(), 1);
            }
            ways.insert(ways.end(), result.begin(), result.end());
        }
        if (num_stairs >= 2){
            result = get_ways(num_stairs - 2);
            for (long unsigned int j=0; j < result.size(); j++){
                result[j].insert(result[j].begin(), 2);
            }
            ways.insert(ways.end(), result.begin(), result.end());
        }
        if (num_stairs >= 3){
            result = get_ways(num_stairs - 3);
            for (long unsigned int j=0; j < result.size(); j++){
                result[j].insert(result[j].begin(), 3);
            }
            ways.insert(ways.end(), result.begin(), result.end());
        }

    }

    return ways;
 }

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    long unsigned int size = ways.size();

    //makes the header
    if(size == 1){
        cout << "1 way to climb 1 stair." <<endl;
    }else{
        cout << size << " ways to climb " << ways[0].size() << " stairs." <<endl;
    }
    //checks if special formatting is needed
    bool resize = false;
    if(size > 9){
        resize = true;
    }
    //iterates through and prints a list of combinations
	for (long unsigned int i = 0; i < size; i++)
	{
		if(i < 9 && resize){ 
            cout <<" " << i+1 << ". " << "["; 
            }
        else{
            cout << i+1 << ". " << "["; 
        }
		for (long unsigned int j = 0; j < ways[i].size(); j++)
		{

			if (j == ways[i].size()- 1){
				cout << ways[i][j];
            }
			else{
				cout << ways[i][j] << ", ";
            }

		}
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
    if(argc !=2){
        cerr << "Usage: ./stairclimber <number of stairs>" <<endl;
        return 1;
    }

    int x = atoi(argv[1]);

    if(isdigit(x) != true && x <= 0 ){
        cerr << "Error: Number of stairs must be a positive integer." <<endl;
        return 0;
    }
    


    display_ways(get_ways(x));
    return 0;



}
