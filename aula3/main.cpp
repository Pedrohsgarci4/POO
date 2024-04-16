#include<iostream>
#include"Garage.hpp"
#include"Order.hpp"
#include"Car.hpp"
#include"Pickup.hpp"
#include"Truck.hpp"
#include"Client.hpp"
#include "Adm.hpp"

int main(){

    Garage *garagem = new Garage( -13.0, 13.0);

    Car *uno = new Car("JAY-0000", "9BWHE21JX24060831", "Uno", 10, 2010, -13.0, 13.0);
    Car *prisma = new Car ("MNS-0000", "9BWHE21JX24060831" , "Prisma", 10, 2010, -13.0, 13.0);

    std::cout << uno;
    std::cout << garagem << '\n';

    Order *order = new Order( 0, "Transportar caixas", Coordinates( 10.0, 12.1),Coordinates(10.0, 10.1), 10, 100);
    
    Adm *adm = new Adm( garagem);

    adm->add_orders(order);
    adm->fulfill_orders( true);

}

