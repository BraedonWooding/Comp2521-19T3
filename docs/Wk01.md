# Wk01 - Recap

## Introductions

- Introduce yourself
- What did you find interesting from COMP1511
- Is there anything from COMP1511 that you felt you didn't understand fully
- Lab Partners

## What does the following do?

```c
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
 
int main(int argc, char *argv[])
{
	int i, j, *a;
	int N = 0;
 
	// initialisation
	assert(argc > 1);
	sscanf(argv[1], "%d", &N);
	assert(N > 0);
	a = malloc(N*sizeof(int));
	assert(a != NULL);
	for (i = 2; i < N; i++) a[i] = 1;
 
	// computation
	for (i = 2; i < N; i++) {
		if (a[i]) {
			for (j = i; i*j < N; j++) a[i*j] = 0;
		}
	}
 
	// results
	for (i = 2; i < N; i++) {
		if (a[i]) printf("%d\n",i);
	}
	exit(EXIT_SUCCESS);
}
```

It may seem obscure at first so let's break it down into individual lines;

- What does `assert` do?

It checks if the condition is false and if it is then it aborts the program with an error

- What happens when you don't have braces around for loop statements => It will then 'add' braces ONLY around the next statement
So that

```c
if (a)
  b();
  c();
```

Is identical to

```c
if (a) {
  b();
}

c();
```

- What does `sscanf(argv[1], "%d", &N)` do?

It is scanf but for strings, scans in a number from the string `argv[1]`

- Alternatives for `sscanf`?  There are a few...

`atoi, strtol, strtoi` will all work.

- For each of the asserts
  - What are they checking
  - What is a better error message that we could display
  
Just generally print out what the values were that you were checking i.e. `N = 4` and print out why that is bad.
  
- What does `exit` do?

Exit the program completely.  Like return 0 in main function.

- What is the value of `a[0]` and `a[1]` during the execution of the program
  - Do we care?  Do they even matter?
  
We don't care because we never touch them.  They will be undefined.

You can only read memory you write.
  
- What does the program produce

The prime numbers according to the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)

Now some of the next content you may not have covered in lectures but you will need for the lab so I'm still going to cover.

- What is Big O Notation?  i.e. `O(n)` what does that mean?  What does it tell us?

It tells you how fast a function grows.

i.e.

```
for (int i = 0; i < N; i++) {
   // 1)
}

for (int x = 0; x < SIZE; x++) {
  for (int y = 0; y < SIZE; y++) {
    // 2)
  }
}
```

The first one will be `O(n)` and the second one will be `O(n * n)` or `O(n^2)`

- What is the Big O Notation of the above code?

The sieve of eratosthenes will be `O(n log (log n))` (which is often referred to as super linear) so I was wrong!  It wasn't `O(n sqrt(n))`.  The reasoning is relatively complex and is due to the prime harmonic series approaching `log(log n)`.

## A 'real' world example!

`CPath` demonstration from [here](https://github.com/BraedonWooding/cpath).

Python is known to be very slow but here you can see that that it's actually faster than Cute Files and TinyDir which are written in C!!!!

| Test                     | User   | System | Wall   |
| ------------------------ | ------ | ------ | ------ |
| CPath (Recursion in C)   | 0.020s | 0.062s | 0.082s |
| CPath (Emplace in C)     | 0.020s | 0.063s | 0.083s |
| CPath (Recursive in cpp) | 0.020s | 0.062s | 0.082s |
| CPath (Emplace in cpp)   | 0.020s | 0.063s | 0.083s |
| find                     | 0.021s | 0.126s | 0.147s |
| Python (os.walk)         | 0.156s | 0.081s | 0.237s |
| Cute Files (C)           | 0.041s | 0.243s | 0.284s |
| TinyDir (C)              | 0.050s | 0.244s | 0.294s |
| tree                     | 0.369s | 0.256s | 0.626s |

Why?

- Look at the user time, what does that mean?  => That the language doesn't always determine the speed
- What is system time?  What does this indicate to us? => That a lot of time is spent looking at files/folders

What does this tell us!

Feel free to check out the code [here](https://github.com/BraedonWooding/cpath) but keep in consideration it is just a rough sketch and a lot of the code is prone to change as I head towards stabilisation :).

And continuing on this note let us write some bash code to generate a ridiculous amount of files!

This will help with this week's lab if you want to write some testing code!

```bash
mkdir tmp
for i in {1..9}; do
  mkdir "tmp/a$i"
  for j in {1..99}; do
    mkdir "tmp/a$i/b$j"
    for k in {1..49}; do
      touch "tmp/a$i/b$j/$k.tmp"
    done
  done
done
```

This is pretty straightforward and not examinable, knowing bash in this course is really important as it can make some automation tasks much much much easier!!!

In C using my library it'll be something like

```c
#include "cpath.h"

int main(void) {
    cpath path = cpathFromUtf8("tmp");
    cpathMkdir(&path);

    for (cpath_char_t i = 1; i < 10; i++) {
        cpathAppendSprintf(&path, "/a%d", i);
        cpathMkdir(&path);
    
        for (cpath_char_t j = 1; j < 100; j++) {
            cpathAppendSprintf(&path, "/b%d", j);
            cpathMkdir(&path);
        
            for (cpath_char_t k = 1; k < 50; k++) {
                cpathAppendSprintf(&path, "/%d.tmp", k);
                FILE *f = cpathOpen(&path, CPATH_STR("w"));
                fclose(f);
                cpathUpDir(&path);
            }
            cpathUpDir(&path);
        }
        cpathUpDir(&path);
    }
    return 0;
}
```

Can you see the similarities to the above bash example?

Want to see the time difference!

Let's run it ourselves we'll have to leave the bash program for a few minutes so we'll run the C program first.

I'm going to run these on my Mac because well the CSE servers are quite a bit slower in terms of IO with the C program taking about 6x the time so it took over 10 mins for the bash program which we don't really have to wait :).  Feel free to copy the files and run it yourself though if you want.

- Carrying on what we were talking about before what perks your interest about the time spent
  - Clearly the user time is high but what about that system time!
  
One small final note about benchmarking:
- Be really really really careful, you'll always get the benchmarks wrong the first time.  Either you'll compile with the wrong settings or write a program that is slow and claim it is the language.
- User Time + System Time != Wall Time, so just tracking how long it took your program to complete is often not a good idea.  For example if I run the program with spotify and chrome and emacs and a billion other things it takes a longer amount of time because the OS has to divide up it's resources between each program.  So NEVER trust the wall time, always aim for user time.  In some cases you care about system time but in the lab you will ONLY care about user time.

As a rule of thumb if your conclusions ever is
- X language is faster than Y language always
- X framework/library is faster than Y framework/library always
- My code is faster than your code always

Then you probably are wrong always think about cases.

The following are valid claims:

- The C programming language will often outperform Python in user time given equally optimised non-trivial programs
- X sort is faster than Y sort in the random case
- BogoSort is the one of the greatest sorting algorithms ever only surparsed by miracle sort.

## IO

What are the following
- argc/argv
- stdin/stdout/stderr

Consider the following program

```c
// my_prog.c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("%s", argv[1]);
    putchar(getchar());
    return 0;
}
```

If we executed the following;

```bash
$ gcc my_prog.c -o my_prog
$ ./my_prog hello there, "John Shepard" < in > out
```

The file `out` contains `Hello Sailor` and the file `in` contains just the word `hey` prior the running the second command.

- What is argc and argv?  => argc is the number of arguments and argv are those arguments as space delimited strings
- Where does getchar take it's character from => stdin which in this case is going to be `in`
- What is printed out to terminal and what is the contents of `out` and `in` after running the command. => `in` won't change, `out` will be `helloh`.  Noting is outputted to terminal.
- What does `>>` do compared to `>` => it appends to the file

## More IO

What does each of the following do.  Note `int x;` is defined prior.

- `scanf("%d", x)` => error not a pointer
- `scanf("%d", &x)` => fine
- `printf("%d", x)` => fine
- `fscanf(stdin, "%d", &x)` => same as the 2nd one
- `fscanf(stderr, "%d", &x)` => shouldn't scan from stderr
- `fprintf(stdout, "%d", x)` => Same as the 3rd one
- `fprintf(stderr, "%d", x)` => Fine, will output to stderr

## Functions

- Make a swap function that exchanges 2 elements in an array. i.e. `swap(array, i, j)` will swap `array[i]` and `array[j]`

Consider the following Linked List

```c
typedef struct _node_t {
    int value;
    struct _node_t *next;
} Node;

typedef Node *List;
```

- What is good about the typedefs, what is bad?  Is there any ambiguity => There is a lot of ambiguity with pointer typedefs
- Write a function to sum up the list using while, for, and then recursive 

Coding solutions [here](https://github.com/BraedonWooding/Comp2521-19T3/tree/master/Tute1_Files)!

## Final Stuff

Make sure you are comfortable with:

- Structs
- Pointers
- Malloc
- Linked Lists
