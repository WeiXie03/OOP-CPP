// challenge_3.cpp

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

const std::string vowels = "aeiou";

using namespace std;

bool all_vowels_once(const string& str, const string& vowels) {
    // check that each vowel uniquely occurs
    for (char vow : vowels)
    {
        if (str.find(vow) == string::npos)
            return false;
        else if (str.find(vow) != str.rfind(vow))
            return false;
    }
    return true;
}

int count_fullvowel_words_file(const string& fname, const string& vowels) {
    int count = 0;
    ifstream inF (fname);

    string word;
    while (inF >> word)
    {
        if ( all_vowels_once(word, vowels) )
            ++ count;
    }
    inF.close();

    return count;
}

int main(int argc, char* argv[]) {
	cout << "Challenge 3 ...\n";

    if (argc < 2) {
        cout << "the name of the file to be processed is to be entered on the command line following the program name\n";
    }

    cout << argv[1] << " contains " << count_fullvowel_words_file(argv[1], vowels) << " words with all the vowels each exactly once." << endl;

    return 0;
}
