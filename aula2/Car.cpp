#include"Vehicle.hpp"
#include<iostream>
#include "Car.hpp"


Car::Car( std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, std::string adress) : Vehicle( placa, chassi, modelo, capacidade, ano, adress){}

Car::~Car(){}

        