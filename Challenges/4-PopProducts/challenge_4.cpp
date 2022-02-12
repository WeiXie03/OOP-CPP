// challenge_4.cpp

//
// You may use only the following #includes in your code:
//
#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//
// You don't need to use them all, but you can't use any others. Don't change
// these in any way.

using namespace std;

struct Product
{
    string name;
    int pop;
    // will count when reading file, when add for first time start at 1
    Product (string id)
        : name(id), pop(1) {}
};

vector<Product> count_prod_freq_file(string fname) {
    vector<Product> counts;
    ifstream inF (fname);
    string read_buf;

    vector<Product>::iterator prod_elem_it;
    while (inF >> read_buf)
    {
        // look up read name in "database" (counts)
        auto record_match = [read_buf](const Product& prod) {
            return (prod.name == read_buf);
        };
        prod_elem_it = find_if(begin(counts), end(counts), record_match);
        // if not yet in database, make new entry
        if (prod_elem_it == end(counts)) {
            // ctor starts count at 1
            counts.push_back( Product(read_buf) );
        }
        else {
            ++ prod_elem_it->pop;
        }
    }
    return counts;
}

int main(int argc, char* argv[]) {
	cout << "Challenge 4 ...\n";

    if (argc < 2)
        cout << "Please enter your input file on command line after program name\n";
    
    vector<Product> counts = count_prod_freq_file(argv[1]);
    /*
    for (Product entry : counts) {
        cout << entry.name <<' '<< entry.pop << '\n';
    }
    */

    return 0;
}
