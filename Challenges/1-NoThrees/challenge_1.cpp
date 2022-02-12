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
#include "challenge_1.h"
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
        //TODO: add try{ ... = stoi(line) }, catch ...

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
