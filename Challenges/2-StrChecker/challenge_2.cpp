// challenge_2.cpp

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

// keep track of types of sets of strings (different, repeated, regular)
struct StrtypesCount
{
    int reps = 0;
    int diffs = 0;
    int regs = 0;
};

bool is_rep(const string& s) {
    // if repeated, should equal first character repeated <length of str> times
    string uniform = string( s.size(), s.at(0) );
    //cout << s << " should == " << '\"'<< uniform <<'\"' << endl;
    return (s == uniform);
}

bool chars_unique(const string& s) {
    // returns whether the chars of a given string are unique within it

    // for each char, check if any other chars same
    string::const_iterator it = s.cbegin();
    for ( ; it < s.cend()-1; ++it)
    {
        // since starting from first, don't need to keep checking from start
        // each time only need to check rest of string
        size_t next_pos = (it - s.cbegin()) + 1;
        // if ANY not unique, whole string not "unique"/diff
        if (s.find(*it, next_pos) != string::npos)
        {
            return false;
        }
    }
    return true;
}

void rec_strType(StrtypesCount& countstruct, const string& s) {
    // first check if just a single char
    if (s.size() == 1) {
        countstruct.reps += 1;
        countstruct.diffs += 1;
    }
    else
    {
        // init assume repeated, => not diff, not reg
        if (is_rep(s)) {
            countstruct.reps += 1;
        }
        // if not repeated, must be diff OR reg
        else
        {
            if (chars_unique(s))
                countstruct.diffs += 1;
            else
                countstruct.regs += 1;
        }
    }
}

int main(int argc, char* argv[]) {
	cout << "Challenge 2 ...\n";

    if (argc < 2)
        cout << "Please enter your input file on command line after program name\n";

    ifstream inF(argv[1]);

    StrtypesCount counter;
    string in_str;
    while (inF >> in_str)
    {
        rec_strType(counter, in_str);
    }

    cout << "repeated: "<< counter.reps << ", ";
    cout << "different: "<< counter.diffs << ", ";
    cout << "regular: "<< counter.regs << endl;

    return 0;
}
