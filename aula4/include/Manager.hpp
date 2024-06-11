#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<iostream>
#include "Order.hpp"
#include "Garage.hpp"
#include"Car.hpp"
#include"Pickup.hpp"
#include"Truck.hpp"
#include"Client.hpp"


class Manager{
    private:
        Garage *garage;
        std::list<Order*> orders;
        std::list<Order*> orders_fulfilled;

    public:
        Manager( Garage *garage );
        ~Manager();

        int add_order( Order *order);
        int add_order(int client_id, Coordinates collection_point, Coordinates delivery_point, float weight, float size, std::string priority);
        void fulfill_orders( bool priority);
        bool fulfill_order_with_quantify( Order *order);
        bool fulfill_order( Order *order,  int num = 2);

        bool operator==( const Manager& other);
        friend std::ostream& operator<<( std::ostream& os, const Manager& obj);
};

#endif