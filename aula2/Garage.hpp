#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <iostream>
#include <list>
#include "Vehicle.hpp"
#include "Order.hpp"

class Garage {
private:
    std::string local;
    std::list<Vehicle*> active_vehicles;

    template<typename Func>
    Vehicle* search(Func func);

public:
    Garage(std::string local);
    ~Garage();

    void add_vehicle(Vehicle* vehicle);
    void remove_vehicle(Vehicle* vehicle);

    Vehicle* search_by_id(int id);
    Vehicle* search_by_placa(std::string placa);
    std::list<Vehicle*> search_by_local(std::string local);
    std::list<Vehicle*> search_by_availability();
    bool fulfill_order(Order* order);
};



#endif