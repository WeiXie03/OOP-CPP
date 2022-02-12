// challenge_1.cpp

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

bool contains_three(string s) {
    for (char c : s)
    {
        // stop as soon as '3' found
        if (c == '3')
            return true;
    }
    return false;
}

ostream& operator<< (ostream& out, const vector<int>& vec) {
    // just vector's elements separated by spaces
    for (int i : vec)
        out << ' ' << i;
    return out;
}

vector<int> read_no3_lines(string fname) {
    // reads a given text file and returns the lines that are numbers without any '3's, in a vector
    vector<int> no3_lines;

    ifstream inF (fname);
    // buffer to store each line
    string line;
    while (getline(inF, line))
    {
        //TODO: add try{ ... = stoi(line) }, catch ... ignore line if not an int

        if (! (contains_three(line))) {
            // first convert to a num, then store
            no3_lines.push_back( stoi(line) );
        }
    }
    inF.close();

    return no3_lines;
}

int sum_vec(const vector<int>& nums_list) {
    // returns the sum of a given list of numbers
    int sum = 0;
    for (int i : nums_list)
    {
        sum += i;
    }
    return sum;
}

int main() {
    cout << "========== No 3 Sum ===========" << endl;

    string inFname;
    cout << "Want to sum some integers except those with the digit '3'? Throw them in a text file one on a line each. Then run this program with just the text file name as an argument!\n";
    cin >> inFname;
    cout << "Proceeding with input file " << inFname << endl;

    vector<int> no3lines = read_no3_lines(inFname);
    cout << "Sum of int's without '3's = " << sum_vec(no3lines) << endl;
    
    return 0;
}
