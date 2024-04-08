#include "Garage.hpp"
#include <iostream>
#include <algorithm>

Garage::Garage(std::string local) : local(local) {}

Garage::~Garage() {
    // Limpeza de memória, se necessário
}

void Garage::add_vehicle(Vehicle* vehicle) {
    active_vehicles.push_back(vehicle);
}

void Garage::remove_vehicle(Vehicle* vehicle) {
    active_vehicles.remove(vehicle);
}

Vehicle* Garage::search_by_id(int id) {
    auto compara_id = [id](Vehicle* vehicle) {
        return vehicle->get_id() == id;
    };
    return search(compara_id);
}

Vehicle* Garage::search_by_placa(std::string placa) {
    auto compara_placa = [placa](Vehicle* vehicle) {
        return vehicle->get_placa() == placa;
    };
    return search(compara_placa);
}

std::list<Vehicle*> Garage::search_by_local(std::string local) {
    std::list<Vehicle*> veiculos_no_local;
    for (auto vehicle : active_vehicles) {
        if (vehicle->get_local() == local) {
            veiculos_no_local.push_back(vehicle);
        }
    }
    return veiculos_no_local;
}

std::list<Vehicle*> Garage::search_by_availability() {
    std::list<Vehicle*> vehicles;
    for (auto vehicle : active_vehicles) {
        if (vehicle->is_available()) {
            vehicles.push_back(vehicle);
        }
    }
    return vehicles;
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
    std::list<Vehicle*> vehicles = search_by_availability();
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

