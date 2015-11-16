# ucd-csi2312-pa3
KMeans Clustering Algorithm
Programmer: Marisa Edwinson

Complier: gcc,gnu

The principal objective of this assignment was to implement the widely used KMeans Algorithm to sort out an accumulation of points into respective clusters as to sort and organize them based on proximity to central reference points (centroids). The centroid of a cluster is an imaginary point which is the mean of all the points in the cluster. 

The methods of implementation are based on our previously developed Point and Cluster classes. In this particular project, the points to be sorted are stored and read in from a comma seperated value file (CSV file). The code presented here is designed to handle any number of points with any number of dimensions. 

The setter method that allows for the reading in of points from a file involves an overloaded insertion operator (>>). Also, we introduce a new class, the KMeans class, which is the destination of point reading. Once the KMeans methods are implemented, the sorted points are outputted to a text file which will display their respective clusters via an id tag. 
The outputted file is also a CSV file. 

