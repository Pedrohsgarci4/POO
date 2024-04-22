#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <iostream>
#include <list>
#include "Vehicle.hpp"
#include "Order.hpp"

class Garage {
private:
    Coordinates coordinates;
    std::list<Vehicle*> active_vehicles;

    template<typename Func>
    Vehicle* search(Func func);

public:
    Garage( double lat, double lng);
    ~Garage();

    void add_vehicle(Vehicle* vehicle);
    void remove_vehicle(Vehicle* vehicle);
    std::list<Vehicle*>* get_active_vehicles();

    Vehicle* search_by(int id);
    Vehicle* search_by(std::string placa);
    Vehicle* search_by_weight( int weigth);

    // metodo retorna uma lista com base em disponibilidade 
    std::list<Vehicle*> search_by();
    // metodo retorna uma lista com base na proximidade 
    std::list<Vehicle*> search_by( Coordinates coordinates);
   
    bool operator==( const Garage& other);

    friend std::ostream& operator<<( std::ostream& os, const Garage& obj);
};



#endif