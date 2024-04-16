#ifndef ADM_H
#define ADM_H

#include<iostream>
#include "Order.hpp"
#include "Garage.hpp"
#include"Car.hpp"
#include"Pickup.hpp"
#include"Truck.hpp"
#include"Client.hpp"


class Adm{
    private:
        Garage *garage;
        std::list<Order*> orders;
        std::list<Order*> orders_fulfilled;

    public:
        Adm( Garage *garage );
        ~Adm();

        int add_orders( Order *order);
        void fulfill_orders( bool priority);
        void fulfills_orders_for_minors( Order *order);
        void fulfill_orders_without_quantity( Order *order);
};

#endif