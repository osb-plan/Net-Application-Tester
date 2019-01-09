# Net-Application-Tester

Please this project is under development. This application is intented for use only on Unix/Linux machines.
Thank you.

DEPENDENCIES

apt-get install libxml2
If it doesn't work create the symbolic link in /usr/lib/x86_64-linux-gnu folder.
The other dependencie is libpthread.


USAGE
To use the generator start the executable:

make
./neta -d dictionary.xml -l log.txt - v 2

-d flag is to provide the dictionary file, inthis file the user can define the characteristics of each field of the struct and their variation.

-l to provide the log file, the application prints some messages on this file

-v verbosity level.

TEST
Tested and compiled with gcc 5.4.0 20160609


