#include "../include/Vehicle.hpp"
#include <iostream>
#include "../include/Car.hpp"


Car::Car( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, double lat, double lng) : Vehicle( placa, chassi, modelo, capacidade, ano, lat, lng)
{
    
}

Car::~Car(){}