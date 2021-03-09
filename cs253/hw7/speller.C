/*
Parker Johnson
HW7 4-25-96
	
Abstact:

Parse the first file (dictionary) and put all of the words into memory: each word 
into a chained hash table. Parse second file (text) and check to see if in hash 
table.  If not print out the word.

Coding:

Used the same parsing as in wc.C and used much of the same code as in 
HW6.  Class Node, List , and ListIter are taken directly from hw6.  Other than 
that the file consists of 5 functions:

Main()--takes in the two files and calls my function read_and_hash() on the first 
file (the dictionary file) and calls read_and_print() on the second file (the 
text file)

read_and_hash()--opens the file and inserts all of the words in that file (the 
dict file) into the chained hash table using the hashing function.

read_and print()--opens the file (text) and determines using the hash function 
where the word is or would be stored and sets up a list iterator on that list.  
If the word is found on the iteration is is not printed out.  If it not found 
upon li.Done() than that word is sent to the standard output and the new 
word is inserted into the table so that no two same words are printed twice.

get_word()--grigni's function to parse a file into individual words and return a 
ptr to those words

Hash()--takes in a char * and returns a psuedo-random integer coressonding to 
the element that the table uses to insert the char*

I have chosen 20000 buckets for the hash table, sufficient for the ~= 25000 
entries in the dict file.

My hash table is a table of ptr's to chars, and the strcmp() is used to 
determine placement in the table.

I chose to use a hash table with chaining as opposed to open addresing 
because I figured with the exceptionally large number of input and 
likely clustering that the chaining search time would be less than a 
linear search, open addressing approach
 */  


#include <iostream.h>		// cerr, cout, etc.
#include <fstream.h>		// for ifstream class
#include <stdlib.h>		// for exit()
#include <ctype.h>		// for isalpha()
#include <string.h>		// for strcpy(), strlen()

template <class T> struct Node {
  friend class List<T>; friend class ListIter<T>;
  T data; Node<T>* link;        // usual stuff here
	public:
  Node(const T& k, Node<T>* l=0): data(k), link(l) {}
};


template <class T> class List {
  friend class ListIter<T>;
  Node<T>* first;
public:
  List(): first(0) {}
  ~List() {                     // destructor, delete all nodes
    Node<T>* p;
    while (first) { p=first; first=first->link; delete p; }
  }
  void Insert (const T &k) { first = new Node<T>(k,first); } // a copy of k
};


template <class T> class ListIter {
  Node<T>* current;
public:
  ListIter<T>(List<T> &l) { current = l.first; }
  T& Val() { return current->data; } //  return current value (l-value)
  int Done() { return current==0; } // are we done yet? (0/1)
  void Next() { if (current) current=current->link; } // take a step
};



//function prototypes
void read_and_print(const char* filename);
void read_and_hash(const char* filename);
char* get_word(istream& is);
int Hash(char * s);

const int buckets= 20000;				//global buckets and table
List <char *> * table = new List <char *> [buckets];

int Hash(char * s)		//my hashing function
{		
        int r=0; int element;
        while (*s) r=r*17+ *s++;
        return ( abs(r%buckets)); 
}

  
char* get_word(istream& is)				//grigni's parsing func
{
  char wordbuf[81];

  while (is >> wordbuf)
    {
      char* beg=wordbuf; while (*beg && !isalpha(*beg)) beg++;
      char* end=beg; while (*end) end++; end--;
      while (end >= beg && !isalpha(*end)) end--;
      if (end < beg) continue;
      *++end='\0';

      char* ret = new char[1+end-beg];
      strcpy(ret,beg);
      return ret;
    }
  return 0;
}


void read_and_hash(const char* filename) //this func reads in word 
{					//and inserts it into table
  // Try to open the named file:
  ifstream infile(filename);
  if (!infile) {
    cerr << "could not read file " << filename << endl;
    exit(1);
  }
  char* word;

  while (word = get_word(infile))	
    {table[Hash(word)].Insert(word); }		//insertion
}


void read_and_print (const char* filename)	//takes in text file
{
  // Try to open the named file:
  ifstream infile(filename);
  if (!infile) {
    cerr << "could not read file " << filename << endl;
    exit(1);
  }
  char* word;

  while (word = get_word(infile))
    {   int flag=0;				//flag checks for li.done()
	ListIter <char *> li(table[Hash(word)]);
    		for (; !li.Done(); li.Next()) { 
			if ( (strcmp(word, li.Val())) == 0) {flag=1; break;}
				  	      }
	if (flag==0){ cout<<word<<endl; table[Hash(word)].Insert(word);}
		//prints ifnot in table and inserts into table
    }
}

int main(int argc, char **argv)
{

  // Check for right number of arguments:
  if (argc != 3) {
    cerr << "usage: give two arguments: a dictionary file and an input file"
	 << endl;
    exit(1);
  }

  read_and_hash(argv[1]);
  cout << endl;
  read_and_print(argv[2]);
}
