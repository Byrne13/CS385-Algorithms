/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      :
 * Version     : 1.0
 * Date        :
 * Description : Counts the number of inversions in an array.
 * Pledge      :
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    int inversions = 0;
    for(int i = 0; i < length; i++){
        for(int j = i; j < length; j++){
            
            //cout<< array[i] << ":" << array[j] <<endl;
            if(array[i] > array[j]){
                //cout<< array[i] << ">" << array[j] <<endl;
                inversions++;
            }
        }
    }
    return inversions;

}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    //makes scratch and calls mergesort
    int *scratch = new int[length];
    long inversions = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long inversions = 0;
    //basecase
    if(high==low){
        return 0;
    }else if (high > low){
        int mid = (low + high)/2;
        int h = mid+1;
        int l = low;
        //recursevily calls two mergesorts and counts # of inversions
        inversions = inversions + mergesort(array, scratch, low, mid) + mergesort(array, scratch, mid + 1, high);
        //looping through target section of array
        for (int i = low; i <=high; i++){
            if ((h > high or array[l] <= array[h]) and l <= mid){
                    scratch[i] = array[l];
                    l++;
            }else{
                scratch[i] = array[h];
                inversions += (mid- l +1);
                h++;
            }
        }
        //put scratch in array
        for(int j = low; j <= high; j++){
            array[j] = scratch[j];
        }

    }
    return inversions;
}

int main(int argc, char *argv[]) {


    
    bool isSlow = false;
    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }else if(argc == 2){
        if(string(argv[1])=="slow"){
            isSlow = true;
        }
        else{
            cerr << "Error: Unrecognized option '"<< argv[1] << "'." << endl;
            return 1;
        }
    }
    else{
        isSlow = false;
    }

    // TODO: parse command-line argument

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }


    // TODO: produce output

    //copy into array
    int x = values.size();
    if(values.size() == 0){
        cerr << "Error: Sequence of integers not received." <<endl;
        return 1;
    }
    //cout << x<<endl;
    int *arr = new int [x];
    copy(values.begin(), values.end(), arr);
    if(isSlow)
        cout <<"Number of inversions: " <<count_inversions_slow(arr, x) << endl;
    else
        cout <<"Number of inversions: " <<count_inversions_fast(arr, x) << endl;

    
    delete[] arr;
    return 0;
}
