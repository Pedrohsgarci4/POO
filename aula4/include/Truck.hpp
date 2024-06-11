#ifndef TRUCK_HPP
#define TRUCK_HPP

#include<iostream>
#include "Vehicle.hpp"


class Truck : public Vehicle{
    public:
        Truck( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, double lat, double lng);

};

#endif