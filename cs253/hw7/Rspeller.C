/*
Parker Johnson
HW7 4-25-96

Abstact:
 
Parse the first file (dictionary) and put all of the words into memory: each w$
into a chained hash table. Parse second file (text) and check to see if in has$
table.  If not print out the word.
 
Coding:
 
Used the same parsing as in wc.C and used much of the same code as in
HW6.
 the file consists of 4 functions:
 
Main()--takes in the two files and calls my function read_and_hash() on the fi$
file (the dictionary file) and calls read_and_print() on the second file (the
text file)
 
read_and_hash()--opens the file and inserts all of the words in that file (the
dict file) into the chained hash table using the hashing function.
 
read_and print()--opens the file (text) and determines using the hash function
where the word is or would be stored and sets up a list iterator on that list.$
If the word is found on the iteration is is not printed out.  If it not found
upon li.Done() than that word is sent to the standard output and the new
word is inserted into the table so that no two same words are printed twice.
 
get_word()--grigni's function to parse a file into individual words and return$
ptr to those words
 
 Using the rogue wave libraries, I did not have to write a hash function
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
#include <rw/hashtab.h>		// RW hashtable headers
#include <rw/collstr.h>
#include <rw/cstring.h>
RWCollectableString * get_word(istream& is);				//grigni's parsing func


  RWHashTable table;
  RWCollectableString * word;

RWCollectableString * get_word(istream& is)				//grigni's parsing func
{
  char wordbuf[81];

  while (is >> wordbuf)
    {
      char* beg=wordbuf; while (*beg && !isalpha(*beg)) beg++;
      char* end=beg; while (*end) end++; end--;
      while (end >= beg && !isalpha(*end)) end--;
      if (end < beg) continue;
      *++end='\0';

return new RWCollectableString (beg);
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

  while (word = get_word(infile))	
    {table.insert(word); }		//insertion
}


void read_and_print (const char* filename)	//takes in text file
{
  // Try to open the named file:
  ifstream infile(filename);
  if (!infile) {
    cerr << "could not read file " << filename << endl;
    exit(1);
  }

  while (word = get_word(infile))
    {
	if (!table.contains(word)) {cout<<*(word)<<endl; table.insert(word);} 
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
