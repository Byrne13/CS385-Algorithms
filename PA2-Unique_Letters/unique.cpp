/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Jack Byrne
 * Date        : 9/25/2021
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    int length = s.length();
    for (int i = 0; i < length; i++){
        if(isupper(s[i])){
            return false;
            }
        }
    return true;

}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.


    unsigned int vector= 0;
    unsigned int setter;

    int length = s.length();
    for (int i = 1; i < length+1; i++){
        
        setter = 1 << (s[length-i] - 'a');
        if ((vector & setter)==0){
            vector = vector | setter;
        }
        else{
            return false;
        }

    }
    return true;
}

int main(int argc, char * const argv[]) {
    
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

  

    if (argv[1] == 0 ){
        cout << "Usage: ./unique <string>" << endl;
        return 0;
    }
    string str = argv[1];
    
    if (argv[2] != 0 ){
        cout << "Usage: ./unique <string>" << endl;
        return 0;
    }
 

    if(is_all_lowercase(str) != true){
        cout << "Error: String must contain only lowercase letters." <<endl;
        return 0;
    }

    int length = str.length();


    for (int i = 0; i < length; i++){
        if(isdigit(str[i])){
            cout << "Error: String must contain only lowercase letters." <<endl;
            return 0;
        }
    }

    if(all_unique_letters(str) != true){
        cout << "Duplicate letters found." <<endl;
        return 0;
    }
    else{
        cout << "All letters are unique." <<endl;
    }


    return 1;
}
