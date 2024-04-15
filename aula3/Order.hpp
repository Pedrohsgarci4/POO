#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <list>
#include "Vehicle.hpp"
#include "Client.hpp"

class Client;

class Order {
private:
    static std::list<Order*> instances;
    static int prox_id;

    int id;
    Client* client;
    std::string description;
    Coordinates collection_point;
    Coordinates delivery_point;
    int weight;
    int size;
    std::list<Vehicle*> vehicles;

    void increment_id();

public:
    Order(int client_id, std::string description, Coordinates collection_point, Coordinates delivery_point, int weight, int size);
    ~Order();

    Client *get_client();

    std::string get_description();
    int set_description(std::string description);

    Coordinates get_collection_point();
    int set_collection_point(double lat, double lng);

    Coordinates get_delivery_point();
    int set_delivery_point(double lat, double lng);

    int get_weight();
    int set_weight(int weight);

    int get_size();
    int set_size(int size);

    void add_vehicle(Vehicle* vehicle);
    void remove_vehicle(Vehicle* vehicle);
    void clear_list_vehicle();
};

#endif
