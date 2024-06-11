#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include<iostream>
#include<list>
#include "Coordinates.hpp"

class Vehicle {
private:
    static int prox_id;

    int id;
    std::string placa;
    std::string chassi;
    std::string modelo;
    int capacidade;
    int ano;
    Coordinates coordinates;

    bool available;

    void increment_id();

public:
    static std::list<Vehicle*>& get_instances();

    Vehicle();

    Vehicle(std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, double lat, double lng);

    virtual ~Vehicle();

    int get_id();

    int set_placa(std::string placa);
    std::string get_placa();

    int set_chassi(std::string chassi);
    std::string get_chassi();

    int set_modelo(std::string modelo);
    std::string get_modelo();

    int set_capacidade(int capacidade);
    int get_capacidade();

    int set_ano(int ano);
    int get_ano();

    int set_coordinates( double lat, double lng);
    Coordinates& get_coordinates();

    bool is_available();

    void set_available(bool status);

    bool operator==( const Vehicle& other);

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& obj);

protected:
    static std::list<Vehicle*> instances;
};

#endif
