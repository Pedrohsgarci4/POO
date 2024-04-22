#ifndef TRUCK_H
#define TRUCK_H

#include<iostream>
#include "Vehicle.hpp"


class Truck : public Vehicle{
    public:
        Truck( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, double lat, double lng) : Vehicle( placa, chassi, modelo, capacidade, ano, lat, lng){}

};

#endif