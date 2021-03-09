// Illustration of both BFS (breadth first search) and DFS (depth first
// search) as two variations of a general "BagSearch" method.  The Bag is
// a Queue or a Stack, respectively.

#include <stdlib.h>		// exit()
#include <iostream.h>
enum Boolean {FALSE, TRUE};

// Abstract class Bag, realized as either a Stack or Queue.  We also define
// BagNodes and BagIterators.  For simplicity, we do not use templates;
// everything is a Bag of int's.
//
// Any Bag supports the operations: Insert, Delete, IsEmpty.

class Bag {
friend class BagIterator;
protected:			// visible to Stack and Queue
  class BagNode {
  public:
    int data;			// the data
    BagNode *link;		// the link to next node
    BagNode(int val, BagNode *l = 0) { data=val; link=l; };
  };
  BagNode *front;
public:
  Bag() { front=0; };		// redefined for Queue
  Boolean IsEmpty() { if (front) return FALSE; return TRUE; }
  virtual void Insert(int) = 0;
  virtual int* Delete(int&) = 0;	// return address of argument, or 0 if empty
};

// Stack: a last-in-first-out (LIFO) Bag

class Stack: public Bag {
public:
  // Bag::Bag() and Bag::IsEmpty() are fine.
  void Insert(int y) { front = new BagNode(y,front); }
  int* Delete(int &ret) {
    if (front==0) return 0;
    BagNode *x = front;
    ret = front->data;
    front = front->link;
    delete x;
    return &ret;
  }
};

// Queue: a first-in-first-out (FIFO) Bag

class Queue: public Bag {
private:
  BagNode *rear;
public:
  Queue() { front = rear = 0;} // constructor
  void Insert(int y) {
    if (front==0) front = rear = new BagNode(y,0);
    else rear = rear->link = new BagNode(y,0);
  }
  int* Delete(int &ret) {
    if (front==0) return 0;
    BagNode *x = front;
    ret = front->data;
    front = front->link;
    if (!front) rear=0;
    delete x;
    return &ret;
  }
};

// BagIterator: an simple iterator for Bags (either kind).
class BagIterator {
private:
  Bag *bag;
  Bag::BagNode *current;
public:
  void Init(Bag &b) { bag=&b; current=b.front; } // (re)initialize to start of b
  BagIterator(Bag &b) { Init(b); } // construct with an argument
  BagIterator() { bag=0; current=0; } // construct, uninitialized
  Boolean NextData(int &d) {	// try to read data and move to next
    if (!current) return FALSE;
    d = current->data;
    current = current->link;
    return TRUE;
  }
};

// In our graphs (below) vertices are integers, and edges are represented
// as adjacency lists.

class Graph
{
private:
  int n;			// The vertices are the integers 0 to n-1.
  Stack *Adj;			// array of n adjacency lists
public:
  Graph(int vertices = 0) : n(vertices) { Adj = new Stack[n];};
  ~Graph() { delete [] Adj; }
  void BFS(int);
  void DFS(int);
  void Setup();
  void AddEdge(int i,int j) { Adj[i].Insert(j); Adj[j].Insert(i); }
  void AddDiEdge(int i,int j) { Adj[i].Insert(j); }
private:
  void BagSearch(int, Bag*, Boolean); // does BFS or DFS, depending on Bag
};

void Graph::Setup()
{
  // Start with 8 vertices and no edges:
  cout << "Setting up the graph ..." << flush;
  Graph(8);

  // Add undirected edges to make this graph:
  //
  //   +---0---+
  //   |       |
  //   | 3   5 |
  //   |/ \ / \|
  //   1   7   2
  //    \ / \ /
  //     4   6
  AddEdge(0,2); AddEdge(0,1); AddEdge(1,4); AddEdge(1,3); AddEdge(2,6);
  AddEdge(2,5); AddEdge(3,7); AddEdge(4,7); AddEdge(5,7); AddEdge(6,7);
  cout << " done." << endl;
}

////////////////// THIS IS THE MAIN POINT

void Graph::BFS(int root)	// Breadth First Search, use a Queue
{
  Bag *q = new Queue;
  BagSearch(root,q,FALSE);
  delete q;
}

void Graph::DFS(int root)	// Depth First Search, use a Stack
{
  Bag *s = new Stack;
  BagSearch(root,s,TRUE);
  delete s;
}

////////////////// THAT WAS THE MAIN POINT


// Arrows:     v -----> w
//
// An "arrow" is an edge out of a vertex v.  We "rotate" an arrow
// about v by stepping through the adjacency list to v's next neighbor.
// In the search below, each vertex has an arrow, which starts at the
// beginning of its adjacency list.

void Graph::BagSearch(int root, Bag *bag, Boolean DF)
{
  // Bag should be empty.
  if (!bag->IsEmpty()) {
    cerr << "BagSearch: bag not empty!" << endl;
    exit(1);
  }

  // array of parents, one per vertex. -1 means no parent is known:
  int *parent = new int[n];
  for (int i=0; i<n; i++) parent[i] = -1;

  // An array of BagIterators, one per vertex.  These are the "arrows".
  // arrow[i] starts at the front of the adjacency list of vertex i.
  BagIterator *arrow = new BagIterator[n];
  for (i=0; i<n; i++) arrow[i].Init(Adj[i]);

  //  Put the root vertex in the bag.
  // cout << "Starting search at " << root << endl;
  parent[root]=root;		// nobody can become the parent of root
  bag->Insert(root);

  int current, child;
  // While the bag is not empty, delete a "current" vertex.
  while (bag->Delete(current)) {
    cout << "Grabbed " << current << " from the bag." << endl;
    // Rotate current's arrow, looking for an unvisited child.
    while (arrow[current].NextData(child)) {
      cout << "Trying arrow from " << current << " to " << child << ", " << flush;
      if (parent[child] >= 0)
	cout << "already has a parent." << endl;
      else {
	cout << "a new child!" << endl;
	parent[child]=current;
	// Depending on DF, we save one of the vertices back in the bag,
	// and continue looking at the other.
	switch (DF) {
	case TRUE : bag->Insert(current); current=child; break;
	case FALSE: bag->Insert(child); break;
	}
      }
    }
    cout << "Exhausted all arrows out of " << current << endl;
  }
  cout << "The bag is empty, so the search is over." << endl;

  delete [] parent;
  delete [] arrow;
}



main()
{
cout<<"Type the # of verticies followed by # of edges:"<<endl;
int num_vert;
num_vert=cin.get()-'0';
while ((cin.peek()>='0')&&(cin.peek()<='9')){ num_vert=num_vert*10+(cin.get()-'0');}
cout<<"num_vert= "<<num_vert<<endl;

if (num_vert<=0) {cerr<<"invalid entry"<<endl;  exit(0);}
Graph g(num_vert);
cout<<num_vert<<" verticies constructed"<<endl;
int vert1, vert2;
int done=0;

  while(! done){
	vert1=cin.get();
	switch (vert1){
	  case ' ': case '\t': case 'n': case 'r':
	  continue;				//ignore whitespace

  	  case '-':
	  done=1; cout<<"term signal"<<endl; continue;

	  default:
	  if ((vert1>='0')&&(vert1<='9')){
	  if ((cin.peek()<'0')||(cin.peek()<'9')) vert1=vert1-'0';
	  while ((cin.peek()>='0')&&(cin.peek()<='9')){ vert1=vert1*10+(cin.get()-'0');}

	  vert2=cin.get();
	  while (vert2==' '){ vert2=cin.get();}
	  if ((cin.peek()<'0')||(cin.peek()<'9')) vert2=vert2-'0';
	  while ((cin.peek()>='0')&&(cin.peek()<='9')){ vert2=vert2*10+(cin.get()-'0');}

	  cout<<"vert1= "<<vert1<<endl<<"vert2= "<<vert2<<endl;
	  g.AddEdge(vert1, vert2);
					 } 
		      }// end of switch
 	       }// end of while
}//end of main()
