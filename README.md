# ucd-csi2312-pa2
Clusters and Points

Due: Mon, Sep 21, at 23:59 Mountain time

PA2 asks you to update your 3D Point class to make it more universal and functional and create a Cluster class which will hold a big number of Point objects. You have to write your own README.md, describing your work in the form of documentation for the two classes Point and Cluster.

You have to submit the assignment on Canvas, but all you have to do is enter the URL of your public PA2 Github repository in the text-entry box during the submission process.

In the README.md of your PA2 submission, indicate which compiler you have used, in a section called Compiler, in case the auto-checker finds problems with your submission that can be attributed to differences between compilers.

Point class

The requirements for the Point class are as follows:

    Point-s should be able to have an arbitrary number of dimensions of doubles. That is, (1, 2), (1, 2, 4), (2, 3, ..., 5, 6), etc. You need to:
        Add a private dim member.
        Create at least one constructor which takes an int for the dimension and an array of double-s. Of course, the array has to be at least as big as the dimension value. You will have to decide if it makes sense to have a default constructor and what initialization it should do.
        Take care of all consequences of this change, including updating the distanceTo() function.
        Since the dimension could be potentially very large, you have to allocate it dynamically, and take care of all cleanup. Memory leaks will be penalized.
        Remember what dynamic allocation means: overload the "big three".
    Point objects should be comparable. You need to:
        Overload the comparison operators: ==, !=, <, >, <=, and >=. Hint: reuse the implementation of == for !=, and so on. This makes the implementation more consistent, easy to ready, and less error prone.
        Assume a lexicographic order, that is, (3, 4, 5) > (1, 2, 3) > (-1, 2, 3) > (-1, 1, 3) > (-1, 1, 2), etc. In other words, compare the first dimension, then the second, and so on.
    Point arithmetic should be allowed. You need to:
        Overload the arithmetic operators: +, -. Addition and subtraction should be dimension-wise, that is, (1, 2, 3) + (4, 5, 6) gives (5, 7, 9). Similar with subtraction.
        Create factor-wise multiplication and division: *, /. That is, if p1 is a point (1, 2, 3), then p1*4 should give a point (4, 8, 12). Similar for division. (Remember to disallow division by zero.) Factors should be doubles.
        Overload the compound assignment operators according to the rules in (1) and (2) above: +=, -=, *=, and /=.

Cluster class

The requirements for the Cluster class are as follows:

    The Cluster should be able to have an arbitrary number of Point-s. You have to:
        Use a typedef statement to create an alias for the type Point * (that is, pointer to Point). Call it PointPtr. Make sure it is global in your namespace.
        Create a private nested structure type Node to support a singly-linked list. Hint: It only needs two members!
        Create a private singly-linked list member of the Cluster class to hold the Point-s. Hint: This is just a pointer to the head.
        Optional: You could, if you want, create an alias to the Node * type (that is, pointer to Node), and use appropriately. If you do so, make sure it is visible where it is used.
        Create a size member to keep track of how many Point-s you have in the Cluster.
        A linked list is dynamically allocated by default: overload the big three.
        Implement a default constructor, if it makes sense. Hint: A Cluster can remain empty and/or unused.
    The linked list naturally supports an order of the elements. You have to:
        Keep the Point-s contained in the Cluster in the lexicographic order mentioned in the requirements for the Point class. Hint: Use the Point comparison operators when adding a Point.
    Since Cluster-s contain PointPtr-s, the corresponding points can be treated as a set, even if there are points that are equal to each other. (Hint: Two points (1, 2, 3) and (1, 2, 3) will have different addresses.) You have to:
        Overload operator+ to represent the UNION of two Cluster-s.
        Overload operator- to represent the INTERSECTION of two Cluster-s. Hint: This may be empty.
        Overload operator==. It will return true iff (this means if and only if) two Cluster-s contain exactly the same points (that is, PointPtr-s). Hint: The ordering might come useful here.
        Overload the compound assignment operators accordingly.
    Cluster-s should be able to to add and remove Point-s. You should:
        Implement the add() and remove() functions to be able to add and remove PointPtr. Hint: See the signatures in the array-based definition of the Cluster class from the lectures.
        Overload operator+ to allow a statement like this: c1 = c1 + p1, where c1 is a Cluster and p1 is a Point. Hint: How similar or different is this to add()?
        Overload operator- to allow a statement like this: c2 = c2 - p2, where c2 is a Cluster and p2 is a Point. Hint: How similar or different is this to remove()?
        Overload the compound operators accordingly.

Clustering namespace

All of your class definition code should be inside a namespace, called Clustering. Make sure your types and typedefs are all properly wrapped in the namespace. Make sure you use the proper ways to access types from a namespace.
Testing

You have to follow the requirements and, for each feature you have to implement, you have to write one or more small snippets of code to test the proper function of the feature. You have to:

    Identify each feature that can be tested independently.
    Think of all the possible ways a programmer might try to use this feature. Each of these is called a use case.
    For each use case, design the minimal code snippet to test if your implementation performs correctly. Hint: Use assert statements from the <cassert (Links to an external site.)> library. For example, for points (1, 2, 3), (3, 4, 5), and (4, 6, 8), the statement assert((1, 2, 3) + (3, 4, 5) == (4, 6, 8)); should pass (that is, not exit).
    Each use case should be a separate function.
    Your main() should call all these functions one after the other as you implement more and more.
    If you think of some new scenario, especially some combination of the features you are implementing, go to (1) and repeat.

Coding style

Familiarize yourself with and start following these coding style guidelines (Links to an external site.). NOTE: If you stumble on the Google C++ Style Guide, be advised that it has been heavily criticized by many leading C++ programmers. I don't advise you to follow it, especially the more advanced features. This Guide is for entry-level coders at Google who need to be able to work with their legacy code. It is not advisable for new projects and novice programmers.
References

Operator overloading guidelines (Links to an external site.).

A very good C++ tutorial (Links to an external site.), including many topics we are covering.

The C++ reference (Links to an external site.).
