// Prototypes

typedef void *Set;
typedef void *Queue;
typedef void *Graph;
typedef int Vertex;

Set newSet(int len);
Queue newQueue(void);
void enqueue(Queue q, Vertex v);
void addToSet(Set s, Vertex v);
int queueLen(Queue q);
Vertex dequeue(Queue q);
int setHasElement(Set s, Vertex v);
int graphNumV(Graph g);
int graphAdjacent(Graph g, Vertex from, Vertex to);

// Could you do this recursively?
Set reachable(Graph g, Vertex v) {
    Set seen = newSet(graphNumV(g));
    Queue q = newQueue();
    enqueue(q, v);
    while (queueLen(q) > 0) {
        Vertex n = dequeue(q);
        addToSet(seen, n);
        for (int i = 0; i < graphNumV(g); i++) {
            if (graphAdjacent(g, n, i) && !setHasElement(seen, i)) {
                enqueue(q, i);
            }
        }
    }

    return seen;
}