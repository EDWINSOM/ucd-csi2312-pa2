#include <iostream>
#include "Point.h"
#include "Cluster.h"


using namespace std;
using namespace Clustering;


int main() {

    Point first(2);
    first.setValue(1,90);
    first.setValue(2,7099990);


    Point second(2);
    second.setValue(1,90);
    second.setValue(2,709090);


   bool equalTo = (second >= first);


    cout << endl << equalTo << endl;







    // deallocate memory of all nodes !
    return 0;
}