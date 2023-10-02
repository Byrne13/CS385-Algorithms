/*******************************************************************************
 * Name    : Jack Byrne
 * Author  : Brian S. Borowski
 * Version : 1.0
 * Date    : September 15, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : 
    is_prime_{new bool[limit + 1]}, limit_{limit} { 
            sieve();
      }    

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.


    

    cout << "Number of primes found: " << num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    
    int count = 0;
    if (num_primes_ < primes_per_row){
        if (num_primes_ == 1){
            cout << "2";
        }
        else{
            for(int i =2 ; i < limit_ + 1; i++){
                if (!is_prime_[i]){
                        cout << i;
                if (i!= max_prime_){
                    
                    cout << " ";
                }
                }
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;
                cout << endl;
        cout << endl;
        cout << endl;
    }
    else{
        for(int i = 2; i < limit_ + 1; i++){
            if (count == primes_per_row){
                count = 0;
                cout << endl;
            }
            if (!is_prime_[i]){
                if (count!=0){
                    cout << " ";
                }
                

                if (num_primes() > primes_per_row){
                    cout << setw(max_prime_width) << i;
                }
                else {
                    cout << i;
                }
                count++;
            }
        }
        cout << endl;
    }

}

int PrimesSieve::count_num_primes() const {
    int count = 0;
    for (int i = 2; i < limit_ + 1; i++){
        if (!is_prime_[i]){
            count++;
        }
    }


    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for (int i = 2; i <= sqrt(limit_) ; i++){
        if(!is_prime_[i]){
            for(int j = pow(i, 2); j <= limit_ ; j = j + i){
                is_prime_[j] = true;
            }
        }
    }
    for (int i = limit_; i> 2; i--){
        if (!is_prime_[i]){
            max_prime_ = i;
            break;
        }

    }
    num_primes_ = count_num_primes();

    
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    
    int x = 1;
    int myNum = num;
    while (myNum-10 >= 0){
        x++;
        myNum = myNum / 10;
    }
    return x;
}

int main() {


    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;


    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    cout << endl;
    
    PrimesSieve MySieve(limit);


    MySieve.display_primes();


    return 0;
}
