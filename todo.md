# TO DO LIST

### No environment at launch
	env -i /bin/bash #removes all env variables

### Handle environment variables
	$_ #-> list_replace(env, "_", get_last_arg(args));

### Invalid input:
	cat notafile #(should be handled through cat itself) 

### Input/Output redirections: 
	<<stop1 <<stop2 cat >outfile | cat <<stop3
	<infile >outfile <invalidinput cat
	>outfile cat <infile




