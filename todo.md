# TO DO LIST

### No environment at launch
	env -i /bin/bash #removes all env variables
	# SEE: set_env function in ./handle_env.c

### Handle environment variables
	$_ #-> env_set__(args, env);
	# IMPORTANT: shell variables are NOT environment variables

### Input/Output redirections: 
	<<stop1 <<stop2 cat >outfile | cat <<stop3
	<infile >outfile <invalidinput cat
	>outfile cat <infile

