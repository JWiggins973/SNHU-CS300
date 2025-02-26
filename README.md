# SNHU-CS300
This is my reflection and final project done in this course

#What was the problem you were solving in the projects for this course?

The problem solved in the course projects was determining the appropriate data stucture to use to store course information (class code, class name, and prerequisites), while sorting (in order of class code), and searching, ensuring the best possible big O. This was achieved by comparing the big O of a vector, binary search tree and linked list.

#How did you approach the problem? Consider why data structures are important to understand.

At the end of each module, after learning about a specific data structure, pseudocode was created to outline the process. This included opening a file, validating it, and then creating an object to store course information. The object was then inserted into the chosen data structure. Additional pseudocode was cretaed to handle searching, sorting, and printing.

For the first project, the pseudocode was analyzed line by line to determine the Big-O complexity of insertion, search, sorting for each data structure. The results were organized into a chart to provide a clear comparison of each structure’s strengths and weaknesses.  

From this analysis, I concluded that a vector is the easiest data structure to implement, offering fast insertions and quick searches for small datasets, though its search and sort performance can degrade significantly as the dataset grows. A hash table allows for fast searches and quick insertions when collisions are minimal, but it lacks built-in sorting and can degrade to O(N) performance if many collisions occur. A binary search tree (BST), maintains sorting during insertion, resulting in the fastest sorting and printing times, but it is the most complex to implement and requires additional memory to store both course information and pointers.

By understanding the strengths and the trade offs between different data structures, I was able to determine the best approach.

#How did you overcome any roadblocks you encountered while going through the activities or project?

One particular road block I encountered during the BST and linked list assignments was understanding the core foundations of implementing a linked list, which caused me to struggle alot with these assignments. The way I overcame this obstacle was to constantoy refrence zybooks and use online resources like youtube videos to visulaize how they worked.

#How has your work on this project expanded your approach to designing software and developing programs?

Working on this project expanded my approach to design software and develop programs by now considering the importance of choosing the correct data structure based on the task at hand. By understanding the pros and cons of each and how they scale based on the size of data will help ensure I'm creating an efficent program.

#How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

My work on this project has improved the way I write programs that are maintainable, readable, and adaptable by breaking the project into smaller steps, using meaningful comments, and choosing sensible variable and function names. Additionally, understanding the pros and cons of different data structures and how they perform in best and worst case scenarios helps in creating efficient and scalable programs.
