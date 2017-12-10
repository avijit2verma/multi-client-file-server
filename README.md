# Multi Client File Server

This is an implementation of a file server capable of handling multiple clients at the same time. This program was written for a lab assignment during my Operating Systems course at IIT Bhubaneswar.

The basic philosphy here is that whenever a new file is requested to be opened, the server forks a new child process and uses it to open the file.

<b>How to run the program></b>

- Make the directory “data” to store the 100 files which will be created for sending and receiving.  

$ mkdir data 

- Generate the 100 files inside the data directory starting from 1 using the script gen.sh as discussed in the class. 

$ ./gen.sh 1 100 

- Compile and run server using the server.c program in terminal window as follows: 

$ cc –o server server.c 

$ ./server <Port no.> 

- Compile and run the client using the client.c program in another terminal window  as follows: 

$ cc –o client client.c 

$ ./client <IP(localhost)> <Port no.> <No. of concurrent clients > 

Note: The number of concurrent clients should be less than no of files created using the gen.sh script. 

- The logfile.txt (containing information about each transfer session) will be appended accordingly and saved to the same directory as server.c program. 
