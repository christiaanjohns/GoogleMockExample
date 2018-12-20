#ifndef FIRSTEXAMPLE_ADDRESS_H
#define FIRSTEXAMPLE_ADDRESS_H


#include <string>

struct Address {
    std::string road;
    std::string city;
    std::string state;
    std::string country;

    std::string summaryDescription() const
    {
        return road + ", " + city + ", " + state + ", " + country;
    }
};

#endif //FIRSTEXAMPLE_ADDRESS_H
