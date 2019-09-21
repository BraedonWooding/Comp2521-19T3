# Wk02

## Big O

What is the complexity of the following

```c
int foo(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d + %d = %d\n", i, j, i + j);
        }
    }
}
```

```c
// Returns the index of the wanted element
// -1 if no such index exists
// Presumes array is sorted
int bar(int array[], int len, int wanted) {
    int hi = len - 1;
    int lo = 0;
    while (low <= hi) {
        int med = (hi + lo) / 2;
        if (array[med] == wanted) {
            return med;
        } else if (array[med] < wanted){
            lo = med + 1;
        } else {
            hi = med - 1;
        }
    }
    return -1;
}
```

> Think about how many elements you will 'touch'

## Another recap of recursive functions

Let's rewrite the 'bar' function from before as recursive!

## DLLs

No that isn't Dynamic Linked Libraries it is doubly linked lists!!

> A prev pointer or a next pointer?  Why not both :O

None of the tute questions require this but the lab does so I want to go through this just shortly.  I'll do it on the 'board' / 'playing around with C'.

Let me know in the lab if you need help around this I'm happy to give a longer explanation to a group in the lab.

## Tips for 'guessing' complexity

If you want a reasonable way of guessing complexity here is some tips:

- Does the direction change?
  - This is where it get's tricky but is typically not too useful by itself look for other properties
- If the direction is constant do you backtrack (i.e. go back 'x' positions to then go forward)
  - Then you probably have something like O(n^k) for k > 1
- Do you consistently skip elements
  - i.e. in the above code example we skipped half the array each time we 'recursed'/looped
  - Skipping a constant number of elements that isn't dependent on 'n' probably won't impact your big O
- Only consider worst performance (for Big O) later on you'll deal with average and best performance
  
Do you have any more tips?  If so then let me know and I'll add them here :)

## Back to complexity analysis

### Palindromes

Let's look at writing it both recursively and iteratively just to get some more practice.

1) Psuedocode
2) Time complexity
3) In C

### Computing Polynomials

Let's state that we are given a polynomial inside an array of size `n` i.e. `P(x) = a_0 x^0 + a_1 x^1 + a_2 x^2 + ... a_n x^n` where all coefficients are stored inside `A[0..n] = [a_0, a_1, ..., a_n]` and we are given the argument `x`

i.e. `double compute_p(double A[], int n, double x);`

Let's design an O(n) function to do above.

#### Interesting Sidepoint that you will cover if you do 3181/3821

What if doing the multiplications were very very expensive how could we reduce it?

### Adding 2 sparse vectors (I'll probably skip this due to time because the challenges are interesting)

Sometimes we end up with vectors that have a lot of 0's i.e. (2.3, 0, 0, 0, -5.61, 0, 0, 1.8) and if we want to store this efficiently we can instead store it as a series of pairs that tell you what index has which value (and we don't store '0's they are just presumed)

i.e. the above vector would be `[(0, 2.3), (4, -5.61), (7, 1.8)]`

Let's try to build an algorithm to add 2 sparse vectors together presuming they have the same dimension.

> Label the first vector size as `n` and the second vector size as `m` this isn't the dimension of the vector but rather the number of sparse pairs there are.

Consider the cases of worst performance!  Clearly if they both have no pairs it is `O(1)` but that isn't reasonable so we want to consider the WORST performance.  Also the pairs are given in order of index (if they weren't can we still solve this in O(n)?)

## Challenge Exercise!!

Let's say I give you 2 stacks the first of size `n` and second of size `m` and I wanted you to tell me the maximal number of elements you can pop off from A or B such that it is `sum(elements popped) <= k` where `k >= 0`.  (Note limiting `k` to be positive just makes it simpler to think about in reality it is arbitrary and is relatively easy to remove that limitation).  Both stacks contain only positive elements (again easier to think about but not really needed).

i.e. for the stacks

```
| 4 |   |
| 2 | 2 |
| 4 | 1 |
| 6 | 8 |
| 1 | 5 |
```

If we had `k = 10` the maximum number of elements would be `4` i.e. `[4, 2, 2, 1]`.

A few restrictions

- You are allowed to use one more stack `C` but no other collections
- You can push/pop but nothing else

Consider the following hints

- Based purely on theoretical information transfer how many elements do we HAVE to visit to know the optimal solution
- This theoretical limit should be what we aim for we may not hit it though!

How easy is it to write it in C?
