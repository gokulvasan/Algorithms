############################################
Use the Makefile with the following commands
############################################

Requirements:
The program count_letters gathers statistics about C source files and prints them on the stdout.
The command line is: count_letters <files..> . Where <files..> is a list of source files or text files.
Output example: letter            number            percent
		a/A.               12.               23%
                b/B.               34.               41%
                 . 		    .                 .
                 .                  .                 .
                 z/Z	            z                 zz%

1- I can build the binary with gcc and arm-none-eabi-gcc.
2- I can give external text files as argument to the main.
3- I can get an output on the console (for POSIX) showing the letter count in the text file.
4- I can run „make posix“, „make posix debug“, „make arm“, „make arm debug“.
5- I can run the posix version on linux/Mac OS
6- You are free to use the compiler version you want.

make posix
----------
build for posix system (macos, linux)
result is count_letters.bin count_letters.map

make posix debug
----------
build debug version for posix system (macos, linux)
result is count_letters.bin, count_letters.elf count_letters.map

make arm
----------
build with arm-none-eabi-gcc for arm systems
result is count_letters.bin count_letters.map

make arm debug
----------
build debug version  with arm-none-eabi-gcc for arm systems
result is count_letters.bin, count_letters.elf count_letters.map