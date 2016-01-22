# Computer Architecture II, Coursework 2 - Cache Simulator - 22/01/2016 - Ravi Woods

## Development Methodology

For this coursework, I used a basic form of Test-Driven development. To do this, I started by producing a set of 3 tests. Each test had 3 text files, for parameters, inputs and the expected outputs. These tests were produced from my understanding of the cache, and aimed to cover most, if not all, edge cases in the specification. Then, I could test and iterate from an empty source file to a finished solution. 

For developing the code, I broke the problem down into 3 more basic problems:

1. Parsing the input and parameters into their respective components.
2. Defining data structures for simulation of the cache.
3. Using these data structures to execute instructions on the cache. For this I needed a good understanding of the cache. Flowcharts like [this one](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c2/Write-back_with_write-allocation.svg/640px-Write-back_with_write-allocation.svg.png) were useful.

Throughout the development, I preferred using STL containers and other C++ optimisations, to add easy to use structure within the code. In addition, I often preferred to abstract away from hardware when I needed. An example was to store the data in a different container to the cache container.

## Use of scripting

Having written the test files, I wrote a shell script which took the parameters and input instructions from the previously written tests, compiled the source files, wrote the output of the source file to another text file (time stamped so I could access it later, if needed), and compared it with the expected output. 

To make easy transitions between different tests, I put each set of text files for a test in one directory, and added a line in the script to change between these directories. 

These scripts have 3 forms, for different operating systems, as I often changed during development.

## Further debugging 

The first debug tool I used, given in the specification, was debug-req. When using this, I printed out each set of the cache, and the block addresses stored inside it. The disadvantage of this system was that it wouldn't print out the data stored within the cache, but this didn't pose a problem for the most part.

In addition to this, I built a preprocessor instruction which would print the name of a variable and its value at any point to standard error, so I could check variables when needed. I could turn this off also, for submission.

## File structure

The structure of the submission directory is as follows 
```
+-readme.md  # This document
|
+-source # All sources and headers.
| |
| +-mem_sim.cpp
| +-mem_sim_functions.cpp
| +-mem_sim_functions.hpp
| +-mem_sim_classes.hpp
| +-mem_sim_libs.hpp
|
+-test_files # Contains shell scripts and text files for the 3 tests.
| +-cygwin_test.sh
| +-mac_test.sh
| +-ubuntu_test.sh
| +-4way # test files for 4-way set associative cache
| 	+-input.txt
| 	+-output.txt
| 	+-params.txt
| 	+-got # directory to store time-stamped output files
| +-directmapped # test files for direct-mapped cache (produced by Dr.Thomas)
| 	+-input.txt
| 	+-output.txt
| 	+-params.txt
| 	+-got # directory to store time-stamped output files
| +-fullyassoc # test files for fully associative cache
| 	+-input.txt
| 	+-output.txt
| 	+-params.txt
| 	+-got # directory to store time-stamped output files
```