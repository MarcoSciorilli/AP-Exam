# Exam project

###### Advanced Programming exam 2020-2021

###### Group members: *Cavuoti Lorenzo*, *Sciorilli Marco*, *Sicklinger Marco*

### AP-Exam repository

The project is divided into a series of directories in order to keep it as tidy as possible. 

The *AP-Exam* repository directly contains four files (LICENSE, this README.md file and a Report) and two directories (cpp_exam and python_exam). 

##### Report

The *Report.md* file contains the description of the work done by this group.



#### Directory: *cpp_exam*

The *cpp-exam* directory contains the Binary Search Tree project. The *cpp_exam* directory contains the Binary Search Tree project and a `makefile` used to compile the codes. Typing `make documentation` will create the documentation for the project using doxygen.

There is an *include* directory, storing the headers `bst.h` and `methods.h`. The former contains the code related to the implementation of the BST node and the iterator class, plus the declaration of all the needed functions (the smallest ones are also defined here), while the latter contains all the needed definitions.

A *trials* directory is also present, containing a `.cpp` file called `trials.cpp` in which the group tested the implemented tree.

Finally, the *benchmark* directory contains a series of files related to the benchmarking of the BST. executing the `test.sh` script found in this directory will run the benchmark on your machine and plot the results.

#### Directory: *python_exam*

The *python_exam* directory contains the python notebook of the assigned python exercise and the corresponding test file.
