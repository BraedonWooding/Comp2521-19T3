# Week 6 Graphs (and midsem)

!> The answers are here https://cgi.cse.unsw.edu.au/~cs2521/19t3/tutes/week06/index.php

Very very big tute this week...

Hope you have all studied.  First off do you have any quick questions about it?

And do you want me to go through any of the problems?

## Graph overview

### Adjacency Matrix vs Adjacency List

> You can assume V x V matrix and presume that non-directional edges are bi-directional.

![graphs](assets/img/graphs.png)

> NOTE to me: Do it in order i, iii, ii

For each of these graphs show the adjacency matrix and adjacency list.

## Interesting application of matrices to solving the number of spanning trees given a graph

I couldn't imagine they would ask you this in an exam since it requires quite a bit of linear algebra but eh.

So as you probably know we can use Kruskall's algorithm to find a spanning tree (if you don't then it'll be talked about eventually probably sometime next week).  But that'll only find one, how can we find maximum number of unique spanning trees.

For example;

![edges](assets/img/edges_spanning.png)

Now we could count it manually via getting each edge and seeing which edges we can remove (this is what you could be asked to do in an exam) to give a spanning tree.

- e1 & e3, e4, e5
- e2 & e3, e4, e5
- e3 & e5 (e2 and e3 is handled above)
- e4 & e5 (e4 and e3 is handled above)
- e5 & none (e5 and the rest are handled above)

Therefore a total of 8!

Or we can utilise 2 methods.

### We can utilise Cayley's Formula for complete graphs

Our graph here is not complete so we can't use this (what edge would make it complete) but if it was we can utilise Cayley's formula to find the number of labelled trees with n vertices (note tree!) this will be equal to the number of spanning trees.

It'll just be V^(V - 2).

### We can use linear algebra for a more general case

Basically we are going to find something called the 'cofactor'.

1. To begin let's get our adjacency matrix up.
2. Then let's replace all the diagonals with the degree of that given vertex i.e. `A\_ij = deg(i), i = j`.
3. Replace all non-diagonal 1's with -1 i.e. `A\_ij = -1, i != j and A\_ij = 1`
4. To compute the cofactor of (i, j) you just ignore the row's and columns of (i, j) and compute the determinant of the result

> We can take the cofactor of any position they will all be the same.  NOTE: you may have to absolute the result.

## Web Crawling

```c
crawl(startURL)
{
	add startURL to Queue
	while (Queue is not empty) {
		nextURL = remove head of Queue
		page = open(nextURL)
		while ((url = scanForHyperlinks(page)) != NULL) {
			if (alreadySeen(url)) continue
			add url to Queue
		}
	}
}
```

?> How would we handle alreadySeen?

The tutorial solutions just say the 'right' answer with 0 justification so nah.  Let's actually talk about it.  We are meant to be scientists after all!

A few solutions (that are wrong in one way or another)

### Efficient Storing

Just store the hash, we can store this as 8 bytes.  We can choose a hash function such that a hash of 0 is only mapped to the empty string (this is actually pretty straightforward) this allows us to have a contains flag without more space.  There are 1 billion websites in the world so this hashmap would need atleast 8 billion bytes or 8 GB of ram (taking an approximation of 1 GB ~ 10^9 Bytes which is kinda correct anyways depending on how you define it as either gigabyte or gibibyte; giga is 1000, gibi is 1024 but no one really follows this).

Now this doesn't handle suburls well but window's servers can apparently support up to 24 TB of ram and apparently Linux (more common for servers) support up to 256 TB dpeending on your distro.  So well I think in terms of space we probably could be fine and maybe it could scale well enough??  But it's a bit rough definitely.

But there is a more important issue here what is it?  For a 8 byte integer how many unique representations can we have?

?> 18,446,744,073,709,551,615 is the answer to the second question or ... eighteen quintillion, four hundred forty six quadrillion, seven hundred forty four trillion, seventy three billion, seven hundred and nine million five hundred and fifty one thousand six hundred and fifteen

Okay maybe we have enough to store all the websites we want but there is still an issue!

?> The tutorial solutions say that our hashtable couldn't store the whole web, I disagree but only on a technicality.  A hashtable could contain everything but only if you are being obscure and only storing the hash.  If you also want to store the key (which you should) and some appropriate value (in our case we don't need to store a value why?) than it won't fit (probably I hate saying 'no' in cs since it's an outdated term).

### Storing hashtable on disk

This would solve all our storage problems (we can get some huge drives) but the disk would be very very very slow.  So we really wouldn't get the speed we would need.

### Correct solution (I guess) using a distributed hash map

Basically you store sections of the hashmap on different systems would allow you to scale.  This is typically called a map-reduce computational strategy (fancy word for splitting a map across systems).

## Some small clarification on HashMap vs HashTable vs Map

Typically 'Map' refers to a binary tree (O(log n) lookups) and 'HashMap' refers to a map where we use hash functions to compare with a HashTable being an array that a hash function is distributed across using either chaining, probing, or second hash functions to properly distribute.  BUT most computer scientists (me included and I believe Ashesh) will use 'HashMap' and 'HashTable' interchangably.

For example in C++ you have std::map which is just a standard binary tree (implemented typically as red black!! :D) where as std::unordered_map is a hashtable (they don't even have 'hash' in the name ew!).

## BFS vs DFS

What would be printed if using dfs vs bfs?  When deciding which one to choose always choose the smallest unvisited node.

<!-- panels:start -->

<!-- div:left-panel -->

Do the following for the below two methods.

```c
depthFirst (g, 0);
depthFirst (g, 3);
breadthFirst (g, 0);
breadthFirst (g, 3);
```

<!-- div:right-panel -->

![bfs vs dfs](assets/img/bfs_dfs.png)

<!-- div:left-panel -->

```c
void breadthFirst (Graph g, Vertex v) {
	int *visited = calloc (g->nV, sizeof (int));
	Queue q = newQueue ();
	QueueJoin (q, v);
	while (QueueLength (q) > 0) {
		Vertex x = QueueLeave (q);
		if (visited[x]) {
			continue;
        }
		visited[x] = 1;
		printf ("%d\n", x);
		for (Vertex y = 0; y < g->nV; y++) {
			if (!g->edges[x][y]) {
				continue;
            }
			if (!visited[y]) {
				QueueJoin (q, y);
            }
		}
	}
}
```

<!-- div:right-panel -->

```c
void depthFirst (Graph g, Vertex v) {
	int *visited = calloc (g->nV, sizeof (int));
	Stack s = newStack ();
	StackPush (s, v);
	while (!StackIsEmpty (s)) {
		Vertex x = StackPop (s);
		if (visited[x]) {
			continue;
        }
		visited[x] = 1;
		printf ("%d\n", x);
		for (Vertex y = g->nV - 1; y >= 0; y--) {
			if (!g->edges[x][y]) {
				continue;
            }
			if (!visited[y]) {
				StackPush (s, y);
            }
		}
	}
}
```

<!-- panels:end -->

## Connected vs Complete

Connected just means all nodes are reachable.

Complete means all nodes are reachable using a single edge from any other node.

Therefore Complete implies Connected and not connected implies not complete.

![connected](assets/img/connected_vs_complete.png)

## Vertex indexed component arrays

![example](assets/img/graph_example.png)

What is the vertex-indexed component array of above?

?> Just look at each vertex and see which group it is in i.e. [0, 0, 0, 1, 1, 1, 0, 0, 0, 1]

1. What bridges exist?  (A bridge is an edge that would cause a new component to exist if you remove it)
2. What is the component array if you remove d?
3. What is the component array if you remove b?

## A grounded example of graphs

![sydney](assets/img/SydneyCBD.png)

Above is an image of sydney's CBD area.  Let's first represent it as a directed graph making sure to reflect oneway streets.

!> Castlereagh St is one-way heading south and Hunter St is one-way heading west. (they don't show on the map).

For each path say if there are multiple (just say one though for time reasons) and indicate if there isn't a path.

1. From D to L
2. J to A
3. A to M
4. M to H

