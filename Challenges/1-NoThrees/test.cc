#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "challenge_1.h"

using namespace std;

void _test_3check() {
    // contains_three()
    for (int i = -25; i < 25; i++)
    {
        cout << to_string(i) <<' '<< contains_three( to_string(i) ) <<'\n';
    }
}

vector<int> _test_readlines(string fname) {
    vector<int> lines;
    lines = read_no3_lines(fname);

    cout << lines;

    return lines;
}

int main(int argc, char* argv[]) {
    //_test_3check();
    
    /* << overload for vector<int>'s test
    vector<int> test_vec {-5, 3, 4, 9, 0};
    cout << test_vec;
    */

    vector<int> lines = _test_readlines(argv[1]);
    cout << endl;

    // test sum vec
    cout << "no 3 sum = "<< sum_vec(lines) << endl;

    return 0;
}
