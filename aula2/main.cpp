#include<iostream>
#include"Garage.hpp"
#include"Order.hpp"
#include"Car.hpp"
#include"Pickup.hpp"
#include"Truck.hpp"
#include"Client.hpp"

int main(){

    Garage *garagem = new Garage("Rua X, n");

    Car *uno = new Car("JAY-0000", "9BWHE21JX24060831", "Uno", 10, 2010, "Rua N, n");

    garagem->add_vehicle( uno);
    Client *cliente = new Client( "014.245.140-54", "Pedro", 18);

    Order *pedido = new Order( 0, "Transportar caixas", "Rua Não sei", "Rua Sem ideia", 10, 100);

    bool status = garagem->fulfill_order(pedido);

}

