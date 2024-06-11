#ifndef PICKUP_HPP
#define PICKUP_HPP

#include<iostream>
#include "Vehicle.hpp"

class Pickup : public Vehicle{
    public:
        Pickup( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, double lat, double lng) ;
        
};

#endif
