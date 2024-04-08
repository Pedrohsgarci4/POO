#ifndef VEHICLE_H
#define VEHICLE_H

#include<iostream>
#include<list>

class Vehicle {
private:
    static int prox_id;

    int id;
    std::string placa;
    std::string chassi;
    std::string modelo;
    int capacidade;
    int ano;
    std::string local;

    bool available;

    void increment_id();

public:
    static std::list<Vehicle*>& get_instances();

    Vehicle(std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, std::string local);

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

    int set_local(std::string local);
    std::string get_local();

    bool is_available();

    void set_available(bool status);

protected:
    static std::list<Vehicle*> instances;
};

#endif
