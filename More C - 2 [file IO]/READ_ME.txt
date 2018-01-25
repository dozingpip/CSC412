#===============================================================================#
#  Example of input from the console and of input output from a file			#
#  The program is broken into three parts:										#
#		- Part I deals with input/output from the console						#
#		- Part II deals with I/O with "text files" in which numbers are 		#
#			stored as human-readable strings.									#
#		- Part III deals with I/O with "binary files" in which numbers are		#
#			stored in their compact native format (4 bytes for an int, 8 bytes	#
#			for a double, etc.).												#
#===============================================================================#

This program uses multiple source files and header files.  I am going to use it
later on as a way to teach you how to make complex make files.  For the time
being, you can simply build it by listing all the .c files to gcc

gcc main.c  asciiIO.c  binaryIO.c  -o myProg


The program runs without arguments

./myProg
