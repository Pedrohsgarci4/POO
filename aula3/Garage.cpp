#include "Garage.hpp"
#include <iostream>
#include <algorithm>

Garage::Garage( double lat, double lng){
    this->coordinates.set_coordinates( lat, lng);
}

Garage::~Garage() {
    // Limpeza de memória, se necessário
}

void Garage::add_vehicle(Vehicle* vehicle) {
    this->active_vehicles.push_back(vehicle);
}

void Garage::remove_vehicle(Vehicle* vehicle) {
    this->active_vehicles.remove(vehicle);
}

std::list<Vehicle*>* Garage::get_active_vehicles(){
    return &this->active_vehicles;
}

// Busca por id
Vehicle* Garage::search_by(int id) {
    auto compara_id = [id](Vehicle* vehicle) {
        return vehicle->get_id() == id;
    };
    return search(compara_id);
}

// Busca por placa
Vehicle* Garage::search_by(std::string placa) {
    auto compara_placa = [placa](Vehicle* vehicle) {
        return vehicle->get_placa() == placa;
    };
    return search(compara_placa);
}

// Busca por coordenadas
std::list<Vehicle*> Garage::search_by( double lat, double lng) {
    Coordinates coordinates(lat, lng);
    std::list<Vehicle*> veiculos_no_local;
    for (auto vehicle : this->active_vehicles) {
        if (vehicle->get_coordinates() == coordinates) {
            veiculos_no_local.push_back(vehicle);
        }
    }
    return veiculos_no_local;
}
// Busca por disponibilidade
std::list<Vehicle*> Garage::search_by() {
    std::list<Vehicle*> vehicles;
    for (auto vehicle : active_vehicles) {
        if (vehicle->is_available()) {
            vehicles.push_back(vehicle);
        }
    }
    return vehicles;
}

Vehicle* Garage::search_by_weight( int weigth){
    Vehicle *aux = nullptr;
    for (auto vehicle : active_vehicles) {
        if (vehicle->get_capacidade()  >weigth && vehicle->is_available()) {
            aux = vehicle;
            break;
        }
    }
    return aux;

}

template<typename Func>
Vehicle* Garage::search(Func func) {
    auto it = std::find_if(active_vehicles.begin(), active_vehicles.end(), func);
    if (it != active_vehicles.end()) {
        return *it; // Retorna o ponteiro para o veículo encontrado
    } else {
        return nullptr; // Retorna nullptr se o veículo não for encontrado
    }
}

bool Garage::fulfill_order(Order* order) {
    std::list<Vehicle*> vehicles = search_by();
    if (!vehicles.empty()) {
        Vehicle* vehicle = vehicles.front();
        vehicle->set_available(false);
        order->add_vehicle(vehicle);
        std::cout << "O Pedido foi atendido\n";
        return true;
    }
    std::cout << "Todos os veiculos ocupados\nPedido não atendido\n";
    return false;
}

bool Garage::operator==( const Garage& other){
    return this->coordinates == other.coordinates;
}

std::ostream& operator<<( std::ostream& os, const Garage& obj){
    os << "Garagem: \n" << obj.coordinates << "\n" << "Veiculos: \n";
    for (auto vehicle : obj.active_vehicles ) {
        os << vehicle << "\n";
    }
    return os;
}

