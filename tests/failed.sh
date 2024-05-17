########## Invalid read/fd ##########
ls;	#invalid read of size 1
	#invalid file descriptor -1 in syscall close()

##########      Leaks      ##########


##########   Redirection   ##########
<<'' <quote1.txt cat; #prints quote1.txt successfully but doesn't launch here_doc.
