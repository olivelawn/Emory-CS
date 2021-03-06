// This file is ../../book/c5/bst.cpp, with two modifications:
// (1) added a Height() class function to BstNode<> and BST<>
// (2) added "#ifndef no_main ... #endif" around main(), for grading purposes
// -- Mic

#include <iostream.h>

enum Boolean {FALSE, TRUE};
template <class Type>
class Element {
public:
    Type key;
};


template <class Type>
class BstNode {
friend class BST<Type>;
public:
private:
   Element<Type> data;
   BstNode *LeftChild, *RightChild;
   void display(int i);
   void treeprint(int i);
   int Height();
};

template <class Type>
void BstNode<Type>::display(int i)
{
   cout << "Position " << i << ": data.key " << data.key << "\n";
   if (LeftChild) LeftChild->display(2*i);
   if (RightChild) RightChild->display(2*i + 1);
};


template <class Type>
void BstNode<Type>::treeprint(int l)
{
   if (this) {
      (this->RightChild)->treeprint(l+1);
      for (int i = 1; i <= l; i++) cout << "   ";
      cout << this->data.key << "\n";
      (this->LeftChild)->treeprint(l+1);
   };
};

template <class Type> int BstNode<Type>::Height()
{
  // if (!this) return 0; // legal?
  int l = (LeftChild  ?  LeftChild->Height() : 0);
  int r = (RightChild ? RightChild->Height() : 0);
  return ((l > r)? l : r)+1;	// max, plus one
};


//-----------------------------------BST-----------------------------
template <class Type>
class BST {
public:
   BST(BstNode<Type> *init = 0) {root = init;};


   Boolean Insert(const Element<Type>& x);
   Boolean Delete(const Element<Type>& x);
   BstNode<Type>* Search(BstNode<Type>*, const Element<Type>&);
   BstNode<Type>* Search(const Element<Type>&);
   BstNode<Type>* IterSearch(const Element<Type>&);

   void treeprint() { cout << "\n"; root->treeprint(1); }

   void display() {cout << "\n";
		   if (root) root->display(1);
		   else cout << "0\n";};
  int Height() { if (!root) return 0; return root->Height(); };

   Element<Type>* Split(Type i, BST& B, BST& C, Element<Type> &x);

private:
   BstNode<Type> *root;
};

template <class Type>
Element<Type>* BST<Type>::Split(Type i, BST<Type>& B, BST<Type>& C,
Element<Type> &x)  
// Split the binary search tree with respect to key @i@
{
    if (!root) {B.root = C.root = 0; return 0;} // empty tree
    BstNode<Type> *Y = new BstNode<Type>; BstNode<Type> *L = Y;
    BstNode<Type> *Z = new BstNode<Type>; BstNode<Type> *R = Z;
    BstNode<Type> *t = root;
    while (t)
        if (i == t->data.key) {  // split at @t@
            L->RightChild = t->LeftChild;
            R->LeftChild = t->RightChild;
            x = t->data;
            B.root = Y->RightChild; delete Y;
            C.root = Z->LeftChild; delete Z;
            return &x;
        }
        else if (i < t->data.key) {
            R->LeftChild = t;
            R = t; t = t->LeftChild;
        }
        else {
            L->RightChild = t;
            L = t; t = t->RightChild;
        }
    L->RightChild = R->LeftChild = 0;
    B.root = Y->RightChild; delete Y;
    C.root = Z->LeftChild; delete Z;
    return 0;
}


template <class Type>
BstNode<Type>* BST<Type>::Search(BstNode<Type>* b, const Element<Type> &x)
{
   if (!b) return 0;
   if (x.key == b->data.key) return b;
   if  (x.key < b->data.key) return Search(b->LeftChild,x);
   return Search(b->RightChild,x);
};

template <class Type>
BstNode<Type>* BST<Type>::Search(const Element<Type>& x)
{
   return Search(root, x);
}

template <class Type>
BstNode<Type>* BST<Type>::IterSearch(const Element<Type>& x)
{
   for (BstNode<Type> *t = root;  t; )
   {
      if (x.key == t->data.key) return t;
      if (x.key < t->data.key) t = t->LeftChild;
      else t = t->RightChild;
   }
   return 0;
}

template <class Type>
Boolean BST<Type>::Insert(const Element<Type>& x)
{
   BstNode<Type> *p = root;  BstNode<Type> *q = 0;
   while (p) {
      q = p;
      if (x.key == p->data.key) return FALSE; //x.key is already in t
      if (x.key < p->data.key) p = p->LeftChild;
      else p = p->RightChild;
   };

   p = new BstNode<Type>;
   p->LeftChild = p->RightChild = 0; p->data = x;
   if (!root) root = p;
   else if (x.key < q->data.key) q->LeftChild = p;
	else q->RightChild = p;
   return TRUE;
}


/* This is the function that I have implemented.  It finds a node and 
deletes it depending on the locaton of the node and its number of children*/

template <class Type> 
Boolean BST<Type>::Delete(const Element<Type> & x) {  //takes in x by reference
  BstNode<Type> *p=root; BstNode<Type> *q=0; // x is node to be deleted
  int flag=0;
	while(p->data.key!=x.key){	     //finding node and parent
	  q=p;
	       if(x.key < p->data.key) p=p->LeftChild;
		 else p=p->RightChild;
		 //cout<<p<<endl;
	         if (p==0) return FALSE;
				 }
  if (p==root) { flag=1; q=0;}
/*
  cout<<"P->data= "<<p->data.key<<endl;
  cout<<"P->LeftChild= "<<p->LeftChild<<endl;
  cout<<"P->RightChild= "<<p->RightChild<<endl;

  cout<<"Q->data= "<<q->data.key<<endl;
  cout<<"Q->LeftChild= "<<q->LeftChild<<endl;
  cout<<"Q->RightChild= "<<q->RightChild<<endl;
*/
  if ((p->RightChild==0)&&(p->LeftChild==0)){  // case no children
	if (flag==1)  {delete p; root=0; return TRUE;}
	if(q->data.key > p->data.key) q->LeftChild=0;  //is p>or< than q
	   else q->RightChild=0;
  	delete p;					//delete p
        return TRUE;     		    }


  else if ((p->RightChild!=0)&&(p->LeftChild!=0)){  //case two children
        //cout<<"second"<<endl;
	BstNode <Type> *temp=p;
	BstNode <Type> *temp2=0;
        p=p->RightChild;		//using the greatest right subtree method
	   while (p->LeftChild!=0) {  temp2=p;  p=p->LeftChild;}  //moves to leftmost leaf
	   if (p->RightChild==0){      //leaf has no rightchildren
		//cout<<"second.1"<<endl;
	        if (flag==1) {
		//cout<<"p->data= "<<p->data.key<<endl;
		//cout<<"temp2->data= "<<temp2->data.key<<endl;
		//cout<<"temp->data= "<<temp->data.key<<endl;
		//cout<<"root->data= "<<root->data.key<<endl;
			if(temp2==0){		//if did not transverse the left branch
			   p->LeftChild=temp->LeftChild;
			   root=p; delete temp; return TRUE;
				    }

	   	  p->LeftChild=temp->LeftChild;	  
	   	  p->RightChild=temp->RightChild;	  
	   	  temp2->LeftChild=0;
		  root= p;
	   	  delete temp;
	   	  return TRUE;
			     }
		if (q->data.key>temp->data.key) q->LeftChild=p;
		  else q->RightChild=p;

	   p->LeftChild=temp->LeftChild;	  
	   if (temp2!=0){p->RightChild=temp->RightChild;	  
	   temp2->LeftChild=0;}
	   delete temp;
	   return TRUE;
				}
//----------------------------------------------------------------------------------
	   if (p->RightChild!=0) {    //leaf has a Rightchild
		//cout<<"second.2"<<endl;
		//cout<<"p->data= "<<p->data.key<<endl;
		//cout<<"temp2->data= "<<temp2->data.key<<endl;
		//cout<<"temp->data= "<<temp->data.key<<endl;
		//cout<<"root->data= "<<root->data.key<<endl;

		//temp2->LeftChild=p->RightChild;
	        if (flag==1) {
	   	  	if(temp2==0){
			   p->LeftChild=temp->LeftChild;
			   root=p; delete temp; return TRUE;
				    }
	   	  p->LeftChild=temp->LeftChild;	  
	   	  p->RightChild=temp->RightChild;	  
		  root= p;
	   	  delete temp; 
	   	  return TRUE;
			     }		
		if (q->data.key>temp->data.key) q->LeftChild=p;
		else q->RightChild=p;

	   if (temp2!=0) temp2->LeftChild=p->RightChild;
	   p->LeftChild=temp->LeftChild;	  
	   if (temp2!=0)  p->RightChild=temp->RightChild;	  
	   delete temp;  return TRUE;
				}
						}

  else if (p->RightChild==0){	//cout<<"third"<<endl;		   //case 1 right child
	if (flag==1) {root=p->LeftChild; delete p; return TRUE;}
	if (q->data.key > p->data.key) q->LeftChild=p->LeftChild;
	  else q->RightChild=p->LeftChild;
     delete p;  return TRUE; 		     }


  else if (p->LeftChild==0){	//cout<<"forth"<<endl;		   //case 1 left child
	if (flag==1) {root=p->RightChild; delete p; return TRUE;}
	if (q->data.key>p->data.key) q->LeftChild=p->RightChild;
	  else q->RightChild=p->RightChild;
     delete p;	return TRUE;	    }

}						   //end of delete function   
 

#ifndef no_main			// DO NOT DELETE THIS LINE
main()
{
   BST<int> m;
   Element<int> a, b, c, d, e, f, g, h, i, j, k, l, z;
   a.key = 10; b.key = 20; c.key = 5; d.key = 3; e.key = 7;
   f.key = 5; g.key = 8; h.key = 3; i.key = 6; j.key = 20; z.key = 1.5;
   cout << "\n" << m.Insert(a);
   cout << "\n" << m.Insert(b);
//   m.treeprint();
//   cout << "\n" << m.Insert(c);
//   m.treeprint();
//   cout << "\n" << m.Insert(d);
//   m.treeprint();
//    cout << "\n" << m.Insert(e);
//   m.treeprint();
//   cout << "\n" << m.Insert(f);
//   m.treeprint();
//   cout << "\n" << m.Insert(g);
//   m.treeprint();
//   cout << "\n" << m.Insert(h);
//   m.treeprint();
//   cout << "\n" << m.Insert(i);
//   m.treeprint();
//   cout << "\n" << m.Insert(j);
   m.treeprint();
   cout << "\n" << m.Delete(a)<<endl;
   m.treeprint();

  /*
   cout << "\n" << (m.Search(j) == m.IterSearch(j));
//   m.treeprint();
   cout << "\n" << (m.Search(i) == m.IterSearch(i));
//   m.treeprint();
   cout << "\n" << (m.Search(b) == m.IterSearch(b));
//   m.treeprint();
   cout << "\n" << (m.Search(a) == m.IterSearch(a));
//   m.treeprint();
   cout << "\n" << (m.Search(d) == m.IterSearch(d));
//   m.treeprint();
   cout << "\n" << (m.Search(c) == m.IterSearch(c));
//   m.treeprint();
   cout << "\n" << (m.Search(f) == m.IterSearch(f));
//   m.treeprint();
   cout << "\n" << (m.Search(e) == m.IterSearch(e));
//   m.treeprint();
   cout << "\n" << (m.Search(g) == m.IterSearch(g));
  m.treeprint();
   cout << "\n" << (m.Search(h) == m.IterSearch(h));
//   m.treeprint();
*/
}
#endif // DO NOT DELETE THIS LINE

// end of bst.cpp
