/* ----
   The following ROM contains the micro program from Tanenbaum Fig 4-20
   on page 200 - 201
   ---- */
Define MIC2 a[7..0] | d[31..0];
   Rom128x32 aa a[6..0] ZERO d[31..0]
	/* 1 */ 16 192 0 0 1 80 96 0 176 19 0 28 36 20 51 19 52 20 4 11
	/* 2 */ 48 0 4 9 16 192 48 0 1 64 0 0 240 17 0 0 17 160 49 0
	/* 3 */ 112 32 0 0 48 0 4 15 16 192 48 0 16 64 0 0 224 17 16 0
	/* 4 */ 16 192 48 0 0 81 97 0 152 26 0 0 96 17 161 0 52 20 4 25
	/* 5 */ 48 0 4 23 48 0 1 27 104 16 131 0 80 0 1 22 112 0 0 0
	/* 6 */ 48 0 4 27 104 16 131 0 104 17 131 0 36 20 51 40 52 20 4 35
	/* 7 */ 48 0 4 33 0 26 35 0 112 192 160 7 0 26 35 0 113 160 161 10
	/* 8 */ 48 0 4 38 0 26 35 0 112 192 160 13 0 26 35 0 112 192 160 16
	/* 9 */ 52 20 4 46 48 0 4 44 48 0 1 22 112 0 0 0 80 0 1 0
	/*10 */ 104 16 131 0 52 20 4 50 0 18 114 0 17 160 32 0 104 48 131 0
	/*11 */ 52 20 4 65 52 20 4 59 48 0 4 56 16 192 16 0 0 82 114 0
	/*12 */ 112 160 32 10 0 210 98 0 16 64 0 0 112 160 16 10 48 0 4 62
	/*13 */ 0 18 114 0 113 160 33 10 0 210 98 0 16 64 0 0 240 17 0 0
	/*14 */ 52 20 4 73 48 0 4 70 0 210 98 0 16 64 0 0 240 16 0 0
	/*15 */ 16 26 1 0 16 17 2 0 112 18 10 0 48 0 4 76 8 26 147 0
	/*16 */ 96 18 162 0 8 26 147 0 24 26 10 0 96 26 106 75 0 0 0 0
	/*17 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*18 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*19 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*20 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*21 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*22 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*23 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*24 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*25 */ 0 0 0 0    0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0
	/*26 */ 0 0 0 0    0 0 0 0   0 0 0 0   ;
Endef;


/*
MIC2 aa ZERO ZERO ZERO ZERO ZERO ZERO ZERO ZERO | d[31..0];
Probe ab d[31]; Probe ab d[30]; Probe ab d[29]; Probe ab d[28]; Probe ab d[27];
Probe ab d[26]; Probe ab d[25]; Probe ab d[24]; Probe ab d[23]; Probe ab d[22];
Probe ab d[21]; Probe ab d[20]; Probe ab d[19]; Probe ab d[18]; Probe ab d[17];
Probe ab d[16]; Probe ab d[15]; Probe ab d[14]; Probe ab d[13]; Probe ab d[12];
Probe ab d[11]; Probe ab d[10]; Probe ab d[9]; Probe ab d[8]; Probe ab d[7];
Probe ab d[6]; Probe ab d[5]; Probe ab d[4]; Probe ab d[3]; Probe ab d[2];
Probe ab d[1]; Probe ab d[0];
*/


Define MSL n z c1 c0 | MSLOUT;
Not aa n nn;
Not aa z nz;
Not aa c1 nc1;
Not aa c0 nc0;

And aa nc1 c0 n nz 01;
And aa nc1 c0 n z 02;
And aa c1 nc0 nn z 03;
And aa c1 nc0 n z 04;
And aa c1 c0 nn nz 05;
And aa c1 c0 nn z 06;
And aa c1 c0 n nz 07;
And aa c1 c0 n z 08;
Or aa 01 02 03 04 05 06 07 08 MSLOUT;
Endef;

Define MPC i[7..0] TICK RESET | o[7..0];
   Dff aa ONE i[0] TICK RESET o[0] nq[0];
   Dff aa ONE i[1] TICK RESET o[1] nq[1];
   Dff aa ONE i[2] TICK RESET o[2] nq[2];
   Dff aa ONE i[3] TICK RESET o[3] nq[3];
   Dff aa ONE i[4] TICK RESET o[4] nq[4];
   Dff aa ONE i[5] TICK RESET o[5] nq[5];
   Dff aa ONE i[6] TICK RESET o[6] nq[6];
   Dff aa ONE i[7] TICK RESET o[7] nq[7];
Endef;

Define INCR in[7..0] | INCROUT[7..0];
Full_Adder aa ONE    in[0] ZERO  | c-out1 INCROUT[0];
Full_Adder aa c-out1 in[1] ZERO  | c-out2 INCROUT[1];
Full_Adder aa c-out2 in[2] ZERO  | c-out3 INCROUT[2];
Full_Adder aa c-out3 in[3] ZERO  | c-out4 INCROUT[3];
Full_Adder aa c-out4 in[4] ZERO  | c-out5 INCROUT[4];
Full_Adder aa c-out5 in[5] ZERO  | c-out6 INCROUT[5];
Full_Adder aa c-out6 in[6] ZERO  | c-out7 INCROUT[6];
Full_Adder aa c-out7 in[7] ZERO  | c-out8 INCROUT[7];
Endef;


Define MIR-Comp Reset N Z Phase[4..1] | MIR[31..0] MPC[7..0];
Not bb Phase[1] nTick;
Not bb Reset nReset;

Switch "CLOCK" aa CLOCK ZERO; 
Switch "R" aa R ZERO; 

MPC aa MMUXOUT[7..0] Phase[1] nReset | MPC[7..0];

INCR ab MPC[7..0] | INCROUT[7..0];

Mux-mxn ac  MIR[7..0] INCROUT[7..0] MSLOUT | MMUXOUT[7..0];
Probe ac MMUXOUT[0];
Probe ac MMUXOUT[1];
Probe ac MMUXOUT[2];
Probe ac MMUXOUT[3];
Probe ac MMUXOUT[4];
Probe ac MMUXOUT[5];
Probe ac MMUXOUT[6];
Probe ac MMUXOUT[7];

MSL ad N Z MIR[30] MIR[29] | MSLOUT;

Probe ad MSLOUT;

MIC2 ba MPC[7..0] | MPS[31..0];

Register bb MPS[31..0] nTick | MIR[31..0];

Endef;
