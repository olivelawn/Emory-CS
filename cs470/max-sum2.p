 
  program Max_Sum (input, output);

  type
    List = array[1..1000] of integer;

  var
    size, max_sum, index: integer;
    sequence: List;
    temp2: List;
	

  procedure Readseq ( var sequence :List; var size : integer);
   var ii :integer;

  begin				    	{this procedure reads input for sequence  }	
    ii := 1;				{from stdin.  sequence and size are called}
    readln(sequence[ii]);		{by reference so their values may be 	  }
    size := 1;				{accessed from main.  var ii is local to  }
    while (sequence[ii] <> -9999) do	{to the procedure.			  }
     begin
      ii := ii + 1;
      readln(sequence[ii]);
      size := size + 1;
     end;
  end;  { of read procedure }

procedure Compute (var sequence, temp2:List; var max_sum, index, size: integer);

var  this_sum, ii, jj, kk : integer;   {these variables local to procedure compute}
     temp1 : List; 

begin
  max_sum := 0;			{max_sum holds the sum of maximum subsequence}
  temp2[1] := -9999;		{temp2 holds the actual values of maximum subsequence}
  for ii := 1 to size do	{we use -9999 as a delimter in the main procedure}
    begin			{hence the reason that temp2 is called by reference}
      index := 1;		{in this procedure.}
      this_sum := 0;
      
       for jj := ii to size do			{this_sum holds the current sequence}
        begin					{sum, and then compares with max_sum}
          temp1[index] := sequence[jj];		{if this_sum is larger, it's value is}
          index := index + 1;			{exchanged with max_sum, then the delimter}
          this_sum := this_sum + sequence[jj];  {is put into temp1, which has been holding}
          if this_sum > max_sum then 		{the greatest subsequence thus far in loop}
            begin				
              max_sum := this_sum; 
              temp1[index] := -9999;
              
	       for kk := 1 to index do		{if this_sum > max_sum copy the sequence}
                temp2[kk] := temp1[kk];		{into temp2 array which is the greatest}
            end;				{sequence so far in outer loop}
        end;
    end;
 end;  { of compute procedure }



begin {of main}



  writeln('Enter a sequence of numbers delimited by -9999:');
    
  Readseq (sequence, size);			    {read input for sequence from stdin}
  Compute (sequence, temp2, max_sum, index, size);  {computes max sum, and greatest}
						    {sequence.  max sum is put into var}
  index := 1;					{max_sum, and the sequence is put into }
  writeln('The maximum sequence found is: '); 	{temp2 array.  Both of these are called}
  write('{');					{by reference			       }
  while (temp2[index] <> -9999) do
    begin					{this loop just prints out sequence and}
      write(temp2[index]);			{stops at the -9999 delimiter	       }
      index := index + 1;
    end;
  write('}');
  writeln;
  writeln('The maximum sum is: ', max_sum);
end.
	
