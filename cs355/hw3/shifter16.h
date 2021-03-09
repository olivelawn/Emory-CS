
Define Decoder2x4 c[1..0] | s[3..0];
 Not 1a c[1] not-c1; Not 2a c[0] not-c0;
 And 2a c[1] c[0] s[3];
 And 2b c[1] not-c0 s[2];
 And 2c not-c1 c[0] s[1];
 And 2d not-c1 not-c0 s[0];
Endef;


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


  

