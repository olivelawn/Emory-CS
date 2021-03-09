	// This is a partial solution to Homework 5.  In particular, it reads
// a graph from cin, does an exhaustive recursive DFS, and prints out
// the vertices in the order that they are visited (this "visiting
// order" is *not* the same as the "finishing order").
//
// This file is based on ../../book/c6/adj.cpp.

#include <stdlib.h>
#include <iostream.h>
#include "Stack.C"

template <class KeyType>
void Stack<KeyType>::StackEmpty(){ cerr<<"Error:Stack empty or user inputed neg exp"<<endl; exit(1);}
 
template <class KeyType>
void Stack<KeyType>::StackFull(){ cerr<<"Stack full"<<endl; exit(1);}

Stack<int> fin;
int elem=0;
//enum Boolean { FALSE, TRUE};
enum Status { UNVISITED, ACTIVE, FINISHED };


template <class Type> class List;
template <class Type> class ListIterator;

template <class Type>
class ListNode {
friend class List<Type>;
friend class ListIterator<Type>;
private:
    Type data;
    ListNode *link;
    ListNode(Type);
};

template <class Type>
ListNode<Type>::ListNode(Type Default)
{
    data = Default;
    link = 0;
}

template <class Type>
class List {
friend class ListIterator<Type>;
public:
    List() {first = 0;};
    void Insert(Type);
    void Delete(Type);
private:
    ListNode<Type> *first;
};

template <class Type>
void List<Type>::Insert(Type k)
{
ListNode<Type> *newnode = new ListNode<Type>(k);
newnode->link = first;
first = newnode;
}

template <class Type>
void List<Type>::Delete(Type k)
{
    ListNode<Type> *previous = 0;
    for (ListNode<Type> *current = first; current && current->data != k;
	previous = current, current = current->link);
   if (current)
   {
       if (previous) previous->link = current->link;
       else first = first->link;
       delete current;
   }
}

template <class Type>
class ListIterator {
public:
    ListIterator(const List<Type>& l): list(l) {current = l.first;}
    Type* First();
    Type* Next();
    Boolean NotNull();
    Boolean NextNotNull();
private:
    const List<Type> &list;
    ListNode<Type>* current;
};

template <class Type>
Type* ListIterator<Type>::First() {
      if (current) return &current->data;
      else return 0;
}

template <class Type>
Type* ListIterator<Type>::Next() {
      current = current->link;
      return &current->data;
}

template <class Type>
Boolean ListIterator<Type>::NotNull()
{
if (current) return TRUE;
else return FALSE;
}

template <class Type>
Boolean ListIterator<Type>::NextNotNull()
{
if (current->link) return TRUE;
else return FALSE;
}

//template <class Type>
ostream& operator<<(ostream& os, List<char>& l)
{
    ListIterator<char> li(l);
    if (!li.NotNull()) return os;
    os << *li.First() << endl;
    while  (li.NextNotNull())
	 os << *li.Next() << endl;
    return os;
}

class Graph
{
  // Read a graph from an input stream:
  friend istream& operator>> (istream&,Graph&);
private:
  List<int> *HeadNodes;
  int n;
  void DFS(const int);		// recursive DFS routine
  Status *visited;		// temporary array during ExhaustiveDFS()
  int *b; 

public:
  // Constructor:
  Graph(const int vertices = 0) : n(vertices)
  { HeadNodes = new List<int>[n];}
  // Destructor:
  ~Graph() { delete [] HeadNodes; }
  // Add a directed edge from vertex i to vertex j:
  void AddDiEdge(int i,int j) { HeadNodes[i].Insert(j); }
  // Exhaustive DFS:
  void ExhaustiveDFS();
  void cyclic_print(int);
  void Topological_print();
  void init();
};

void Graph::init()
{
b=new int[n];
while (elem < n) { b[elem++]=-1;}
elem=0;
}

// Read a graph from an input stream
istream& operator>> (istream& input, Graph& g)
{
  int a, b;
  // input >> n; g.Graph(n); // does not work with our compiler!
  input >> g.n;
  g.HeadNodes = new List<int>[g.n]; // maybe should delete[] old value
  while (1) {
    input >> a >> b;		// read another edge
    if (a<0 || b<0) return input;
    g.AddDiEdge(a,b);
  }
}

/*
This is how I did the program:
I record the visiting order in an array to which *b points to.  
I record the status of each node indexed by that node # in an array called visited

If a cycle is found using the *visited array, the program immeadiately calls the 
cyclic print function using the node that was the first to be found as cyclic in 
the b-> array and then prints numbers to the left if they have a an active status 
as defined by the visited array.  Commented code was used for debugging.
*/

// Recursive DFS workhorse: visit all the vertices reachable from v
void Graph::DFS(const int v)
{ cout<<"here"<<endl;
  if (visited[v] == ACTIVE){ cout<<"what?"<<endl; cyclic_print(v); exit(0);}
  visited[v] = ACTIVE;  b[elem++]=v; 
//  cout<<endl<<"status: "<<endl;
//  for (int m=0; m<n; m++) cout<<visited[m]<<" "; cout<<endl;
//  cout<<endl<<"B: "<<endl;
//  for (int z=0; z<n; z++) cout<<b[z]<<" "; cout<<endl;
  cout << ' ' << v <<endl;	// list vertices in "visiting order"
  ListIterator<int> li(HeadNodes[v]);
  if (! li.NotNull()) { cout<<"v is fin: "<<v<<endl; visited[v] = FINISHED; fin.Add(v); return;}
  cout<<"now"<<endl;
  int w = *li.First();
  while (1) {
    if ( visited[w]!= FINISHED) DFS(w);
    if (li.NextNotNull()) w = *li.Next();
    else { visited[v]=FINISHED; fin.Add(v); return;}
  }
  cout<<endl; // Note: now we are "finished" with v.
}

// Exhaustive DFS: repeat the recursive DFS on each unvisited vertex
// until every vertex has been visited.
void Graph::ExhaustiveDFS()
{
  visited = new Status[n];
  for (int i = 0; i < n; i++) visited[i] = UNVISITED;
  for (i = 0; i < n; i++)
    if  (visited[i]!= FINISHED) DFS(i);
  delete [] visited;
}

void Graph::cyclic_print(int v)
{
  int check;
  int i=0;
//  cout<<endl<<"B: "<<endl;
//  for (int z=0; z<n; z++) cout<<b[z]<<" ";
//  cout<<endl<<"status: "<<endl;
//  for (int m=0; m<n; m++) cout<<visited[m]<<" ";

  cout<<endl<<"Cyclic Graph:";
  while(b[i]!=v) i++;
  while (i<n){
        check=b[i];
        if (visited[check]==1)  cout<<" "<<b[i];
        i++;
	      }
cout<<endl;
}

void Graph::Topological_print()
{
 int ret;
 cout<<"Acyclic Graph in Topological Order:";
   while (! fin.IsEmpty())  {fin.Delete(ret); cout<<" "<<ret;}
}    
   
main()
{
 Graph g;
 cin >> g;			// read the graph from cin
 g.init();
 cout << "Visiting order:"<<endl;
 g.ExhaustiveDFS();
 cout<<endl;
 g.Topological_print();
 cout << endl;
}
