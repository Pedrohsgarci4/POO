#include<iostream>
#include"Garage.hpp"
#include"Order.hpp"
#include"Car.hpp"
#include"Pickup.hpp"
#include"Truck.hpp"
#include"Client.hpp"

int main(){

    Garage *garagem = new Garage( -13.0, 13);

    Car *uno = new Car("JAY-0000", "9BWHE21JX24060831", "Uno", 10, 2010, -13.0, 13);

    garagem->add_vehicle( uno);
    Client *cliente = new Client( "014.245.140-54", "Pedro", 18);

    Order *pedido = new Order( 0, "Transportar caixas", Coordinates( 10, 12),Coordinates(10, 10), 10, 100);

    bool status = garagem->fulfill_order(pedido);

}

