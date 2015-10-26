# ucd-csi2312-pa2
Clusters and Points


Programmer: Marisa Edwinson

Complier: gcc , gnu

This project involved extensive manipulation and creation of a Point class and a Cluster class. 

The overall structure of the project involved the creation of abstacted objects called Clusters. Each cluster contained inside it a singly linked list made of "nodes" (also a form of abstracted objects). Each 
Cluster has a member that keeps a pointer to the first node, and a size member variable to keep track of the number of Point objects held within the Cluster (one Point per Node). 

Each Node has two members, a Point pointer and another node pointer (NodePtr) that points to (keep track/access of) the next node in the list. All Node's are dynamically allocated. 

The Point pointer within the node is used to point to a dynamically allocated Point object. Each point object can be thought of a point in an n-dimensional space, as the number of dimensions is allowed to vary in this program. For example, a 3-dimensional Point object would have member variables x,y,z to represent its coordinates.

Below is a description of the features for both the Point class and Cluster Class:


Point class

-  Point objects can have an arbitrary number of dimensions of doubles. That is, (1, 2), (1, 2, 4), (2, 3, ..., 5, 6), etc. 

-  Each has a member function specifying the value of the dimension for that point and an array of doubles to hold the coordinate values for each dimension. This array is dynamically allocated.
 
-  There is a "distanceTo() member function available to calculate the distance between to Point objects
 
-  There is an extensive list of overloaded operators to allow Point object arithmetic and comparison. 

Note*       We assume a lexicographic order, that is, (3, 4, 5) > (1, 2, 3) > (-1, 2, 3) > (-1, 1, 3) > (-1, 1, 2), etc. In other words, compare the first dimension, then the second, and so on.




Cluster class

-    The Cluster can hold an arbitrary number of Point-s. This is made possible by a Point pointer that points to a dynamically allocated Point object. 
   
-   The Cluster class makes use of a singly-linked list.

-   Each cluster has a "size" member variable to keep track of how many Point objects you have in the Cluster.

-   The linked list is dynamically allocated by default.

-   A Cluster can remain empty and/or unused.

-   Point objects contained in the Cluster are in lexicographic order 

-   There are member functions that allow Cluster arithmetic, comparison, and the adding or deleting of a Point within the cluster




