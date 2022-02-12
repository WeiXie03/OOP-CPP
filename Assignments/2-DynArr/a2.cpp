// a2.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Tom Xie
// St.# : 301466036
// Email: tom_xie@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

//
// These are the only permitted includes: don't include anything else.
//
#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class str_vec
{
private:
    int cap;
    int sz;
    // underlying-str-array pointer
    string* arr;

public:
    str_vec()
        : cap(10), sz(0)
    {
        arr = new string[cap];
    }

    str_vec(int num, string str)
        : cap(2*num + 1), sz(num)
    {
        if (num < 0) cmpt::error("str_vec constructor: size of vec cannot be negative");
        arr = new string[cap];
        for (int i=0; i < num; i++) {
            arr[i] = str;
        }
    }

    str_vec(const str_vec& other)
        : cap(other.cap), sz(other.sz)
    {
        arr = new string[cap];
        for (int i=0; i < sz; i++) {
            arr[i] = other.arr[i];
        }
    }

    ~str_vec() {
        delete[] arr;
        sz = 0;
        cap = 0;
    }

    int size() const {
        return sz;
    }
    int capacity() const {
        return cap;
    }
    double pct_used() const {
        return ( double(size()) / double(capacity()) );
    }

    string join(string sep) const {
        if (sz == 0)
            return "";

        string joined;
        joined += arr[0];
        for (int i=1; i < sz; i++)
        {
            joined += sep;
            joined += arr[i];
        }
        return joined;
    }

    string to_str() const {
        string arr_str;
        arr_str += "{";
        arr_str += join(", ");
        arr_str += "}";
        return arr_str;
    }

    void print() const {
        cout << to_str();
    }
    void println() const {
        cout << to_str() << '\n';
    }

    string get(int i) const {
        if (i < 0 || i > size()-1)
            cmpt::error("get(): inputted index out of bounds");
        return arr[i];
    }
    void set(int i, string s) {
        if (i < 0 || i > size()-1)
            cmpt::error("set(): inputted index out of bounds");
        arr[i] = s;
    }

    void expand() {
        // make a new underlying array of double cap, with same contents, and free old array
        string* new_arr = new string [2*capacity()];
        // copy over contents
        for (int i=0; i < size(); i++)
        {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }

    void append(string s) {
        if (size() == capacity()) {
            expand();
        }
        sz += 1;
        arr[size()-1] = s;
    }
    void append_new(string s) {
        // check if s in vec already
        for (int i=0; i < size(); i++)
        {
            if (arr[i] == s) {
                return;
            }
        }
        append(s);
    }

    string trim_str(const string& s) {
        // returns trimmed (of leading and trailing spaces) copy of s

        int real_start_i = 0;
        // record position of first non-space in real_start_it by looping through
        while (s[real_start_i] == ' ' && real_start_i < s.size())
        {
            real_start_i ++;
        }

        int real_end_i = s.size()-1;
        // looping backwards, record position of last non-space in string in real_end_it
        // only need to check until first non-space in string
        while (s[real_end_i] == ' ' && real_end_i > real_start_i)
        {
            real_end_i --;
        }

        // now copy trimmed portion
        string::const_iterator ch_it;
        // length = last - first + 1
        return s.substr(real_start_i, (real_end_i - real_start_i +1));
    }

    void trim_all() {
        for (int i=0; i < size(); i++)
        {
            arr[i] = trim_str(arr[i]);
        }
    }

    void remove(int i) {
        if (i < 0 || i > size()) {
            cmpt::error("remove(): index out of bounds");
        }

        sz -= 1;
        // move forward by 1
        for (int j = i; j < size(); j++)
        {
            arr[j] = arr[j+1];
        }
        // erase last spot
        arr[size()+1] = "";
    }

    void keep_all_starts_with(char c) {
        for (int i=0; i < size(); i++)
        {
            if (arr[i][0] != c) {
                remove(i);
            }
        }
    }

    void clear() {
        for (int i=0; i < size(); i++)
        {
            arr[i] = "";
        }
        sz = 0;
    }

    void squish() {
        for (int i=size(); i < capacity(); i++)
        {
            if (arr[i] != "") {
                return;
            }
        }
        cap = sz;
    }
};

bool operator== (const str_vec& v1, const str_vec& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    for (int i=0; i < v1.size(); i++)
    {
        if (v1.get(i) != v2.get(i)) {
            return false;
        }
    }
    return true;
}
bool operator!= (const str_vec& v1, const str_vec& v2) {
    if (v1.size() != v2.size()) {
        return true;
    }
    int min_size = (v1.size() < v2.size()) ? v1.size() : v2.size();
    for (int i=0; i < min_size; i++)
    {
        if (v1.get(i) != v2.get(i)) {
            return true;
        }
    }
    return false;
}

void test_str_vec_def() {
    str_vec test_vec;
    assert(test_vec.capacity() == 10);
    assert(test_vec.size() == 0);
}

void test_str_vec_n() {
    struct Testcase
    {
        int len;
        string elem;

        Testcase(int n, string s)
            : len(n), elem(s) {}
    };
    Testcase cases[] {
        Testcase(0, "aegr"),
        Testcase(3, ""),
        Testcase(2, "!.eav edg3"),
        //Testcase(-2, "`-9/''`"),
    };
    for (Testcase tcase : cases)
    // check constructor-created str-vecs have correct fields
    {
        str_vec ctor_vec(tcase.len, tcase.elem);
        assert(ctor_vec.size() == tcase.len);
        assert(ctor_vec.capacity() == 2*tcase.len + 1);
        if (tcase.len > 0) {
            // all elements should equal tcase.elem
            for (int i=0; i < ctor_vec.size(); i++)
                assert(ctor_vec.get(i) == tcase.elem);
        }
    }
}

void test_str_vec_cp() {
    str_vec t1(4, "ev");
    str_vec c1(t1);
    assert(c1.capacity() == 2*4+1);
    assert(c1.size() == 4);
    for (int i=0; i < t1.size(); i++) {
        assert(c1.get(i) == "ev");
    }

    t1.set(1, " qb3");
    t1.set(3, "3g r");
    str_vec c2(t1);
    assert(c2.capacity() == 2*4+1);
    assert(c2.size() == 4);
    assert(c2.get(0) == "ev");
    assert(c2.get(1) == " qb3");
    assert(c2.get(3) == "3g r");
}

void test_getsize() {
    str_vec t1(4, "ev");
    assert(t1.size() == 4);
    str_vec t2(5, "");
    assert(t2.size() == 5);
    str_vec t3(0, "ev");
    assert(t3.size() == 0);
    //test = str_vec(-1, "ev");
    // should result in cmpt::error
}
void test_getcap() {
    str_vec t1(4, "ev");
    assert(t1.capacity() == 2*4+1);
    str_vec t2(5, "");
    assert(t2.capacity() == 2*5+1);
    str_vec t3(0, "ev");
    assert(t3.capacity() == 2*0+1);
    // should result in cmpt::error
    //test = str_vec(-1, "ev");
}
void test_pct_used() {
    str_vec t1(4, "ev");
    assert(t1.pct_used() == 4.0/(2.0*4.0+1.0));
    str_vec t2(5, "");
    assert(t2.pct_used() == 5.0/(2.0*5.0+1.0));
    str_vec t3(0, "ev");
    assert(t3.pct_used() == 0.0/(2.0*0.0+1.0));
    // should result in cmpt::error
    //test = str_vec(-1, "ev");
}

void test_get() {
    str_vec t1(4, "ev\n gu 1``/.,\[");
    assert(t1.get(0) == "ev\n gu 1``/.,\[");
    assert(t1.get(3) == "ev\n gu 1``/.,\[");
    // should result in cmpt::error
    //assert(t1.get(4) == "ev\n gu 1``/.,\[");
    str_vec t2(0, "ev\n gu 1``/.,\[");
    // should result in cmpt::error
    //assert(t2.get(0) == "ev\n gu 1``/.,\[");
}
void test_set() {
    str_vec t1(4, "ev\n gu 1``/.,\[");
    assert(t1.get(0) == "ev\n gu 1``/.,\[");
    t1.set(0, "");
    assert(t1.get(0) == "");

    assert(t1.get(3) == "ev\n gu 1``/.,\[");
    t1.set(3, "ebteio");
    assert(t1.get(3) == "ebteio");

    // should result in cmpt::error
    //t1.set(4, " efg");
}

void test_join() {
    str_vec t1(4, "aeg");
    t1.set(1, "ev");
    t1.set(2, "0,.");
    t1.set(3, "aevfv");
    assert(t1.join(", ") == "aeg, ev, 0,., aevfv");

    str_vec t2;
    assert(t2.join("-") == "");

    str_vec t3(1, "hp\t h");
    assert(t3.join(";") == "hp\t h");
}

void test_tostr() {
    str_vec t1(4, "aeg");
    t1.set(1, "ev");
    t1.set(2, "0,.");
    t1.set(3, "aevfv");
    assert(t1.to_str() == "{aeg, ev, 0,., aevfv}");

    str_vec t2;
    assert(t2.to_str() == "{}");

    str_vec t3(1, "hp\t h");
    assert(t3.to_str() == "{hp\t h}");
}

void test_append() {
    str_vec t1(4, "ev\n gu 1``/.,\[");
    for (int i = t1.size()-1; i < t1.capacity()-1; i++) {
        t1.append("e f");
        assert(t1.get(i+1) == "e f");
    }
    assert(t1.capacity() == 2*4+1);
    t1.append("ae 3f3");
    assert( t1.get(t1.size()-1) == "ae 3f3");
    assert(t1.capacity() == 2*(2*4+1));
}

void test_append_new() {
    str_vec t1(4, "brt");
    for (int i = t1.size()-1; i < t1.capacity()-1; i++) {
        t1.append_new("e f");
        assert(t1.get(i+1) == "e f");
    }
    t1.append_new("brt");
    assert(t1.size() == t1.capacity());

    assert(t1.capacity() == 2*4+1);
    t1.append_new("ae 3f3");
    assert( t1.get(t1.size()-1) == "ae 3f3");
    assert(t1.capacity() == 2*(2*4+1));
}

void test_trim_all() {
    str_vec t1(4, "  ev gu 1``/., [f ");
    t1.append("\ta e f  ");
    t1.append(" fs  s j");
    assert(t1.size() == 6);

    t1.trim_all();

    for (int i = 0; i < 4; i++) {
        assert(t1.get(i) == "ev gu 1``/., [f");
    }
    assert(t1.get(4) == "\ta e f");
    assert(t1.get(5) == "fs  s j");
}

void test_remove() {
    str_vec t1(4, "aeg");
    assert(t1.size() == 4);
    t1.remove(2);
    assert(t1.size() == 3);
    assert(t1.get(2) == "aeg");
}

void test_keep_all_starts() {
    str_vec t1(4, "aeg");
    t1.set(1, "ev");
    t1.set(2, "0,.");
    t1.keep_all_starts_with('a');
    assert(t1.size() == 2);
    assert(t1.get(1) == "aeg");

    str_vec t2;
    t2.keep_all_starts_with('e');
    assert(t2.size() == 0);

    str_vec t3(4, "");
    t1.keep_all_starts_with('\0');
    assert(t1.size() == 0);
}

void test_clear() {
    str_vec t1(4, "aeg");
    t1.set(1, "ev");
    t1.set(2, "0,.");
    t1.clear();
    assert(t1.capacity() == 2*4+1);
    assert(t1.size() == 0);
    str_vec t2;
    t2.clear();
    assert(t2.capacity() == 10);
    assert(t2.size() == 0);
}
void test_squish() {
    str_vec t1(4, "aeg");
    t1.set(2, "");
    t1.set(3, "");
    t1.squish();
    assert(t1.capacity() == 4);
    assert(t1.size() == 4);

    str_vec t2;
    t2.squish();
    assert(t2.size() == 0);
    assert(t2.capacity() == 0);
}

void test_comps() {
    // ==
    str_vec t1(4, "aeg");
    str_vec t2(t1);
    assert(t1 == t2);
    str_vec t3(3, " 3 ");
    assert(((t1 == t3) == false));
    str_vec t4(4, " 3 ");
    assert(((t1 == t4) == false));
    str_vec t5;
    assert(((t1 == t5) == false));

    // !=
    assert((t1 != t2) == false);
    assert(t1 != t3);
    assert(t1 != t4);
    assert(t1 != t5);
}

int main() {
    cout << "Assignment 2 ... \n";
    test_str_vec_def();
    test_str_vec_n();
    test_str_vec_cp();
    // "delegate" destructor testing to valgrind

    test_getsize();
    test_getcap();
    test_pct_used();

    test_get();
    test_set();

    test_join();
    test_tostr();

    test_trim_all();
    test_remove();
    test_clear();
    test_squish();

    test_comps();
}
