#ifndef CAR_HPP
#define CAR_HPP

#include<iostream>
#include "Vehicle.hpp"


class Car : public Vehicle{
    public:
        Car( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, double lat, double lng);

        ~Car();
};

#endif