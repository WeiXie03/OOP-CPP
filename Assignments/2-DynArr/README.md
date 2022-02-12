# Assignment 2: An Object-oriented Dynamic String Array

Your task is to use *object-oriented programming* to implement a vector-like
class called `str_vec`. One if it's major features is that it completely (and
correctly!) manages its own memory.


## Getting Started

Put all your code for this assignment into [a2.cpp](a2.cpp). Implement all the
requested methods and functions using the exact name and parameters. You can
add other helper functions/methods if you need them.

Write a test function for *each* major method/function to ensure it is
correct. Use either if-statements or assertions the testing. Each test
function should have approximately 3 - 5 tests.


## Questions

Implement each of the following methods and functions. Use `const`, `public`,
and `private` whenever possible.

1. Implement a **default constructor** for `str_vec()` that creates a new
   `str_vec` of size 0 and capacity 10. 

   Example:

   ```cpp
   str_vec arr;
   // arr is an empty str_vec of size 0 and capacity 10
   ```

   The capacity of `str_vec` is the size of its underlying array. The size is
   the number of items in the `str_vec` from the point of view of the user.

2. Implement a **constructor** `str_vec(n, s)` that creates a new `str_vec` of
   size `n` where each element contains a copy of the string `s`. The capacity
   should be at least `n`. If `n` is less than 0, use `cmpt::error` to throw a
   helpful error message.

   Example:

   ```cpp
   str_vec arr(5, "cat");
   // arr is str_vec of size 5, each entry containing the string "cat"
   ```

3. Implement a **copy constructor** `str_vec(other)` that creates a new
   `str_vec` that is a copy of the `str_vec` named `other`. 

   Example:

   ```cpp
   str_vec a(5, "<empty>");
   str_vec b(a);
   // b is a str_vec of size 5 with each entry equal to the string "<empty>"
   ```

   The *capacity* of `b` should be at least the *size* of `a`.

   Both `a` and `b` should have their own underlying array.

4. Implement a **destructor** `~str_vec()` that deletes the dynamic memory
   used by the `str_vec`.

   Be sure to test your program with `valgrind`!

5. Implement these **getters**:

   - `size()`: returns the number of strings in the `str_vec`.

   - `capacity()`: returns the capacity of the `str_vec`, i.e. the size of the
     underlying array.

   - `pct_used()`: returns the percentage (from 0.0 to 1.0) of the underlying
     array that is in use, i.e. the size divided by the capacity.

   Make sure that these are all `const` methods!

   Example:

   ```cpp
   str_vec empty;

   cout << empty.size()     << ' '    // 0
        << empty.capacity() << ' '    // 10
        << empty.pct_used() << '\n';  // 0
   ```

6. Implement a non-mutating method called `join(sep)` that combines all the
   strings in `str_vec` into a single long string, with every string, except
   the first one, beginning with `sep`.

   For example, if the `str_vec` `a` is `{"up", "down", "hello", "goodbye"}`,
   then:

   - `a.join(", ")` returns the string `up, down, hello, goodbye`

   - `a.join("-")` returns the string `up-down-hello-goodbye`
   
   - `a.join("")` returns the string `updownhellogoodbye`
   
   If `a` is empty, then `a.join(sep)` returns the empty string.

   If `a` only has one string, then `a.join(sep)` returns just that string.

7. Implement these non-mutating methods:

   - `to_str()`: returns a `string` representation of the `str_vec`; please
     use the `{}`-brackets style as shown in the example below.

   - `print()`: a `void` method that prints the string representation of the
     `str_vec` to `cout`

   - `println()`: is a `void` method that does the same thing as `print()`,
     but also prints a `\n` at the end

   Make sure these are all `const`!

   Example:

   ```cpp
   str_vec arr(3, "cat");

   string s = arr.to_str(); // s is the string {"cat", "cat", "cat"}

   arr.print();    // prints {"cat", "cat", "cat"} on cout (no \n at end)
   arr.println();  // prints {"cat", "cat", "cat"} on cout (\n at end)
   ```

8. Implement these methods:

   - `get(i)` is a **getter** that returns the `string` at index location `i`
     of the `str_vec`. Just as with arrays, the first index location is 0.
     Make sure this is `const`!

   - `set(i, s)` is a **setter** that sets index location `i` to be a copy of
     string `s`.

   Both methods should do *bounds checking*: use `cmpt::error` to throw a
   helpful error message if the passed-in index `i` is less than 0, or greater
   than `size() - 1`.

   Example:

   ```cpp
   str_vec arr(3, "cat");

   arr.set(1, "dog");       // arr is now {"cat", "dog", "cat"}

   string s1 = arr.get(1);  // s1 is "dog"
   string s2 = arr.get(2);  // s2 is "cat"
   ```

9. Implement these mutating methods:

   - `append(s)` is a `void` method that adds the string `s` to the right end
     (the back) of the `str_vec`, increasing the size by 1

   - `append_new(s)` is the same as `append(s)`, but `s` is only appended if
     it's *not* already in the `str_vec`; if `s` is already there,
     `append_new(s)` does nothing

   For both methods, the underlying capacity should only be increased if
   necessary. When the capacity is increased, it should be *doubled*.

   Example:

   ```cpp
   str_vec arr; // empty, size 0

   arr.append("apple");      // {"apple"}
   arr.append("orange");     // {"apple", "orange"}
   arr.append_new("apple");  // {"apple", "orange"}
   arr.append_new("pear");   // {"apple", "orange", "pear"}
   arr.append_new("orange"); // {"apple", "orange", "pear"}
   ```

10. Implement the `void` mutating method `trim_all()` that removes any leading
    and trailing spaces from all the elements of the `str_vec`.

    For example, if the `str_vec` `a` is `{"hat", " dog", "house ", " wall
    "}`, then after calling `a.trim_all()` it will be `{"hat", "dog", "house",
    "wall"}`.

11. Implement the `void` mutating method `remove(int i)` that removes the
    string at index location `i`. All the strings to the right are moved down
    one position to fill in the gap, and the size of the `str_vec` is
    decreased by 1.

    For example, suppose `str_vec` `a` is `{"apple", "orange", "pear"}`. Then
    after calling `a.remove(1)`, it will be `{"apple", "pear"}`.

    `remove` should do bounds-checking on `i`. If `i` is less than 0, or
    greater than or equal to `size()`, then it should call `cmpt::error` with
    a helpful error message.

12. Implement the `void` mutating method `keep_all_starts_with(char c)` that
    removes all strings that *don't* start with `c`.

    For example, if the `str_vec` `a` is `{"hat", "book", "horse", "house",
    "Hot!"}`, then after calling `a.keep_all_starts_with('h')` it will be
    `{"hat", "horse", "house"}`.

    The order of the strings in the `str_vec` after calling
    `keep_all_starts_with` should be the same as before calling it.

    If none of the strings start with `c`, or the `str_vec` is empty, then
    `keep_all_starts_with` does nothing.

13. Implement these mutating methods:

    - `clear()` is a `void` method that removes all elements from the
      `str_vec` so its size is 0. Make this method as efficient as possible.
      The capacity can stay the same.

    - `squish()` is a `void` method that will, if necessary, re-size the
      underlying array so that the size and capacity are the same. The
      elements in the array are the same (and in the same order) after
      squishing as before.

    Example:

    ```cpp
    str_vec arr;      // {}, size 0, capacity 10
    arr.append("a");  // {"a"}, size 1, capacity 10
    arr.append("b");  // {"a", "b"}, size 2, capacity 10
       
    arr.squish();     // {"a", "b"}, size 2, capacity 2

    arr.clear();      // {}, size 0, capacity 2
    ```

14. Implement these functions (*not* methods!):

    - `operator==(a, b)` is a `bool` function that returns `true` if the
      `str_vec` `a` and the `str_vec` `b` have the same elements in the same
      order, and `false` otherwise

    - `operator!=(a, b)` is a `bool` function that returns `true` if the
      `str_vec` `a` and the `str_vec` `b` *don't* have the same elements in
      the same order, and `false` otherwise

   Example:

   ```cpp
   str_vec a(3, "cat"); 
   str_vec b(3, "cat");

   if (a == b) cout << "same\n";       // prints "same"
   if (a != b) cout << "different\n";  // prints nothing

   a.set(0, "feline");

   if (a == b) cout << "same\n";       // prints nothing
   if (a != b) cout << "different\n";  // prints "different"
   ```

## Submit Your Work

Please put all your code into [a2.cpp](a2.cpp), and submit it on Canvas.
Implement **all** the methods and functions exactly as described, otherwise
the marking software will probably give you 0!

The only file you submit is [a2.cpp](a2.cpp): *don't* submit any other files.
The marker will use the standard [makefile](makefile) to compile it, and a
copy of [cmpt_error.h](cmpt_error.h) will be in the same folder as
[a2.cpp](a2.cpp) when it's tested.


## Basic Requirements

Before we give your program any marks, it must meet the following basic
requirements:

- It must compile on Ubuntu Linux using the standard course
  [makefile](makefile):
  
  ```
  $ make a2
  g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a2.cpp   -o a2
  ```
  
  If your program fails to compile, your mark for this assignment will be 0.

  A copy of [cmpt_error.h](cmpt_error.h) will be in the same folder as
  [a2.cpp](a2.cpp) when it's compiled, so your program can use `cmpt::error`
  if necessary.

- It must have no memory leaks or memory errors, according to `valgrind`,
  e.g.:

  ```
  $ valgrind ./a2
    
  // ... lots of output ... 
  ```

  A program is considered to have no memory error if:

  - In the `LEAK SUMMARY`, `definitely lost`, `indirectly lost`, and `possibly
    lost` must all be 0.

  - The `ERROR SUMMARY` reports 0 errors.

  - It is usually okay if **still reachable** reports a non- zero number of
    bytes.

- **You must include the large comment section with student info and the
  statement of originality**. If your submitted file does not have this, then
  we will assume your work is not original and it will not be marked.
  
If your program meets all these basic requirements, then it will graded using
the marking scheme on Canvas.


## Marking Scheme

### Source Code Readability (6 marks)

- All names of variables, functions, structs, classes, etc. are sensible,
  self-descriptive, and consistent.

- Indentation and spacing is perfectly consistent and matches the structure of
  the program. All blank lines, indents, and extra spaces have a reason.

- All lines are 100 characters in length, or less.

- Comments are used when appropriate: to describe code that is tricky or very
  important. There are no unnecessary comments, and no commented-out code.

- Appropriate features of C++ are used in an appropriate way. For example, do
  **not** use a feature of C (like C-style strings) when there is a better
  feature of C++ (e.g. the standard `string` class). Don't use any features
  you don't understand.

- Overall, the source code is easy to read and understand.

### Questions

- **1 mark** for correctly and efficiently implementing the functions/methods
  for each question.

- **1 mark** for a testing function for each question that automatically tests
  each of the functions/methods in that question. The testing should either
  use if-statements or assertions.
