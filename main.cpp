#include <iostream>
#include "Point.h"
#include "Cluster.h"


using namespace std;
using namespace Clustering;


int main() {



 Cluster c1;

 Point a1(2);
 a1.setValue(1,1);
 a1.setValue(2,1);
 PointPtr ap = &a1;

 Point a2(2);
 a2.setValue(1,2);
 a2.setValue(2,1);
 PointPtr ap2 = &a2;

 Point a3(2);
 a3.setValue(1,3);
 a3.setValue(2,0);
 PointPtr ap3 = &a3;

 c1.add(ap);
 c1.add(ap2);
 c1.add(ap3);

 cout << c1;

 Point adder(2);
 adder.setValue(1,0);
 adder.setValue(2,9);
 PointPtr ap4 = &adder;

Cluster m;

 m = (c1 + ap4);

 cout << m;

 Cluster n;

 n = (m - ap2);

 cout << n;





    // deallocate memory of all nodes !
    return 0;
}