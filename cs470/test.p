program Test (input, output);




  var
	this_sum : integer;		{this is a comment compiler ignore}
        max_sum : real;
	sequence : array[0..1000] of integer;
        i : integer;
	arraysize : integer;


  begin

	i := 0;
	this_sum := 0;
	max_sum := 0;
 
  	writeln ('Please insert a series of numbers, delimited by -999');
 
	read(sequence[i]);
	while(sequence[i] <> -999) do
	   begin
		i := i+1;
		arraysize := arraysize + 1;
		read(sequence[i]);
	   end;
 
	i := 0;
	while(sequence[i] <> -999) do
	   begin
	       	writeln(sequence[i]);
	   	i := i+1;
	   end;

	write('arraysize is');
	writeln(arraysize);

  end.

