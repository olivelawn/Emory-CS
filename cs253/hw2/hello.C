// tokens and expressions
#include <iostream.h>

typedef char token;
typedef token *expression;
inline token NextToken(expression &e) { return *e++; }

main() {
  expression e = "Hello world.\n#";
  token y;
  while ((y = NextToken(e)) != '#') cout << y;
}
