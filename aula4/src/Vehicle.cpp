#include "../include/Vehicle.hpp"
#include <stdexcept>

std::list<Vehicle*> Vehicle::instances;
int Vehicle::prox_id = 1;

void Vehicle::increment_id() {
    prox_id++;
}

std::list<Vehicle*>& Vehicle::get_instances() {
    return instances;
}

Vehicle::Vehicle(){
    this->id = prox_id;
    increment_id();

    this->available = true;

    instances.push_back(this);
}

Vehicle::Vehicle(std::string placa, std::string chassi, std::string modelo, int capacidade, int ano, double lat, double lng) {
    if (placa.size() != 8) {
        throw std::invalid_argument("Valor inválido para placa");
    }
    this->placa = placa;

    if (chassi.size() != 17) {
        throw std::invalid_argument("Valor inválido para chassi");
    }
    this->chassi = chassi;

    if (modelo.empty()) {
        throw std::invalid_argument("Valor inválido para modelo");
    }
    this->modelo = modelo;

    if (capacidade < 1) {
        throw std::invalid_argument("Valor inválido para capacidade");
    }
    this->capacidade = capacidade;

    if (ano < 1886) {
        throw std::invalid_argument("Valor inválido para ano");
    }
    this->ano = ano;

    this->coordinates.set_coordinates( lat, lng);

    this->id = prox_id;
    increment_id();

    this->available = true;

    instances.push_back(this);
}

Vehicle::~Vehicle() {
    instances.remove(this);
}

int Vehicle::get_id() {
    return this->id;
}

int Vehicle::set_placa(std::string placa) {
    if (placa.size() == 7) {
        this->placa = placa;
        return 1;
    }
    return 0;
}

std::string Vehicle::get_placa() {
    return this->placa;
}

int Vehicle::set_chassi(std::string chassi) {
    if (chassi.size() == 17) {
        this->chassi = chassi;
        return 1;
    }
    return 0;
}

std::string Vehicle::get_chassi() {
    return this->chassi;
}

int Vehicle::set_modelo(std::string modelo) {
    if (!modelo.empty()) {
        this->modelo = modelo;
        return 1;
    }
    return 0;
}

std::string Vehicle::get_modelo() {
    return this->modelo;
}

int Vehicle::set_capacidade(int capacidade) {
    if (capacidade > 0) {
        this->capacidade = capacidade;
        return 1;
    }
    return 0;
}

int Vehicle::get_capacidade() {
    return this->capacidade;
}

int Vehicle::set_ano(int ano) {
    if (ano > 1885) {
        this->ano = ano;
        return 1;
    }
    return 0;
}

int Vehicle::get_ano() {
    return this->ano;
}

int Vehicle::set_coordinates(double lat, double lng) {
    this->coordinates.set_coordinates( lat, lng);
    return 1;
}

Coordinates& Vehicle::get_coordinates() {
    return this->coordinates;
}


bool Vehicle::is_available() {
    return this->available;
}

void Vehicle::set_available(bool status) {
    this->available = status;
}


bool Vehicle::operator==( const Vehicle& other){ 
    return this->get_id() == other.id;
}

std::ostream& operator<<( std::ostream& os, const Vehicle& obj){
    return os << obj.modelo <<" de placa "<< obj.placa;
    
}
