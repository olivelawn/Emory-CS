/* #include "basic.h"
#include "clock.h" */

Define Comb RD WR | MREQ READ;
Or aa RD WR MREQ;
Or aa RD ZERO READ;
Endef;

Define SelectC RD WR | SELECT; /*  If select = 1 select c bus */
Not aa RD nRD;
And aa nRD WR SELECT;
Endef;

Define TRI in[15..0] WR | out[15..0];
Tri-state-buffer aa in[0] WR | out[0];
Tri-state-buffer aa in[1] WR | out[1];
Tri-state-buffer aa in[2] WR | out[2];
Tri-state-buffer aa in[3] WR | out[3];
Tri-state-buffer aa in[4] WR | out[4];
Tri-state-buffer aa in[5] WR | out[5];
Tri-state-buffer aa in[6] WR | out[6];
Tri-state-buffer aa in[7] WR | out[7];
Tri-state-buffer aa in[8] WR | out[8];
Tri-state-buffer aa in[9] WR | out[9];
Tri-state-buffer aa in[10] WR | out[10];
Tri-state-buffer aa in[11] WR | out[11];
Tri-state-buffer aa in[12] WR | out[12];
Tri-state-buffer aa in[13] WR | out[13];
Tri-state-buffer aa in[14] WR | out[14];
Tri-state-buffer aa in[15] WR | out[15];
Endef;


Define Comm Phase[4..1] RD WR MAR MBR MARData[15..0] DataBusIn[15..0]
C[15..0] | MReq READ AddrBus[15..0] DataBusOut[15..0] MBROutput[15..0];
Not bc WR nWR;

Register "MAR" aa MARData[15..0] marload | AddrBus[15..0];
Nand aa MAR Phase[3] marload;

Mux-mxn ba C[15..0] DataBusIn[15..0] sel | MUXOUT[15..0];

Register "MBR" bb MUXOUT[15..0] mbrload | MBROutput[15..0];
Nand bb MBR Phase[4] mbrload;

TRI bc MBROutput[15..0] nWR | DataBusOut[15..0];

Comb da RD WR | MReq READ;
SelectC da RD WR | sel;


Endef;

