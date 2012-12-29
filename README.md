os_replacement
==============

Implement several replacement policies and compare between them in terms of performance.


1. The code was written under the Ubuntu Linux System (Version 11.10).
2. The Compiler version is GCC 4.6.1.
3. I have written a "makefile" document.
   So just type "make" command under current directory to compile source code.
   Type "make clean" under current directory to remove object and execution files.
4. The format of running source code is as below:

   ./Replacement <replace method> <memory size> <input file name>

   (1) The <replace method> argument is necessary;
       0: First In First Out
       1: Second Chance
       2: Least Recently Used
   (2) The <memory size> is necessary;
	   The memory size must be a positive non-zero number.
   (3) The <input file name> argument is necessary;
