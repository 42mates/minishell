#!/bin/bash --posix

posix() { export $@; export; }
msh() { ./exe $@; }

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
 	"yo$hey=magle" #$define $hey

### TO TEST MANUALLY ###
	#key="'"
	#key='"'
)

make re

for value in "${posix_values[@]}"; do
	echo
	echo -e "\033[0;33mTEST '\033[1;33m$value\033[0;33m'\033[0m"
	msh "$value" > test.msh
	posix "$value" > test.posix
	unset $value
	diff --color test.posix test.msh
	echo 
	read -p "Press enter to continue "
done