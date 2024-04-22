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

        static void increment_id();

    public:
        Order(int client_id, std::string description, Coordinates collection_point, Coordinates delivery_point, int weight, int size);
        Order(int client_id, Coordinates collection_point, Coordinates delivery_point, int weight, int size);
        ~Order();

        int get_id() const;
        Client *get_client() const;
        std::string get_description() const;
        Coordinates get_collection_point() const;
        Coordinates get_delivery_point() const;
        int get_weight() const;
        int get_size() const;


        int set_description(std::string description);
        int set_collection_point(double lat, double lng);
        int set_delivery_point(double lat, double lng);
        int set_weight(int weight);
        int set_size(int size);

        void add_vehicle(Vehicle* vehicle);
        void remove_vehicle(Vehicle* vehicle);
        void clear_list_vehicle();

        bool operator==( const Order& other);
        friend std::ostream& operator<<( std::ostream& os, const Vehicle& obj);

};

#endif
