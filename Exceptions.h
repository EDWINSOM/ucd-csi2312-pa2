//
// Created by marisa on 11/25/15.
//

#ifndef PA2_EXCEPTIONS_H
#define PA2_EXCEPTIONS_H

#include <string>

namespace Clustering {

    class DimensionalityMismatchEx
    {
                std::string name;

            public:

                DimensionalityMismatchEx() {}

                DimensionalityMismatchEx(std::string identification): name(identification) {}

                std::string getName() const { return name; }

                friend std::ostream &operator<<(std::ostream &, const DimensionalityMismatchEx &);

    };

    class OutOfBoundsEx
    {
        std::string name;

    public:

        OutOfBoundsEx() {}

        OutOfBoundsEx(std::string nameAssigned): name(nameAssigned) {}

        std::string getName() const {return name;};

        friend std::ostream &operator<<(std::ostream &, const OutOfBoundsEx &);

    };

    class RemoveFromEmptyEx
    {
        std::string name;

    public:

        RemoveFromEmptyEx() {}

        RemoveFromEmptyEx(std::string firstName): name(firstName) {}

        std::string getName() const {return name;}

        friend std::ostream &operator<<(std::ostream &, const RemoveFromEmptyEx &);

    };

}


#endif //PA2_EXCEPTIONS_H

