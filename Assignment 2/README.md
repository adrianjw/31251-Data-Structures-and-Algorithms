# Assignment 2 - Algorithms on Directed Graphs

### Overview
You task is to code a small collection of graph algorithms:

- Shortest paths
- DAG testing
- DAG Hamiltonian path testing
- Connected component search
- Strongly connected component search
- Topological Sort

These will use the directed graph from assignment 1 (or rather, a modified, definitely working version of it).

### The Code
You are provided with a number of C++ files, the one you will be assessed on is `directed_graph_algorithms.cpp`. The six methods present in the skeleton are the entry point for the tests. To support this there is a `directed_graph.hpp` file, which includes a fully working implementation of a directed graph. Note that it is somewhat different from the assignment 1 specification, so make sure you familiarise yourself with it. You are also provided with a `main.cpp` to do any testing you like. The run button will compile and execute `main.cpp`, the submit button will run `graph_algorithms.cpp` against the tests.

You may modify any of these files as you see fit, as long as the tests still execute, apart from adding additional libraries, though you have an extended collection of libraries compared to assignment 1.

As with the first assignment, you should be able to complete the assignment within the `graph_algorithms.cpp` file (though you are not restricted to this), but you will likely need to add extra functions, perhaps extra classes, so on and so forth.

In a folder you can also view the testing code. This is not the copy that is executed, it's just there for your edification. If any bugs or mistakes in the tests are discovered, the actual tests may be altered, so the code here should only be taken as a guide (hopefully a good guide, but nonetheless).

### The Algorithms
As mentioned in the overview, you are to implement six graph based algorithms. In rough order of difficulty, they are:

- Shortest paths
- DAG testing
- DAG Hamiltonian path testing
- Topological Sort
- Connected component search
- Strongly connected component search

This ordering may vary quite a bit, depending on how you approach the problems however, so take some time to think carefully how you will solve each one. As these are described in the lectures, I will not add additional clutter here about their function or details (but you can of course as questions).

### Marking
**Functionality** constitutes 70% of the total mark and will be marked exclusively by the tests.

**Design** constitutes 20% of the total mark. It does not depend on the functionality of your code. You may be asked questions by your tutor to help them test your understanding of your code. It will be marked qualitatively against the following rubric:

- **Pass:** The code shows basic understanding of how to employ data structures to achieve a goal. The design should avoid unnecessary data structures and should make reasonable use of iteration and recursion when appropriate.
- **Credit:** The design shows a solid understanding of data structures and demonstrate effective use of control structures to achieve the program’s goals.
- **Distinction:** The design shows a high degree of understanding of how to use data structures to achieve a goal efficiently, and demonstrate some evidence that the design does not use unnecessary resources. The design should be clean and efficient.
- **High Distinction:** The design demonstrates a high degree of understanding of data structures and how to efficiently employ them to build algorithms that not only meet technical goals, but support maintenance and future development.

**Style** constitutes 10% of the total mark. It will be marked qualitatively against the following rubric:

- **Pass:** The code mostly uses some formatting standard and is somewhat readable.
- **Credit:** The code adheres well to a formatting standard and variables are well named.
- **Distinction:** At least as well formatted as for Credit standards, along with sufficient inline commenting to explain the code.
- **High Distinction:** Excellent formatting and variable naming. Excellent, judiciously employed comments that explain the code without just repeating the code.

### Submission
You will submit your work with the "submit" button on Ed. No other submissions will be accepted. You are welcome to develop your code elsewhere, if that suits your workflow, but remember it must compile and run on Ed. We are using the g++ compiler set to C++17 standard for this assessment. However code that compiles with clang++ should also work with g++ (unless you're doing something weird - so check first!).

### Plagiarism Checking
All code will be checked for student misconduct and plagiarism using specialised code similarity detection software.
