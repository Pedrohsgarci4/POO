#ifndef TRUCK_H
#define TRUCK_H

#include<iostream>
#include "Vehicle.hpp"


class Truck : public Vehicle{
    public:
        Truck( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, std::string adress) : Vehicle( placa, chassi, modelo, capacidade, ano, adress){}

};

#endif