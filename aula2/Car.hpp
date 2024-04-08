#ifndef CAR_H
#define CAR_H

#include<iostream>
#include "Vehicle.hpp"


class Car : public Vehicle{
    public:

        Car( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, std::string adress) ;

        ~Car();
};

#endif