# Week 08

Assignment Talk. [here](https://docs.google.com/presentation/d/1GZtNTn7PvM2qzi_FAiQ_a5BJDJEUqmT_PGE32xXpMUw/edit?usp=sharing)

## Hashtables

### Best and Worst case insertion and search

#### What is the best case?

Think about optimising it so collisions are minimized!

#### What is the worst case?

You may want to use the sum of arithmetic series i.e. `(a_1 + a_n) * n/2` i.e. 0 + 1 + 2 = (0 + n) * n /2 = n^2 / 2.

### Example

Let's say we have the hash;

```c
uint64_t hash(int x) {
  // NOTE: Most platforms have int to be 4 bytes but C just specifies
  //       that it is atleast 4 bytes not exactly 4.  So we have to be careful
  //       about casting in the case it is > 8 bytes and our caller is relying on that
  // C11 provides static assert for cases like this.  This will provide error at compile time.
  _Static_assert(sizeof(x) <= 8, "Int must be <= 8 bytes to satisfy cast");
  return (uint64_t)x % 11;
}
```

Insert the following `11  16  27  35  22  20  15  24  29  19  13`.

Note: for the second hash function use `hash2(x) = (x % 3) + 1`

Table:

| Key      | 11 | 16 | 27 | 35 | 22 | 20 | 15 | 24 | 29 | 19 | 13 |
|----------|----|----|----|----|----|----|----|----|----|----|----|
| hash(x)  |  0 |  5 |  5 |  2 |  0 |  9 |  4 |  2 |  7 |  8 |  2 |
| hash2(x) |  3 |  2 |  1 |  3 |  2 |  3 |  1 |  1 |  3 |  2 |  2 |

#### Chaining

> I sometimes call it linear chaining to indicate a linked list since you could use a BST if you know your going to face a high number of collisions

#### Linear Probing

Basically just a linear search ones the collision happens

#### Double hashing

Slightly more complex but basically it is just

```c
i = 0;
pos;
do {
   pos = (hash(key) + i * hash2(key)) % len(table);
   i++;
} while collision at pos;
```

## Side note:

Some hash functions are listed [here](http://www.cse.yorku.ca/~oz/hash.html)

I personally like djb2 since it's simple and just good for in general.  So I'll rewrite it in more of a 1511/2521 style

```c
// char on most systems is probably unsigned
// but often with hashes because we are shifting
// we really want to make sure it is
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    size_t pos = 0; // support ridiculously long strings
    while (str[pos] != '\0') {
        // some places do (hash << 5) + hash but it's the same thing
        hash = hash * 33 + str[pos];
        pos++;
    }
    return hash;
}
```

You'll notice all hash algorithms use prime numbers!!

Very popular second hash functions look like; `hash2(key) = PRIME - (key % PRIME)` where `PRIME < len(table)`

> Second hash functions can't evaluate to 0 and must ensure that all positions will be eventually searched.

## Functional Stuff!

Do we want to write some haskell code?  I'm up for it if you want?

## Function Pointers

We interpret it from inside out spiraling. using the left right left rule.

Always start at the identifier and read the following symbols as;
- * => pointer to (always on left)
- [] => array of (always on right)
- () => function returning (always on right)

For example:

```c
int *p[];
```

is interpreted as;

```c
       p          // p is
       p[]        // an array of
      *p[]        // pointers to
  int *p[]        // int
```

i.e. p is an array of pointers to ints

Example for functions

```c
int *(*func())();
```

is

```c
       func        // func is
       func()      // a function returning
      *func()      // a pointer to
     (*func())()   // a function returning
    *(*func())()   // a pointer to
int *(*func())()   // an int
```

Therefore func is a function returning a pointer to a function returning a pointer to an int.

## Map

```c
typedef int (*map_apply)(int); // f is a pointer to a function (taking int) returning int
void map(List L, map_apply f) {
    if (!empty(L)) {
        head(L) = (*f)(head(L));
        map(tail(L), f);
    }
}
```

Trace the calls of function call on list [1, 3, 5, 7, 9]

```c
int square (int x) { return x * x; }
map(myList, square);
```

In haskell (we'll come back to this in a moment):

```haskell
-- You typically don't modify lists in haskell
-- Just create new ones.
my_map :: [Int] -> (Int -> Int) -> [Int]
-- tail isn't the last element in haskell it is the list of all elements
-- but the first one or the head. i.e. tail of [1 2 3] is [2 3]
my_map xs f = if null xs then [] else f (head xs) : my_map (tail xs) f

-- Though I would personally write it as
my_map' :: [Int] -> (Int -> Int) -> [Int]
my_map' [] f = []
-- 'x' is the head and 'xs' is the 'tail' of the list
my_map' (x:xs) f = f x : my_map' xs f
```

## Fold

```c
typedef int (*foldR_func)(int, int);
int foldR(List L, foldR_func f, int z) {
    if (empty(L)) return z;
    else          return f(head(L), fold(tail(L), f, z));
}
```

i.e. it does the right most first.  So apply it to the list [2, 3, 4] using the following;

```c
int mult(int x, int y) { return x * y; }

int product = foldR(myList, mult, 1);
```

Trace function calls...

### Haskell Aside of lists

For example in haskell if you wanted to sum up a list you would do

```haskell
-- lists are provided to you and are linked lists by default
-- But creating our own is easy!
-- 'a' is just a type
data List a = Null
            | Cons a (List a)
            deriving (Show)

-- takes in a list of numbers and returns a number
sumList :: (Num a) => List a -> a
-- empty list is obviously just 0
sumList Null = 0
sumList (Cons x rest) = x + sumList rest

-- To make it foldable we have to do
-- (You can ignore this it is just to make the foldable work)
instance Foldable List where
    foldMap f Null = mempty
    foldMap f (Cons a rest) = f a `mappend` foldMap f rest

-- But we can use a functional tool called foldl
sumList' :: (Num a) => List a -> a
sumList' = foldl (+) 0

-- And it turns out there is already a list built for us
inbuilt_sumList :: (Num a) => [a] -> a
inbuilt_sumList [] = 0
inbuilt_sumList (x:xs) = x + inbuilt_sumList xs

inbuilt_sumList' :: (Num a) => [a] -> a
-- (+) is the function + i.e. add :: (Int -> Int) -> Int a b = a + b
inbuilt_sumList' = foldl (+) 0

-- and to multiply
list = [2, 3, 4]
-- (*) is the function '*' i.e. mul :: (Int -> Int) -> Int a b = a * b
product = foldr (*) 1 list
```

## Fibonacci

In haskell...

```haskell
-- Integer is arbitrary precision i.e. as big as you want
fib :: Int -> Integer
fib n | n < 0 = error "Fib is only defined for positive integers (and 0)"
-- you could write this as fib n | n <= 1 = 1
fib 0 = 0
fib 1 = 1
fib n = fib(n - 1) + fib(n - 2)
```

In C

```c
// Most people start fib at 0.
// I believe tute starts it at 1.
// I'll start it at 0
int fib(int n) {
    assert(n >= 0);
    if (n <= 1) return 1;
    else        return fib(n - 1) + fib(n - 2);
}
```

> Let's run them and see what happens

This quickly gets out of hand in terms of the number of calls i.e. for 5 it is

```
                fib(5)
               /     \
              /     fib(3)
             /     /      \
            /     fib(2)  fib(1)
           /     /    \
          /     fib(1) fib(0)
         /
        fib(4)
        /    \
       /    fib(2)
      /     /    \
     /    fib(2) fib(1)
    fib(3)
   /    \
  fib(2) fib(1)
 /     \
fib(1) fib(0)
```

We can memoize this to make it much faster...

> We may not get time for this but I'll try!

In haskell it will be...

```haskell
memoize :: (Int -> a) -> (Int -> a)
-- Basically we are just setting it up
-- So our 'thunks' can be shared with fib :)
memoize f = (map f [0 ..] !!)

memoized_fib :: Int -> Integer
momoized_fib = fix $ memoize . fib
```

