/* -----------------------------------------------------------
   Basic circuits made available for the CS355 class project
   ----------------------------------------------------------- */

/* Full adder.
   Syntax: Full_Adder a b c-in | c-out s;
   Effect: Adds binary numbers a + b with carry.
*/
Define Full_Adder CarryIn a b | CarryOut Sum;
  Xor aa a b x;
  Xor ab x CarryIn Sum;
  And bb a b y;
  And cb CarryIn x z;
  Or bc-cc y z CarryOut;
Endef;

/* 2x4 Decoder
   Syntax: Decoder2x4 <x,y> c[1..0] | s[3..0];
*/
Define Decoder2x4 c[1..0] | s[3..0];
 Not 1a c[1] not-c1; Not 2a c[0] not-c0;
 And 2a c[1] c[0] s[3];
 And 2b c[1] not-c0 s[2];
 And 2c not-c1 c[0] s[1];
 And 2d not-c1 not-c0 s[0];
Endef;
