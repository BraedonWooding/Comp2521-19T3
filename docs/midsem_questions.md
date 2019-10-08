# Midsem Questions

Download the zip file [here](https://github.com/BraedonWooding/Comp2521-19T3/raw/master/practice/midsem.zip)

## Difference (difference.c)

!> Run `sh ./autotest_diff.sh` to test

Given 2 lists return a new list which is the difference of the two sets.

Difference is defined as being a list of all the nodes that aren't common. i.e. given `[1, 2, 3]` and `[2, 3, 9]` the difference is `[1, 9]`.

Some more cases:

- diff `[1, 2, 3]` and `[1, 1, 3, 2]` is `[]`
- diff `[1, 1, 1]` and `[2, 2, 2]` is `[1, 2]`

## Polynomial Fit (polyfit.c)

!> Run `sh ./autotest_poly.sh` to test

Does the list fit the given coefficient curve.

For example if we have list 1 -> 2 -> 3
It can be represented via a line with points (0, 1), (1, 2), (2, 3)

```
   /
  /
 /
```

And will fit the curve 1 + 1 * x which is the coefficient array [1, 1]

Some more examples:
The list 0 -> 1 -> 4 -> 9 -> 16 -> 25 is a list of points of
(0, 0), (1, 1), (2, 4), (3, 9), (4, 16), (5, 25) and will fit the curve x^2
which is the coefficient array [0, 0, 1].
