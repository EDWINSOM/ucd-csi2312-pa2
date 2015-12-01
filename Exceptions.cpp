//
// Created by marisa on 11/25/15.
//

#include "Exceptions.h"
#include <iostream>

using namespace std;

namespace Clustering {

  ostream &operator<<(std::ostream &ostream, const DimensionalityMismatchEx &ex) {

        cout << endl << "DimensionalityMismatchEx( " << ex.getName() << " )";

        return ostream;
    }

    ostream &operator<<(std::ostream &ostream1, const OutOfBoundsEx &ex) {

        cout << endl << "OutOfBoundsEx( " << ex.getName() << " )";

        return ostream1;
    }

    ostream &operator<<(std::ostream &ostream2, const RemoveFromEmptyEx &ex) {

        cout << endl << "RemoveFromEmptryEx( " << ex.getName() << " )";

        return ostream2;
    }
}

