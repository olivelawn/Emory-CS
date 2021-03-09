
/* ---------------  START OF SHIFTER -------------- */

Define Bit-shifter l c r c1 c0 | z;
 
Decoder2x4 bd c1 c0 | s3 s2 s1 s0;
 
And ae s2 r right;
And be s1 l center;
And ce s0 c left;
 
Or bg right center left z;
 
Endef;
 
 
Define SHIFTER16 a[15..0] c1 c0 | s[15..0] ;
 
  Bit-shifter aa ZERO  a[15] a[14] c1 c0 | s[15];
  Bit-shifter ab a[15] a[14] a[13] c1 c0 | s[14];
  Bit-shifter ac a[14] a[13] a[12] c1 c0 | s[13];
  Bit-shifter ad a[13] a[12] a[11] c1 c0 | s[12];
  Bit-shifter ae a[12] a[11] a[10] c1 c0 | s[11];
  Bit-shifter af a[11] a[10] a[9]  c1 c0 | s[10];
  Bit-shifter ag a[10] a[9]  a[8]  c1 c0 | s[9];
  Bit-shifter ah a[9]  a[8]  a[7]  c1 c0 | s[8];
  Bit-shifter ai a[8]  a[7]  a[6]  c1 c0 | s[7];
  Bit-shifter aj a[7]  a[6]  a[5]  c1 c0 | s[6];
  Bit-shifter ak a[6]  a[5]  a[4]  c1 c0 | s[5];
  Bit-shifter al a[5]  a[4]  a[3]  c1 c0 | s[4];
  Bit-shifter am a[4]  a[3]  a[2]  c1 c0 | s[3];
  Bit-shifter an a[3]  a[2]  a[1]  c1 c0 | s[2];
  Bit-shifter ao a[2]  a[1]  a[0]  c1 c0 | s[1];
  Bit-shifter ap a[1]  a[0]  ZERO  c1 c0 | s[0];
 
Endef;

/* -------------- END OF SHIFTER ------------------- */
/* -------------- START OF ALU --------------------- */
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
/* ------------------ END OF ALU --------------- */


Define R0 i[15..0] TICK RESET | o[15..0] nq[15..0];
   Dff aa ONE i[0] TICK RESET o[0] nq[0];
   Dff aa ONE i[1] TICK RESET o[1] nq[1];
   Dff aa ONE i[2] TICK RESET o[2] nq[2];
   Dff aa ONE i[3] TICK RESET o[3] nq[3];
   Dff aa ONE i[4] TICK RESET o[4] nq[4];
   Dff aa ONE i[5] TICK RESET o[5] nq[5];
   Dff aa ONE i[6] TICK RESET o[6] nq[6];
   Dff aa ONE i[7] TICK RESET o[7] nq[7];
   Dff aa ONE i[8] TICK RESET o[8] nq[8];
   Dff aa ONE i[9] TICK RESET o[9] nq[9];
   Dff aa ONE i[10] TICK RESET o[10] nq[10];
   Dff aa ONE i[11] TICK RESET o[11] nq[11];
   Dff aa ONE i[12] TICK RESET o[12] nq[12];
   Dff aa ONE i[13] TICK RESET o[13] nq[13];
   Dff aa ONE i[14] TICK RESET o[14] nq[14];
   Dff aa ONE i[15] TICK RESET o[15] nq[15];
Endef;
    
Define R1 i[15..0] TICK RESET | o[15..0] nq[15..0];
   Dff aa ONE i[0] TICK RESET o[0] nq[0];
   Dff aa ONE i[1] TICK RESET o[1] nq[1];
   Dff aa ONE i[2] TICK RESET o[2] nq[2];  
   Dff aa ONE i[3] TICK RESET o[3] nq[3];
   Dff aa ONE i[4] TICK RESET o[4] nq[4];
   Dff aa ONE i[5] TICK RESET o[5] nq[5];
   Dff aa ONE i[6] TICK RESET o[6] nq[6];
   Dff aa ONE i[7] TICK RESET o[7] nq[7];
   Dff aa ONE i[8] TICK RESET o[8] nq[8];
   Dff aa ONE i[9] TICK RESET o[9] nq[9];
   Dff aa ONE i[10] TICK RESET o[10] nq[10];
   Dff aa ONE i[11] TICK RESET o[11] nq[11];
   Dff aa ONE i[12] TICK RESET o[12] nq[12];
   Dff aa ONE i[13] TICK RESET o[13] nq[13];
   Dff aa ONE i[14] TICK RESET o[14] nq[14];
   Dff aa ONE i[15] TICK RESET o[15] nq[15];
Endef;

Define R2 i[15..0] TICK RESET | o[15..0] nq[15..0];
   Dff aa ONE i[0] TICK RESET o[0] nq[0];
   Dff aa ONE i[1] TICK RESET o[1] nq[1];
   Dff aa ONE i[2] TICK RESET o[2] nq[2];
   Dff aa ONE i[3] TICK RESET o[3] nq[3];
   Dff aa ONE i[4] TICK RESET o[4] nq[4];
   Dff aa ONE i[5] TICK RESET o[5] nq[5];
   Dff aa ONE i[6] TICK RESET o[6] nq[6];
   Dff aa ONE i[7] TICK RESET o[7] nq[7];
   Dff aa ONE i[8] TICK RESET o[8] nq[8];
   Dff aa ONE i[9] TICK RESET o[9] nq[9];
   Dff aa ONE i[10] TICK RESET o[10] nq[10];
   Dff aa ONE i[11] TICK RESET o[11] nq[11];
   Dff aa ONE i[12] TICK RESET o[12] nq[12];
   Dff aa ONE i[13] TICK RESET o[13] nq[13];
   Dff aa ONE i[14] TICK RESET o[14] nq[14];
   Dff aa ONE i[15] TICK RESET o[15] nq[15];
Endef;

Define R3 i[15..0] TICK RESET | o[15..0] nq[15..0];
   Dff aa ONE i[0] TICK RESET o[0] nq[0];
   Dff aa ONE i[1] TICK RESET o[1] nq[1];
   Dff aa ONE i[2] TICK RESET o[2] nq[2];
   Dff aa ONE i[3] TICK RESET o[3] nq[3];   
   Dff aa ONE i[4] TICK RESET o[4] nq[4];   
   Dff aa ONE i[5] TICK RESET o[5] nq[5];   
   Dff aa ONE i[6] TICK RESET o[6] nq[6];
   Dff aa ONE i[7] TICK RESET o[7] nq[7];
   Dff aa ONE i[8] TICK RESET o[8] nq[8];
   Dff aa ONE i[9] TICK RESET o[9] nq[9];
   Dff aa ONE i[10] TICK RESET o[10] nq[10];
   Dff aa ONE i[11] TICK RESET o[11] nq[11];
   Dff aa ONE i[12] TICK RESET o[12] nq[12];
   Dff aa ONE i[13] TICK RESET o[13] nq[13];
   Dff aa ONE i[14] TICK RESET o[14] nq[14];
   Dff aa ONE i[15] TICK RESET o[15] nq[15];
Endef;

Define R4 i[15..0] TICK RESET | o[15..0] nq[15..0];
   Dff aa ONE i[0] TICK RESET o[0] nq[0];
   Dff aa ONE i[1] TICK RESET o[1] nq[1];
   Dff aa ONE i[2] TICK RESET o[2] nq[2];
   Dff aa ONE i[3] TICK RESET o[3] nq[3];   
   Dff aa ONE i[4] TICK RESET o[4] nq[4];   
   Dff aa ONE i[5] TICK RESET o[5] nq[5];   
   Dff aa ONE i[6] TICK RESET o[6] nq[6];   
   Dff aa ONE i[7] TICK RESET o[7] nq[7];   
   Dff aa ONE i[8] TICK RESET o[8] nq[8];   
   Dff aa ONE i[9] TICK RESET o[9] nq[9];
   Dff aa ONE i[10] TICK RESET o[10] nq[10];
   Dff aa ONE i[11] TICK RESET o[11] nq[11];
   Dff aa ONE i[12] TICK RESET o[12] nq[12];
   Dff aa ONE i[13] TICK RESET o[13] nq[13];
   Dff aa ONE i[14] TICK RESET o[14] nq[14];
   Dff aa ONE i[15] TICK RESET o[15] nq[15];
Endef;



Define R5 | D[15-0];
   Or aa ZERO D[15]; Or aa ZERO D[14]; Or aa ZERO D[13];
   Or aa ZERO D[12]; Or aa ZERO D[11]; Or aa ZERO D[10];
   Or aa ZERO D[9];  Or aa ZERO D[8];  Or aa ZERO D[7];
   Or aa ZERO D[6];  Or aa ZERO D[5];  Or aa ZERO D[4];
   Or aa ZERO D[3];  Or aa ZERO D[2];  Or aa ZERO D[1];
   Or aa ZERO D[0];
Endef;

Define R6 | D[15-0];
   Or aa ZERO D[15]; Or aa ZERO D[14]; Or aa ZERO D[13];
   Or aa ZERO D[12]; Or aa ZERO D[11]; Or aa ZERO D[10];
   Or aa ZERO D[9];  Or aa ZERO D[8];  Or aa ZERO D[7];
   Or aa ZERO D[6];  Or aa ZERO D[5];  Or aa ZERO D[4];
   Or aa ZERO D[3];  Or aa ZERO D[2];  Or aa ZERO D[1];
   Or aa ONE D[0];
Endef;

Define R7 | D[15-0];
   Or aa ONE  D[15]; Or aa ONE  D[14]; Or aa ONE  D[13];
   Or aa ONE  D[12]; Or aa ONE  D[11]; Or aa ONE  D[10];
   Or aa ONE  D[9];  Or aa ONE  D[8];  Or aa ONE  D[7];
   Or aa ONE  D[6];  Or aa ONE  D[5];  Or aa ONE  D[4];
   Or aa ONE  D[3];  Or aa ONE  D[2];  Or aa ONE  D[1];
   Or aa ONE D[0];
Endef;

Define R8 | D[15-0];
   Or aa ZERO  D[15]; Or aa ZERO  D[14]; Or aa ZERO  D[13];
   Or aa ZERO  D[12]; Or aa ONE  D[11]; Or aa ONE  D[10];
   Or aa ONE  D[9];  Or aa ONE  D[8];  Or aa ONE  D[7];
   Or aa ONE  D[6];  Or aa ONE  D[5];  Or aa ONE  D[4];
   Or aa ONE  D[3];  Or aa ONE  D[2];  Or aa ONE  D[1];
   Or aa ONE D[0];
Endef;
 
Define R9 | D[15-0];
   Or aa ZERO  D[15]; Or aa ZERO  D[14]; Or aa ZERO  D[13];
   Or aa ZERO  D[12]; Or aa ZERO  D[11]; Or aa ZERO  D[10];
   Or aa ZERO  D[9];  Or aa ZERO  D[8];  Or aa ONE  D[7];
   Or aa ONE  D[6];  Or aa ONE  D[5];  Or aa ONE  D[4];
   Or aa ONE  D[3];  Or aa ONE  D[2];  Or aa ONE  D[1];
   Or aa ONE D[0];
Endef;
 
Define R10 | D[15-0];
   Or aa ZERO  D[15]; Or aa ZERO  D[14]; Or aa ZERO  D[13];
   Or aa ZERO  D[12]; Or aa ZERO  D[11]; Or aa ZERO  D[10];
   Or aa ZERO  D[9];  Or aa ZERO  D[8];  Or aa ZERO  D[7];
   Or aa ZERO  D[6];  Or aa ZERO  D[5];  Or aa ZERO  D[4];
   Or aa ZERO  D[3];  Or aa ONE  D[2];  Or aa ONE  D[1];
   Or aa ONE D[0];
Endef;
 
Define R11 | D[15-0];
   Or aa ZERO  D[15]; Or aa ZERO  D[14]; Or aa ZERO  D[13];
   Or aa ZERO  D[12]; Or aa ZERO  D[11]; Or aa ZERO  D[10];
   Or aa ZERO  D[9];  Or aa ZERO  D[8];  Or aa ZERO  D[7];
   Or aa ZERO  D[6];  Or aa ZERO  D[5];  Or aa ZERO  D[4];
   Or aa ONE  D[3];  Or aa ZERO  D[2];  Or aa ZERO  D[1];
   Or aa ZERO D[0];
Endef;
 
Define R12 | D[15-0];
   Or aa ZERO  D[15]; Or aa ZERO  D[14]; Or aa ZERO  D[13];
   Or aa ZERO  D[12]; Or aa ZERO  D[11]; Or aa ZERO  D[10];
   Or aa ZERO  D[9];  Or aa ZERO  D[8];  Or aa ZERO  D[7];
   Or aa ZERO  D[6];  Or aa ZERO  D[5];  Or aa ZERO  D[4];
   Or aa ONE  D[3];  Or aa ZERO  D[2];  Or aa ZERO  D[1];
   Or aa ONE D[0];
Endef;
 
Define R13 | D[15-0];
   Or aa ONE D[15]; Or aa ZERO D[14]; Or aa ONE D[13];
   Or aa ZERO D[12]; Or aa ONE D[11]; Or aa ZERO D[10];
   Or aa ONE D[9];  Or aa ZERO D[8];  Or aa ONE D[7];
   Or aa ZERO D[6];  Or aa ONE D[5];  Or aa ZERO D[4];
   Or aa ONE D[3];  Or aa ZERO D[2];  Or aa ONE D[1];
   Or aa ZERO D[0];
Endef;

Define R14 | D[15-0];
   Or aa ONE  D[15]; Or aa ONE  D[14]; Or aa ONE  D[13];
   Or aa ONE  D[12]; Or aa ONE  D[11]; Or aa ONE  D[10];
   Or aa ONE  D[9];  Or aa ONE  D[8];  Or aa ONE  D[7];
   Or aa ONE  D[6];  Or aa ONE  D[5];  Or aa ONE  D[4];
   Or aa ONE  D[3];  Or aa ONE  D[2];  Or aa ONE  D[1];
   Or aa ONE D[0];
Endef;

Define R15 | D[15-0];
   Or aa ONE  D[15]; Or aa ONE  D[14]; Or aa ONE  D[13];
   Or aa ONE  D[12]; Or aa ZERO  D[11]; Or aa ZERO  D[10];
   Or aa ZERO  D[9];  Or aa ZERO  D[8];  Or aa ONE  D[7];
   Or aa ONE  D[6];  Or aa ONE  D[5];  Or aa ONE  D[4];
   Or aa ZERO  D[3];  Or aa ZERO  D[2];  Or aa ZERO  D[1];
   Or aa ZERO D[0];
Endef;

Define MIR Addr[5..0] | MIR[31..0];
Rom64x32 ab-bb Addr[5] Addr[4] Addr[3] Addr[2] Addr[1] Addr[0] ZERO MIR[31..0]

    16 16 5 0   16 17 5 0     16 16 10 0   16 17 10 0  16 16 12 0  
    16 17 12 0  16 16 13 0    16 17 13 0   144 16 0 0  144 17 0 0  
    0 16 1 0    8 16 1 0      24 16 0 0    20 16 0 0   18 16 0 0    
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  ;
Endef;



Define DataPath MIR[31..0] mbr [15..0] Phase[3..0] Reset |
	R0[15..0] R1[15..0] R2[15..0] R3[15..0] R4[15..0] R5[15..0]
	R6[15..0] R7[15..0] R8[15..0] R9[15..0] R10[15..0] R11[15..0]
	R12[15..0] R13[15..0] R14[15..0] R15[15..0] 
	A[15..0] B[15..0] AMUX[15..0] C[15..0] N Z ;

And aa Phase[3] MIR[20] ENC;
Not aa ENC notENC;

Dec4x16 "4x16" aa MIR[19] MIR[18] MIR[17] MIR[16] notENC O[15..0];

Not ab Reset notReset;
Not ab O[0] notO0;
Not ab O[1] notO1;
Not ab O[2] notO2;
Not ab O[3] notO3;
Not ab O[4] notO4;

R0       "R0" ac C[15..0] notO0 notReset | R0[15..0];
R1       "R1" ac C[15..0] notO1 notReset | R1[15..0];
R2       "R2" ac C[15..0] notO2 notReset | R2[15..0];
R3       "R3" ac C[15..0] notO3 notReset | R3[15..0];
R4       "R4" ac C[15..0] notO4 notReset | R4[15..0];
/* Register "R1" ac C[15..0] O[1] | R1[15..0];
   Register "R2" ac C[15..0] O[2] | R2[15..0];
   Register "R3" ac C[15..0] O[3] | R3[15..0];
   Register "R4" ac C[15..0] O[4] | R4[15..0];  */
R5       "R5"  ac | R5[15..0];
R6       "R6"  ac | R6[15..0];
R7       "R7"  ac | R7[15..0];
R8       "R8"  ac | R8[15..0];
R9       "R9"  ac | R9[15..0];
R10      "R10" ac | R10[15..0];
R11      "R11" ac | R11[15..0];
R12      "R12" ac | R12[15..0];
R13      "R13" ac | R13[15..0];
R14      "R14" ac | R14[15..0];
R15      "R15" ac | R15[15..0];


Mux-mxn "a-mul" dc R15[15..0] R14[15..0] R13[15..0] R12[15..0] R11[15..0]
	   R10[15..0]
	   R9[15..0] R8[15..0] R7[15..0] R6[15..0] R5[15..0] R4[15..0]
	   R3[15..0] R2[15..0] R1[15..0] R0[15..0]     MIR[11..8] |
	   aout[15..0];

Mux-mxn "b-mul" dd R15[15..0] R14[15..0] R13[15..0] R12[15..0] R11[15..0]
	   R10[15..0]
	   R9[15..0] R8[15..0] R7[15..0] R6[15..0] R5[15..0] R4[15..0]
	   R3[15..0] R2[15..0] R1[15..0] R0[15..0]     MIR[15..12] |
	   bout[15..0];

Not ec Phase[1] notPhase[1];

Register "a-latch" ec aout[15..0] notPhase[1] | A[15..0]; 
Register "b-latch" ee bout[15..0] notPhase[1] | B[15..0]; 

/* Or ee B[15..0] MAR[15..0]; */

Mux-mxn "A-MUX" fc mbr[15..0] A[15..0] MIR[31] | AMUX[15..0];

ALU16 "ALU" gd AMUX[15..0] B[15..0] MIR[28] MIR[27] | ALUOUT[15..0] N Z;

SHIFTER16 "SHIFTER" ge ALUOUT[15..0] MIR[26] MIR[25] | C[15..0];

Endef;

