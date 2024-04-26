#!/bin/bash --posix

posix() { export $@; export; }
msh() { ./exe $@; }

#leaks() #SHOWS INCONSISTENT RESULTS WHEN VALUES NOT DEFINED IN QUOTES
#{
#	echo -e "\n\033[1;31mVALGRIND\033[0;31m"
#	valgrind ./exe "$value" 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|total heap usage"; 
#	echo -en "\033[0m"
#}

posix_values=(
	""
	"="
	"''"
	"'x'"
	"=="
	"key"
	"key="
	"key=="
	"key=val1=val2"
	"key=val1 key2"
	"key=val1 key2=val2"
	"0"
	"0="
	"0=="
	"0=x"
	"0=hey"
	"k'e'y=1"
	"k'e'y=1"
 	"yo$hey=wassup" #define $hey before testing
)

make re

for value in "${posix_values[@]}"; do
	echo
	echo -e "\033[0;33mTEST '\033[1;33m$value\033[0;33m'\033[0m"
	echo -n > tests/test.msh && echo -n > tests/test.posix
	msh "$value" > tests/test.msh
	posix "$value" > tests/test.posix; unset $value
	diff --color tests/test.posix tests/test.msh

	echo; #leaks; echo

	read -p "Press q to quit, or Enter to continue: " input
	if [[ $input == "q" ]]; then
		exit 0
	fi
done