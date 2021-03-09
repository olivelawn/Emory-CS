
Define Circuit1 mem read line | OUT;
Not aa line nline;
And aa mem read nline out;
Not aa out OUT ;
Endef;

Define Circuit2 mem read line | rw en tri;
And aa mem read line tri-tmp;
Not aa tri-tmp tri;
Or  aa ZERO read rw;
And aa mem line en-tmp;
Not aa en-tmp en;
Endef;

Define TRI1 in[15..0] en | out[15..0];
Tri-state-buffer aa in[0] en | out[0];
Tri-state-buffer aa in[1] en | out[1];
Tri-state-buffer aa in[2] en | out[2];
Tri-state-buffer aa in[3] en | out[3];
Tri-state-buffer aa in[4] en | out[4];
Tri-state-buffer aa in[5] en | out[5];
Tri-state-buffer aa in[6] en | out[6];
Tri-state-buffer aa in[7] en | out[7];
Tri-state-buffer aa in[8] en | out[8];
Tri-state-buffer aa in[9] en | out[9];
Tri-state-buffer aa in[10] en | out[10];
Tri-state-buffer aa in[11] en | out[11];
Tri-state-buffer aa in[12] en | out[12];
Tri-state-buffer aa in[13] en | out[13];
Tri-state-buffer aa in[14] en | out[14];
Tri-state-buffer aa in[15] en | out[15];
Endef;
 

Define TRI2 in[7..0] en | out[7..0];
Tri-state-buffer aa in[0] en | out[0];
Tri-state-buffer aa in[1] en | out[1];
Tri-state-buffer aa in[2] en | out[2];
Tri-state-buffer aa in[3] en | out[3];
Tri-state-buffer aa in[4] en | out[4];
Tri-state-buffer aa in[5] en | out[5];
Tri-state-buffer aa in[6] en | out[6];
Tri-state-buffer aa in[7] en | out[7];
Endef;



Define Memory MReq Read Addr[15..0] DataIn[15..0] | DataOut[15..0] ;

Rom64x16 aa Addr[5..0] ZERO RomOut[15..0]
10 4168 72 0 0 0 0 0 0 0 0 
15 0     0 0 0 0 0 0 0 0 0 
0  0     0 0 0 0 0 0 0 0 0 
0  0     0 0 0 0 0 0 0 0 0
0  0     0 0 0 0 0 0 0 0 0
0  0     0 0 0 0 0 0 0;

Circuit1 ba MReq Read Addr[6] | tri-enable;
Probe "1tri" ba tri-enable;
TRI1 ab RomOut[15..0] tri-enable | DataOut[15..0];


Ram64x8 ac DataIn[15..8] Addr[5..0] rw outen Data[15..8];
Circuit2 bc MReq Read Addr[6] | rw outen tri;
Probe "2rw" bc rw;
Probe "2en" bc outen;
Probe "2tri" bc tri;
TRI2 ad Data[15..8] tri | DataOut[15..8];

Ram64x8 ae DataIn[7..0] Addr[5..0] rw outen Data[7..0];
TRI2 af Data[7..0] tri | DataOut[7..0];

Endef;


