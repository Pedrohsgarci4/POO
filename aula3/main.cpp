#include<iostream>
#include"include/Garage.hpp"
#include"include/Order.hpp"
#include"include/Car.hpp"
#include"include/Pickup.hpp"
#include"include/Truck.hpp"
#include"include/Client.hpp"
#include "include/Manager.hpp"

int main(){

    Garage *garagem = new Garage( -13.0, 13.0);

    Car *uno = new Car("JAY-0000", "9BWHE21JX24060831", "Uno", 10, 2010, -13.0, 13.0);
    Car *prisma = new Car ("MNS-0000", "9BWHE21JX24060831" , "Prisma", 10, 2010, -13.0, 13.0);
    std::cout << *uno;

    std::cout << *garagem << '\n';

    garagem->add_vehicle(prisma);
    garagem->add_vehicle(uno);

    Order *order = new Order( 0, "Transportar caixas", Coordinates( 10.0, 12.1),Coordinates(10.0, 10.1), 5, 10);
    
    Order *order2 = new Order( 0, "Transportar caixas", Coordinates( 10.0, 12.1),Coordinates(10.0, 10.1), 5, 4);
    Manager *adm = new Manager( garagem);

    adm->add_order(order);
    adm->add_order(order2);
    adm->fulfill_orders( true);


    return 0;
}

