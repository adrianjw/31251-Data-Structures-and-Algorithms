# Assignment 1 - Directed Graphs

### Overview
Your task is to implement a directed graph class, offering a reasonably effective suite of operations, including computing spanning trees, depth and breadth first traversals, and implementing iterators.

### The Code
You are provided with a `directed_graph.hpp` file, which includes all the basic definitions you will need (and it can be done with just those - I made sure). You made add extra methods, classes, structs etc., as long as they don't interfere with the operation of the tests. You may not include any further classes from the standard library in any of your marked code. You have also been provided with a `main.cpp` for ad-hoc testing purposes. `main.cpp` file does not form part of the assignment, and will not be marked. You can do anything you like with it. When the "run" button is pressed, it will compile and run `main.cpp`. When the "mark" button is pressed, your code will be run against the tests. Note that as this is C++, if your code causes a program crash (e.g. a segfault), the testing code cannot recover, and will fail to mark your work - if you get this, make sure you fix that problem first!

You have also been given a copy of `test.h`, which is the set of tests that the code will be run against. Note that this code has had certain elements removed (things that would just give part of the solution), so it's not runnable in its current state, but it may help you understand where you program is failing, and to design your own tests to be run with `main.cpp`.

Remember to read over all the code before starting.

You have terminal access if you so desire it.

### Directed Graphs
As the abstract data structure, and the possibilities for implementing it, have been covered in the lectures, I won't repeat them here. Please refer to the lecture material for the technical details in this regard. However, don't hesitate to ask questions etc. - you're welcome to inquire, I just don't want to clutter this space up!

### The `directed_graph` Class
`directed_graph` is probably the most complicated C++ class you will have had to implement, but it bears a great resemblance to many of the things we've already done, so just break it down into smaller, more manageable tasks. The code itself is commented to indicate the purpose of each method. Again, to avoid clutter, I won't repeat it all here, but do not hesitate to ask if anything is unclear (there's a forum specifically for the assignment).

### Marking
The assignment will be marked against three components: functionality, design and style.

**Functionality** will be marked exclusively by the tests, and constitutes 50% of the total mark.

**Design** constitutes 35% of the total mark. It does not depend on the functionality of your code. You may be asked questions by your tutor to help them test your understanding of your code. It will be marked qualitatively against the following rubric:

- **Pass:** The code shows basic understanding of how to employ data structures to achieve a goal. The design should avoid unnecessary data structures and should make reasonable use of iteration and recursion when appropriate.
- **Credit:** The design shows a solid understanding of data structures and demonstrate effective use of control structures to achieve the program’s goals.
- **Distinction:** The design shows a high degree of understanding of how to use data structures to achieve a goal efficiently, and demonstrate some evidence that the design does not use unnecessary resources. The design should be clean and efficient.
- **High Distinction:** The design demonstrates a high degree of understanding of data structures and how to efficiently employ them to build algorithms that not only meet technical goals, but support maintenance and future development.

**Style** constitutes 15% of the total mark. It will be marked qualitatively against the following rubric:

- **Pass:** The code mostly uses some formatting standard and is somewhat readable.
- **Credit:** The code adheres well to a formatting standard and variables are well named.
- **Distinction:** At least as well formatted as for Credit standards, along with sufficient inline commenting to explain the code.
- **High Distinction:** Excellent formatting and variable naming. Excellent, judiciously employed comments that explain the code without just repeating the code.

### Submission
You will submit your work with the "mark" button on Ed. No other submissions will be accepted. You are welcome to develop your code elsewhere, if that suits your workflow, but remember it must compile and run on Ed. We are using the g++ compiler set to C++17 standard for this assessment. However code that compiles with clang++ should also work with g++ (unless you're doing something weird - so check first!).

You may submit as many times as you like (in fact, repeated submission is an expected part of the development process).

### Plagiarism Checking
All code will be checked for student misconduct and plagiarism using specialised code similarity detection software.
