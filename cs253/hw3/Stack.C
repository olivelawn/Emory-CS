/*	Parker Johnson
	2/7/96
	Stack.C
*/

const int DefaultSize = 10;
enum Boolean {FALSE, TRUE};

template <class KeyType>
class Stack
{
// objects: A finite ordered list with zero or more elements.
public:
    Stack(int MaxStackSize = DefaultSize);
    // Create an empty stack whose maximum size is MaxStackSize

    Boolean IsFull();
    // if number of elements in the stack is equal to the maximum size of
    //   the stack, return TRUE (1); otherwise, return FALSE (0)

    void Add (const KeyType& item);
    // if IsFull(), then StackFull(); else insert item into the top of the stack.

    Boolean IsEmpty();
    // if number of elements in the stack is equal to 0, return TRUE (1) else return FALSE (0).

    KeyType* Delete(KeyType&);
    // if IsEmpty(), then StackEmpty(); else remove and return the topmost element of the stack

    // Implement these two functions as you see fit. -- Mic
    void StackEmpty() {cerr << "empty" << endl;  exit(1);}
    void StackFull()  {cerr << "full" << endl;  exit(1);}
    void Output();
    void print();
private:
    int top;
    KeyType *stack;
    int MaxSize;
};

template <class KeyType>
Stack<KeyType>::Stack (int MaxStackSize) : MaxSize (MaxStackSize)
{
    stack = new KeyType[MaxSize];
    top = -1;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsFull()
{
    if (top == MaxSize -1) return TRUE;
    else return FALSE;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsEmpty()
{
    if (top == -1) return TRUE;
    else return FALSE;
}

template <class KeyType>
void Stack<KeyType>::Add (const KeyType& x)
// add x to the stack
{
    if (IsFull()) StackFull();
    else stack[++top] = x;
}

template <class KeyType>
KeyType* Stack<KeyType>::Delete (KeyType& x)
// remove and return top element from stack
{
    if (IsEmpty()) {StackEmpty(); return 0;}
    x = stack[top--];
    return &x;
}

template <class KeyType>
void Stack<KeyType>::Output()
{
  cout << "top = " << top << endl;
  for (int i = 0; i <= top; i++)
      cout << i << ":" << stack[i] << endl;
}

template <class KeyType>
void Stack<KeyType>::print()
{
     cout<<"top= "<<top<<endl;
  for (int i=0; i<=top; i++){
     cout<<stack[i]<<" ";}
cout<<endl;   
}
