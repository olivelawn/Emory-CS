Define Four-Phase-Clock r t | Phase[3..0];
 Switch aa set ONE;
 Switch aa reset ONE;

 Dff aa ONE sw1 t ONE q1 q1x;
 Dff aa ONE sw2 t ONE q2 q2x;

 Not aa r not-r;
 Xor aa q1 q2 q1-xor-q2;

 And aa not-r q1-xor-q2 sw1;

 And aa q2x not-r sw2;

 And aa q1x q2x Phase[0];
 And aa q1x q2 Phase[1];
 And aa q1 q2x Phase[2];
 And aa q1 q2 Phase[3];
 
Endef;


