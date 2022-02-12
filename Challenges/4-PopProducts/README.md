# The Most Popular Product

Suppose you go to the supermarket and buy these items:

	milk apple orange orange butter

We'll call this a **basket** of five items.

The supermarket saves the names of all items in a database so that so it can
analyze purchasing patterns.

In this challenge you are given a file of baskets, one basket per line. Write
a program that finds **the top 3 most frequently occurring items**, both their
names and counts. In the case of a tie, choose the item that occurs first
alphabetically.

Every basket in the file has at least one (and maybe many more) items in it,
and items are separated by a space. The same item might appear more than once
in a basket.

All item names are strings of 1, or more, letters or digits, including the `_`
character. For example, `chocolate_milk`, `Eggos`, and `4socks_blue` are all
valid product names. Case matters, and so `Eggos` and `eggos` are considered
*different*.

For example, here is a file containing 5 baskets:

	paper pen paper carrots
	chocolate_milk
	cauliflower milk white_cheese cheese_strings pen
	orange apple raisins paper pen condensed_milk
	red_grapes paper paper paper chocolate_milk

The top 3 most frequently occurring items are:

	6  paper
	3  pen
	2  chocolate_milk

What are the top 3 most frequently occurring items, and their counts, for the
baskets in [baskets.txt](baskets.txt)?

Remember, if two or more items have the same count, then the item whose name
comes first alphabetically is chosen.


## Files

[baskets.txt](baskets.txt).

Write your answer in [challenge_4.cpp](challenge_4.cpp).


## Ideas (not for marks!)

- Could you modify your program to find the most frequent *pair* of items in
  the baskets?

- How efficient is your program? Would it work well for *millions* of baskets?


## Reminder

The purpose of these challenges is to practice solving problems with C++.
Please try to do them on your own, and don't just search for solutions online
or ask others for the answers.
