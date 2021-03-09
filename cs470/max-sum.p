 
  program Max_Sum (input, output);

  var
    i, k, ii, jj, size, this_sum, max_sum, index : integer;
    sequence: array[1..1000] of integer;
    temp1: array[1..1000] of integer;
    temp2: array[1..1000] of integer;
	
  begin
  writeln('Enter a sequence of numbers delimited by -9999:');
	
  i := 1;
  readln(sequence[i]);
  size := 1;
  while (sequence[i] <> -9999) do
    begin
      i := i + 1;
      readln(sequence[i]);
      size := size + 1;
    end;
    
  max_sum := 0;
  temp2[1] := -9999;
  for ii := 1 to size do
    begin
      index := 1;
      this_sum := 0;
      
       for jj := ii to size do
        begin
          temp1[index] := sequence[jj];
          index := index + 1;
          this_sum := this_sum + sequence[jj];
          if this_sum > max_sum then 
            begin
              max_sum := this_sum; 
              temp1[index] := -9999;
              
	       for k := 1 to index do
                temp2[k] := temp1[k];	
            end;
        end;
    end;
    
  index := 1;
  writeln('The maximum sequence found is: ');
  write('{');
  while (temp2[index] <> -9999) do
    begin
      write(temp2[index]);
      index := index + 1;
    end;
  write('}');
  writeln;
  writeln('The maximum sum is: ', max_sum);
end.
	
