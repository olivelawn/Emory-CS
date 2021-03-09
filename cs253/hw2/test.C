// A simple version of tokens and expressions,
// as used by program 3.19.

// You should not use this code, since in fact you are
// supposed to read your input from the "standard input"
// rather than a string.  That is, you should use
// something like "y=cin.get()" in your homework.

#include <iostream.h>

typedef char token;
typedef token *expression;
token NextToken(expression &e) { return *e++; }

main() {
  expression e = "Hello world.\n#";
  token y;
  while ((y = NextToken(e)) != '#') cout << y;
}
