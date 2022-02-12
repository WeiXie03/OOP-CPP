#include <iostream>

using namespace std;

int* f(int a) {
    a = 5;
    int* p = &a;
    return p;
}

/*
void del_arr() {
    int* arr = new int [4];
    for (int i=0; i < 4; i++)
    {
        // arr[i] is an int!
        delete arr[i];
    }
    delete[] arr;
}
*/

int main() {
    /*
    int *p = f(3);
    cout << *p;
    */

    int a = 3;
    cout << a + 5.4 << '\n';
}
