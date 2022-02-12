# Same or Different

Call a non-empty string **different** if no two of its characters are equal,
and **repeated** if all its characters are equal. Strings of length 1 are both
different and repeated. A string is **ordinary** if it is neither different
nor repeated. The empty string is ordinary.

For example, `house` is different, `oooo` is repeated, and `U` is both
different and repeated. `eeeE` and `todo` are both ordinary.

How many strings in [strings2.txt](strings2.txt) are different? How many are
repeated?

For example:

```
rename
eeE
house
U
todo
oooo
```

`house` and `U` are different, and `oooo` and `U` are repeated. So there are 2
different strings and 2 repeated strings.

Notice that case matters, e.g. `'a'` and `'A'` are *not* equal.

## Ideas (not for marks!)

- How easy would be to modify your program so that uppercase and lowercase
  versions of a letter were considered equal?

## Files

[strings2.txt](numbers1.txt) contains one integer per line.

Write your answer in [challenge_2.cpp](challenge_1.cpp).


## Reminder

The purpose of these challenges is to practice solving problems with C++.
Please try to do them on your own, and don't just search for solutions online
or ask others for the answers.
