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

/* D-latch
   Syntax: D_Latch D Clock | Q-bar Q;
*/
Define D_Latch D Clk | q-bar q;
 And 1d D Clk set;  Nor 1e set q q-bar;
 Not 2c D Not-D;    And 2d Clk Not-D reset; Nor 2e q-bar reset q;
Endef;
 
/* D-flipflop
   Syntax: D_Flipflop <x,y> D Clock | Q-bar Q;
*/
Define D_Flipflop D Clk | q-bar q;
 And 1d D Clk set1;  Nor 1e set1 q1 q1-bar;
 And 2d Clk Not-D reset1; Nor 2e q1-bar reset1 q1;
 Not 2c D Not-D;
 And 1f q1-bar Not-Clk set2;  Nor 1g set2 q q-bar;
 And 2f Not-Clk q1 reset2; Nor 2g q-bar reset2 q;
 Not 2f Clk Not-Clk;
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




/* 1 bit ALU
   Syntax: One_Bit_ALU a b carry-in sel1 sel0 | z carry-out;

   sel1 = 0, sel0 = 0 -> Add a, b carry-in
   sel1 = 0, sel0 = 1 -> a AND b
   sel1 = 1, sel0 = 0 -> a
   sel1 = 1, sel0 = 1 -> Not a
*/

Define One_Bit_ALU a b c-in s[1..0] | z c-out;
 And 1a a b Out-And2;
 Not 1a a Out-Not;
 Full_Adder 1a a b c-in | c-out1 Out-Sum;
 Decoder2x4 2a s[1] s[0] | l3 l2 l1 l0;
 And 2c l3 Out-Not Out-Not1;
 And 2c l2 a Out-a;
 And 2c l1 Out-And2 Out-And1;
 And 2c l0 Out-Sum Out-Sum1;
 And 2c l0 c-out1 c-out;

 Or 2c  Out-Not1 Out-a Out-And1 Out-Sum1 z;
Endef;


Define ALU16 a[15..0] b[15..0] s[1] s[0] | z[15..0] N Z;
        One_Bit_ALU aa a[0] b[0] ZERO s[1] s[0] | z[0] out0;
        One_Bit_ALU ab a[1] b[1] out0 s[1] s[0] | z[1] out1;
        One_Bit_ALU ac a[2] b[2] out1 s[1] s[0] | z[2] out2;
        One_Bit_ALU ad a[3] b[3] out2 s[1] s[0] | z[3] out3;
        One_Bit_ALU ae a[4] b[4] out3 s[1] s[0] | z[4] out4;
        One_Bit_ALU af a[5] b[5] out4 s[1] s[0] | z[5] out5;
        One_Bit_ALU ag a[6] b[6] out5 s[1] s[0] | z[6] out6;
        One_Bit_ALU ah a[7] b[7] out6 s[1] s[0] | z[7] out7;
        One_Bit_ALU ai a[8] b[8] out7 s[1] s[0] | z[8] out8;
        One_Bit_ALU aj a[9] b[9] out8 s[1] s[0] | z[9] out9;
        One_Bit_ALU ak a[10] b[10] out9 s[1] s[0] | z[10] out10;
        One_Bit_ALU al a[11] b[11] out10 s[1] s[0] | z[11] out11;
        One_Bit_ALU am a[12] b[12] out11 s[1] s[0] | z[12] out12;
        One_Bit_ALU an a[13] b[13] out12 s[1] s[0] | z[13] out13;
        One_Bit_ALU ao a[14] b[14] out13 s[1] s[0] | z[14] out14;
        One_Bit_ALU ap a[15] b[15] out14 s[1] s[0] | z[15] out15;
	
	And da z[15] ONE N;
        Nor da z[0] z[1] z[2] z[3] z[4] z[5] z[6] z[7] z[8] z[9] z[10] z[11] z[12] z[13] z[14] z[15] Z;
Endef;

 


