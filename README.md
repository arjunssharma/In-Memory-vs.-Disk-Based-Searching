Arjun Sharma
CSC 541, Assignment 1

# In Memory vs. Disk-based Searching

## Introduction

This C project serves as an introduction to random-access file I/O in UNIX
using C, as well as an investigation of time efficiency isssues associated
with in-memory versus disk-based searching. Two different databases have
been provided, seek.db and key.db. These both contain lists of integers in
binary form. The purpose of the assignment is to use the seek database to
search for values in the key database. Implementations for four 
different searching strategies have been created:

- Linear search in memory
- Binary search in memory
- Linear search on disk
- Binary search on disk

## Program Execution

This program has been designed to only function in a UNIX environment. A
makefile has been provided, which will compile the project and create the
executable ```assn_1```. The following demonstrates how to compile and
run the program:

```
$ make
$ ./assn_1 search_mode key_db seek_db
```

```search_mode``` has four different options:

- ```--mem-lin``` is used for in memory, linear searching
- ```--mem-bin``` is used for in memory, binary searching
- ```--disk-lin``` is used for on disk, linear searching
- ```--disk-bin``` is used for on disk, binary searching

```key_db``` and ```seek_db``` are the respective key and seek databases
containing binary integer data. 

### Source Code

Source code for the project is found in assn_1.c. 

### Target Environment

Per class requirements, this project has been targeted for a UNIX platform
and gcc compiler 3.4.6. 

## Program Output

The program will go through each integer in the seek database and search
for it in the key database. It will create output for each entry in the
seek database and display whether or not it was found in the key database.
It will also display the time it took for the given search strategy to
complete, as follows:

```
        6474: No
         104: Yes
        4387: Yes
        9473: Yes
		...
		Time: 0.291555
```

## Testing

An example seek and key database have been provided, as well as an 
example of what the output should look like. These can be found in the
```data/example``` folder of this project.

The provided makefile can be used to test each of the four search 
strategies implemented. 

```
$ make test
```

The above command will run each search method against the example
databases provided, outputting to ```output.txt```. The output will then
be diff'ed against the example output, and the results of the diff
will be written to ```test_results.txt```. Note that the output file
is deleted with each search run, and this file is deleted after the last
search. 

