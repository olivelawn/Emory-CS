Define TestRom1 a[3..0] | d[15..0];
   Rom16x16 aa a[3..0] ZERO d[15..0]
	0 1 2 3 4 5 6 7 8 9 10 167 897 9876 14890 56789;
Endef;

Define TestRom2 a[3..0] | d[15..0];
   Rom16x16 aa a[3..0] ZERO d[15..0]
	1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768;
Endef;
