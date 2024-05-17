#!/bin/bash

if [[ "$1" == "clean" || "$1" == "c" ]]; then
	find . ! -name setup.sh ! -name README.txt ! -name failed.sh -delete
	exit
elif [[ "$1" == "help" || "$1" == "h" ]]; then
	echo "Usage: ./setup.sh [option]"
	echo "Options:"
	echo "  No option: Set up the directory with the necessary files and directories."
	echo "  c, clean:  Remove all files and directories created by this script."
	echo "  h, help:   Display this help message."
	exit
fi


read -p "This script will set the directory back to default. Are you sure you want to continue? [y/n] " yesno

if [[ ! $yesno =~ ^[Yy]$ && ! -z $yesno ]]; then
	exit 1
fi

find . ! -name setup.sh ! -name README.txt ! -name failed.sh -delete

mkdir dir1 dir2 dir3
touch dir1/file1 dir2/file2 dir3/file3
mkdir dir1/subdir1 dir2/subdir2 dir3/subdir3
touch dir1/subdir1/file1 dir2/subdir2/file2 dir3/subdir3/file3
touch empty_file empty_file2
wget -qO bible.txt http://www.gutenberg.org/files/10/10-0.txt

mkdir permission_tests; cd permission_tests
touch r_only w_only x_only rw_only rx_only wx_only 000_only 777_only 
chmod 444 r_only
chmod 222 w_only
chmod 111 x_only
chmod 666 rw_only
chmod 555 rx_only
chmod 333 wx_only
chmod 000 000_only
chmod 777 777_only
cd ..

echo "\"It's Britney, bitch.\" - Various sources." > quote1.txt
echo "\"I am Groot\" - Groot, Guardians of the Galaxy." > quote2.txt
echo "\"That's what she said\" - Michael Scott, The Office (US)." > quote3.txt

chmod +x *.sh