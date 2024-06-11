#ifndef ORDER_HPP
#define ORDER_HPP

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
        Coordinates collection_point;
        Coordinates delivery_point;
        Coordinates collection_point;
        Coordinates delivery_point;
        float weight;
        float volume;
        std::string priority;
        std::list<Vehicle*> vehicles;

        static void increment_id();

    public:
        Order(int client_id, Coordinates collection_point, Coordinates delivery_point, float weight, float volume, std::string priority);
        ~Order();

        int get_id() const;
        Client *get_client() const;
        Coordinates get_collection_point() const;
        Coordinates get_delivery_point() const;
        Coordinates get_collection_point() const;
        Coordinates get_delivery_point() const;
        float get_weight() const;
        float get_volume() const;
        std::string get_priority() const;

        int set_collection_point(double lat, double lng);
        int set_delivery_point(double lat, double lng);
        int set_weight(float weight);
        int set_volume(float volume);
        int set_priority(std::string priority);

        void add_vehicle(Vehicle* vehicle);
        void remove_vehicle(Vehicle* vehicle);
        void clear_list_vehicle();

        bool operator==( const Order& other);
        friend std::ostream& operator<<( std::ostream& os, const Vehicle& obj);
};

#endif
