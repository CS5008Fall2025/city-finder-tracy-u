# Report
Fill out these report questions. 


1. What is the difference between a directed and undirected graph?
   In a directed graph edges have a direction. For example, A may connect to B, but 
   B does not connect to A. In an undirected graph the edge connects A and B such
   that you can traverse the path from A to B and B to A. 

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.
     * $O(V2)$
   * Assuming you used a heap / priority queue to store the vertices.
     * $O((V + E) log V)$

3. Explain in your own words what that means for larger graphs when trying to find the shortest distance. 
   - When trying to find the shortest distance for larger graphs, Dijkstra's will become much slower.
   with an array, it will require two calculations for each vertex. The use of a priority queue is more
   efficient than an array and will see slightly slower growth.

## Deeper Thinking
4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer. 

   For a very large data set, using something like an adjacency list would be better than a matrix.
   Similarly, using a heap/priority queue would be more efficient. Memoization would be especially helpful
   in this type of scenario (where the distances between vertices are not frequently changing.) 
   From my professional life, I know there are graph databases, which are structured to store vertices and edges and also to specifically query the properties of those vertices and edges. Now that I understand
   a graph and its potential uses, I am much more interested in learning more about the use of those! 


## Future Understanding
5. Related to shortest distance, is a problem called the "messenger" or "traveling sales person" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops?
     * 720 (6!)
   * How many possible paths are there if you have 10 stops?
     * 3628800 (10!)
6. What type of growth is this problem? 
   * Factorial growht
7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it? 
   The TSP problem is a computational optimization problem, and it is classified as NP-complete.
   This means that it is both NP and NP-hard. [^1] [^2] An NP-Hard problem "NP-hard if, for every problem L which can be solved in non-deterministic polynomial-time, there is a polynomial-time reduction from L to H." [^3] An NP problem is a problem "...for which any given yes-solution can be verified as a solution in polynomial time by a deterministic Turing machine (or solvable by a non-deterministic Turing machine in polynomial time)." [^3] NP-Complete is a "[c]lass of decision problems which contains the hardest problems in NP. Each NP-complete problem has to be in NP." [^3]


8. Provide some examples of fields / problems that use TSP.
   Some examples of fields that use TSP are 



> [!TIP]
> We are having you explore TSP, so you can see the terms used for problem classification that are often the foundation of computer science theory. You will not be asked to know about TSP outside of this assignment or even problem classification. Computer Science is often about dealing with problems considered "too hard" or "impossible", and finding ways to make them possible! As such, knowing topics such as N, NP, NP-Complete, etc. is important to understand the limits (to break).


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

*You and your partner pull the same file from Github to make changes. You both change the same section of code. Your partner pushes their changes first, then you try to push. What is the result and how do you resolve this?*
   This will likely result in a merge conflict. There are a few options to resolve this. 
   - You can git pull and merge changes. This will attempt to merge your partner's changes into yours. It may result in conflicts that need to be addressed case-by-case. Once those are addressed, you can create a commit and push your changes. This approach typically results in a commit noting the merge. 
   - You can rebase your branch. If you thought about this like building layers of legos, this method would pick up your layer of legos (code) and layer in your partner's layer of legos (code) and then put your legos back on top. This might still result in conflicts that need to be addressed case-by-case. Once those are addressed, you can push your changes. This avoids merge commits, but can be more complicated on shared branches with lots of activity. [^4] (<- this is was a favorite resource of mine for learning git.)


2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others. 
   I spent a lot of time trying to build a struct that stored the letter and the count
   which required a lot of weird looping. When I remembered this week's lab and the 
   ascii hash exercise, where we could convert a char to an int just by casting, 
   the exercise became much easier. Instead of creating a map, just using the ascii
   value as the index simplified the code. Additionally, it was a good lesson that
   starting from 0 and incrementing up for each index, rather than looping through 
   and comparing to every previous value, was much more efficient. Rather than starting
   with the values in this string, starting with all possible values was actually
   much more readable and efficient. 


   ```c
   int firstUniqChar(char* s) {
    size_t length = strlen(s);
    if (length == 1) return 0;

    int charCount[256] = {0}; // create an array initialized to 0
    
    // increment frequencies
    for (int i = 0; i < length; i++) {
        int index = (int)s[i]; // convert to ascii
        charCount[index]++;
    }
    
    for (int i = 0; i < length; i++) {
        int index = (int)s[i]; // convert to ascii
        if (charCount[index] == 1) {
            return i;
        }
    }
    
    return -1;
   }
   ```


References
1. https://en.wikipedia.org/wiki/Complexity_class#:~:text=Relationships%20between%20complexity%20classes,-Savitch's%20theorem&text=These%20relationships%20answer%20fundamental%20questions,also%20solve%20in%20exponential%20space.
2. https://www.geeksforgeeks.org/dsa/difference-between-np-hard-and-np-complete-problem/
3. https://en.wikipedia.org/wiki/NP-hardness
4. https://www.youtube.com/watch?v=mGSecJDvtUQ