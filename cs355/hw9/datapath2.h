Define MIR Addr[5..0] | MIR[31..0];
    Rom64x32 ab Addr[5..0] ZERO MIR[31..0]
    16 16 5 0  16 17 5 0  16 16 10 0  16 17 10 0
    16 16 12 0  16 17 12 0  16 16 13 0  16 17 13 0
    144 16 0 0  144 17 0 0  0 16 1 0  8 16 1 0
    24 16 0 0  20 16 0 0  18 16 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ;
Endef;


Define SHIFTER r c l c1 c0 | o;
  Not aa c1 notc1;
  Not ba c0 notc0;
  And ab notc1 notc0 c o0;
  And bb notc1 c0 r o1;
  And cb c1 notc0 l o2;
  Or db o0 o1 o2 o;
Endef;

Define SHIFTER16 a[15..0] c[1..0] | s[15..0];
  SHIFTER aa ZERO a[15] a[14] c[1] c[0] | s[15];
  SHIFTER ba a[15] a[14] a[13] c[1] c[0] | s[14];
  SHIFTER ca a[14] a[13] a[12] c[1] c[0] | s[13];
  SHIFTER ca a[13] a[12] a[11] c[1] c[0] | s[12];
  SHIFTER ca a[12] a[11] a[10] c[1] c[0] | s[11];
  SHIFTER ca a[11] a[10] a[9] c[1] c[0] | s[10];
  SHIFTER ca a[10] a[9] a[8] c[1] c[0] | s[9];
  SHIFTER ca a[9] a[8] a[7] c[1] c[0] | s[8];
  SHIFTER ca a[8] a[7] a[6] c[1] c[0] | s[7];
  SHIFTER ca a[7] a[6] a[5] c[1] c[0] | s[6];
  SHIFTER ca a[6] a[5] a[4] c[1] c[0] | s[5];
  SHIFTER ca a[5] a[4] a[3] c[1] c[0] | s[4];
  SHIFTER ca a[4] a[3] a[2] c[1] c[0] | s[3];
  SHIFTER ca a[3] a[2] a[1] c[1] c[0] | s[2];
  SHIFTER ca a[2] a[1] a[0] c[1] c[0] | s[1];
  SHIFTER ca a[1] a[0] ZERO c[1] c[0] | s[0];
Endef;

Define BITALU a b c-in s[1..0] | z c-out;
 And 1a a b Out-And2;
 Or 1a a Out-Or;
 Not 1a a Out-Not;
 Full_Adder 1a a b c-in | c-out1 Out-Sum;
 Decoder2x4 2a s[1] s[0] | l3 l2 l1 l0;
 And 2c l1 Out-And2 Out-And1;
 And 2c l2 Out-Or Out-Or1;
 And 2c l3 Out-Not Out-Not1;
 And 2c l0 Out-Sum Out-Sum1;
 And 2c l0 c-out1  c-out;
 Or 2c  Out-And1 Out-Or1 Out-Not1 Out-Sum1 z;
Endef;

Define ALU16 a[15..0] b[15..0] c[1..0] | s[15..0] N Z;

 BITALU 00 a[0] b[0] ZERO c[1..0] | s[0] t0;
 BITALU 10 a[1] b[1] t0 c[1..0] | s[1] t1;
 BITALU 20 a[2] b[2] t1 c[1..0] | s[2] t2;
 BITALU 30 a[3] b[3] t2 c[1..0] | s[3] t3;
 BITALU 40 a[4] b[4] t3 c[1..0] | s[4] t4;
 BITALU 50 a[5] b[5] t4 c[1..0] | s[5] t5;
 BITALU 60 a[6] b[6] t5 c[1..0] | s[6] t6;
 BITALU 70 a[7] b[7] t6 c[1..0] | s[7] t7;
 BITALU 90 a[8] b[8] t7 c[1..0] | s[8] t8;
 BITALU 01 a[9] b[9] t8 c[1..0] | s[9] t9;
 BITALU 11 a[10] b[10] t9 c[1..0] | s[10] t10;
 BITALU 21 a[11] b[11] t10 c[1..0] | s[11] t11;
 BITALU 31 a[12] b[12] t11 c[1..0] | s[12] t12;
 BITALU 41 a[13] b[13] t12 c[1..0] | s[13] t13;
 BITALU 51 a[14] b[14] t13 c[1..0] | s[14] t14;
 BITALU 61 a[15] b[15] t14 c[1..0] | s[15] Cout;
 Or 71 s[15..0] Z1;
 Not 81 Z1 Z;  
 Or 91 s[15] N;
Endef;


Define REG5 | OUTR5[15..0];
    Or aa ZERO OUTR5[15];
    Or aa ZERO OUTR5[14];
    Or aa ZERO OUTR5[13];
    Or aa ZERO OUTR5[12];
    Or aa ZERO OUTR5[11];
    Or aa ZERO OUTR5[10];
    Or aa ZERO OUTR5[9];
    Or aa ZERO OUTR5[8];
    Or aa ZERO OUTR5[7];
    Or aa ZERO OUTR5[6];
    Or aa ZERO OUTR5[5];
    Or aa ZERO OUTR5[4];
    Or aa ZERO OUTR5[3];
    Or aa ZERO OUTR5[2];
    Or aa ZERO OUTR5[1];
    Or aa ZERO OUTR5[0];
Endef;

Define REG6 | OUTR6[15..0];
    Or aa ZERO OUTR6[15];
    Or aa ZERO OUTR6[14];
    Or aa ZERO OUTR6[13];
    Or aa ZERO OUTR6[12];
    Or aa ZERO OUTR6[11];
    Or aa ZERO OUTR6[10];
    Or aa ZERO OUTR6[9];
    Or aa ZERO OUTR6[8];
    Or aa ZERO OUTR6[7];
    Or aa ZERO OUTR6[6];
    Or aa ZERO OUTR6[5];
    Or aa ZERO OUTR6[4];
    Or aa ZERO OUTR6[3];
    Or aa ZERO OUTR6[2];
    Or aa ZERO OUTR6[1];
    Or aa ONE OUTR6[0];
Endef;

Define REG7 | OUTR7[15..0];
    Or aa ONE OUTR7[15];
    Or aa ONE OUTR7[14];
    Or aa ONE OUTR7[13];
    Or aa ONE OUTR7[12];
    Or aa ONE OUTR7[11];
    Or aa ONE OUTR7[10];
    Or aa ONE OUTR7[9];
    Or aa ONE OUTR7[8];
    Or aa ONE OUTR7[7];
    Or aa ONE OUTR7[6];
    Or aa ONE OUTR7[5];
    Or aa ONE OUTR7[4];
    Or aa ONE OUTR7[3];
    Or aa ONE OUTR7[2];
    Or aa ONE OUTR7[1];
    Or aa ONE OUTR7[0];
Endef;

Define REG8 | OUTR8[15..0];
    Or aa ZERO OUTR8[15];
    Or aa ZERO OUTR8[14];
    Or aa ZERO OUTR8[13];
    Or aa ZERO OUTR8[12];
    Or aa ONE OUTR8[11];
    Or aa ONE OUTR8[10];
    Or aa ONE OUTR8[9];
    Or aa ONE OUTR8[8];
    Or aa ONE OUTR8[7];
    Or aa ONE OUTR8[6];
    Or aa ONE OUTR8[5];
    Or aa ONE OUTR8[4];
    Or aa ONE OUTR8[3];
    Or aa ONE OUTR8[2];
    Or aa ONE OUTR8[1];
    Or aa ONE OUTR8[0];
Endef;

Define REG9 | OUTR9[15..0];
    Or aa ZERO OUTR9[15];
    Or aa ZERO OUTR9[14];
    Or aa ZERO OUTR9[13];
    Or aa ZERO OUTR9[12];
    Or aa ZERO OUTR9[11];
    Or aa ZERO OUTR9[10];
    Or aa ZERO OUTR9[9];
    Or aa ZERO OUTR9[8];
    Or aa ONE OUTR9[7];
    Or aa ONE OUTR9[6];
    Or aa ONE OUTR9[5];
    Or aa ONE OUTR9[4];
    Or aa ONE OUTR9[3];
    Or aa ONE OUTR9[2];
    Or aa ONE OUTR9[1];
    Or aa ONE OUTR9[0];
Endef;


Define REG10 | OUTR10[15..0];
    Or aa ZERO OUTR10[15];
    Or aa ZERO OUTR10[14];
    Or aa ZERO OUTR10[13];
    Or aa ZERO OUTR10[12];
    Or aa ZERO OUTR10[11];
    Or aa ZERO OUTR10[10];
    Or aa ZERO OUTR10[9];
    Or aa ZERO OUTR10[8];
    Or aa ZERO OUTR10[7];
    Or aa ZERO OUTR10[6];
    Or aa ZERO OUTR10[5];
    Or aa ZERO OUTR10[4];
    Or aa ZERO OUTR10[3];
    Or aa ONE OUTR10[2];
    Or aa ONE OUTR10[1];
    Or aa ONE OUTR10[0];
Endef;


Define REG11 | OUTR11[15..0];
    Or aa ZERO OUTR11[15];
    Or aa ZERO OUTR11[14];
    Or aa ZERO OUTR11[13];
    Or aa ZERO OUTR11[12];
    Or aa ZERO OUTR11[11];
    Or aa ZERO OUTR11[10];
    Or aa ZERO OUTR11[9];
    Or aa ZERO OUTR11[8];
    Or aa ZERO OUTR11[7];
    Or aa ZERO OUTR11[6];
    Or aa ZERO OUTR11[5];
    Or aa ZERO OUTR11[4];
    Or aa ONE OUTR11[3];
    Or aa ZERO OUTR11[2];
    Or aa ZERO OUTR11[1];
    Or aa ZERO OUTR11[0];
Endef;


Define REG12 | OUTR12[15..0];
    Or aa ZERO OUTR12[15];
    Or aa ZERO OUTR12[14];
    Or aa ZERO OUTR12[13];
    Or aa ZERO OUTR12[12];
    Or aa ZERO OUTR12[11];
    Or aa ZERO OUTR12[10];
    Or aa ZERO OUTR12[9];
    Or aa ZERO OUTR12[8];
    Or aa ZERO OUTR12[7];
    Or aa ZERO OUTR12[6];
    Or aa ZERO OUTR12[5];
    Or aa ZERO OUTR12[4];
    Or aa ONE OUTR12[3];
    Or aa ZERO OUTR12[2];
    Or aa ZERO OUTR12[1];
    Or aa ONE OUTR12[0];
Endef;

Define REG13 | OUTR13[15..0];
    Or aa ONE OUTR13[15];
    Or aa ZERO OUTR13[14];
    Or aa ONE OUTR13[13];
    Or aa ZERO OUTR13[12];
    Or aa ONE OUTR13[11];
    Or aa ZERO OUTR13[10];
    Or aa ONE OUTR13[9];
    Or aa ZERO OUTR13[8];
    Or aa ONE OUTR13[7];
    Or aa ZERO OUTR13[6];
    Or aa ONE OUTR13[5];
    Or aa ZERO OUTR13[4];
    Or aa ONE OUTR13[3];
    Or aa ZERO OUTR13[2];
    Or aa ONE OUTR13[1];
    Or aa ZERO OUTR13[0];
Endef;

Define REG14 | OUTR14[15..0];
    Or aa ONE OUTR14[15];
    Or aa ONE OUTR14[14];
    Or aa ONE OUTR14[13];
    Or aa ONE OUTR14[12];
    Or aa ONE OUTR14[11];
    Or aa ONE OUTR14[10];
    Or aa ONE OUTR14[9];
    Or aa ONE OUTR14[8];
    Or aa ONE OUTR14[7];
    Or aa ONE OUTR14[6];
    Or aa ONE OUTR14[5];
    Or aa ONE OUTR14[4];
    Or aa ONE OUTR14[3];
    Or aa ONE OUTR14[2];
    Or aa ONE OUTR14[1];
    Or aa ONE OUTR14[0];
Endef;

Define REG15 | OUTR15[15..0];
    Or aa ONE OUTR15[15];
    Or aa ONE OUTR15[14];
    Or aa ONE OUTR15[13];
    Or aa ONE OUTR15[12];
    Or aa ZERO OUTR15[11];
    Or aa ZERO OUTR15[10];
    Or aa ZERO OUTR15[9];
    Or aa ZERO OUTR15[8];
    Or aa ONE OUTR15[7];
    Or aa ONE OUTR15[6];
    Or aa ONE OUTR15[5];
    Or aa ONE OUTR15[4];
    Or aa ZERO OUTR15[3];
    Or aa ZERO OUTR15[2];
    Or aa ZERO OUTR15[1];
    Or aa ZERO OUTR15[0];
Endef;

Define Register0 INREG0[15..0] t r | OUTREG[15..0] Q[15..0];

  Dff aa ONE INREG0[0] t r OUTREG[0] Q[0];
  Dff aa ONE INREG0[1] t r OUTREG[1] Q[1];
  Dff aa ONE INREG0[2] t r OUTREG[2] Q[2];
  Dff aa ONE INREG0[3] t r OUTREG[3] Q[3];
  Dff aa ONE INREG0[4] t r OUTREG[4] Q[4];
  Dff aa ONE INREG0[5] t r OUTREG[5] Q[5];
  Dff aa ONE INREG0[6] t r OUTREG[6] Q[6];
  Dff aa ONE INREG0[7] t r OUTREG[7] Q[7];
  Dff aa ONE INREG0[8] t r OUTREG[8] Q[8];
  Dff aa ONE INREG0[9] t r OUTREG[9] Q[9];
  Dff aa ONE INREG0[10] t r OUTREG[10] Q[10];
  Dff aa ONE INREG0[11] t r OUTREG[11] Q[11];
  Dff aa ONE INREG0[12] t r OUTREG[12] Q[12];
  Dff aa ONE INREG0[13] t r OUTREG[13] Q[13];
  Dff aa ONE INREG0[14] t r OUTREG[14] Q[14];
  Dff aa ONE INREG0[15] t r OUTREG[15] Q[15];
Endef;


Define DataPath MIR[31..0] MBR[15..0] Phase[3..0] Reset | R0[15..0] R1[15..0] R2[15..0] R3[15..0] R4[15..0] R5[15..0] R6[15..0] R7[15..0] R8[15..0] R9[15..0] R10[15..0] R11[15..0] R12[15..0] R13[15..0] R14[15..0] R15[15..0] A[15..0] B[15..0] AMUX[15..0] C[15..0] N Z;

  And aa Phase[3] MIR[20] ENC;

  Not aa ENC notENC;

  Dec4x16 aa MIR[19..16] notENC D[15..0];

  Not aa Reset not-Reset;
  Not aa D[0] not-D0;

  Register0 aa C[15..0] not-D0 not-Reset | R0[15..0] Qx[15..0];

  Register aa C[15..0] D[1] | R1[15..0];
  Register aa C[15..0] D[2] | R2[15..0];
  Register aa C[15..0] D[3] | R3[15..0];
  Register aa C[15..0] D[4] | R4[15..0];

  REG5 aa | R5[15..0];
  REG6 aa | R6[15..0];
  REG7 aa | R7[15..0];
  REG8 aa | R8[15..0];
  REG9 aa | R9[15..0];
  REG10 aa | R10[15..0];
  REG11 aa | R11[15..0];
  REG12 aa | R12[15..0];
  REG13 aa | R13[15..0];
  REG14 aa | R14[15..0];
  REG15 aa | R15[15..0];

  Mux-mxn aa R15[15..0] R14[15..0] R13[15..0] R12[15..0] R11[15..0] R10[15..0] R9[15..0] R8[15..0] R7[15..0] R6[15..0] R5[15..0] R4[15..0] R3[15..0] R2[15..0]  R1[15..0] R0[15..0] MIR[11..8] | BUSAMUX[15..0];

  Mux-mxn aa R15[15..0] R14[15..0] R13[15..0] R12[15..0] R11[15..0] R10[15..0] R9[15..0] R8[15..0] R7[15..0] R6[15..0] R5[15..0] R4[15..0] R3[15..0] R2[15..0] R1[15..0] R0[15..0] MIR[15..12] | BUSBMUX[15..0];

  Not aa Phase[1] notPhase1; 
  Register aa BUSAMUX[15..0] notPhase1 | A[15..0];
  Register aa BUSBMUX[15..0] notPhase1 | B[15..0];
  Mux-mxn aa MBR[15..0] A[15..0] MIR[31] | AMUX[15..0];
  ALU16 aa AMUX[15..0] B[15..0] MIR[28..27] | ALUOUT[15..0] N Z;
  SHIFTER16 aa ALUOUT[15..0] MIR[26..25] | C[15..0];
  
Endef;

