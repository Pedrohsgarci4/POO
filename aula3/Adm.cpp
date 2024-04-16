#include<iostream>
#include "Adm.hpp"


Adm::Adm( Garage* garage){
    this->garage = garage;
}


int Adm::add_orders( Order* order){
    if( order == nullptr){
        return 1;
    }
    this->orders.push_back( order);
    return 0;
}

void Adm::fulfill_orders_without_quantity( Order *order){
    int weight = order->get_weight();

    while (weight > 0){
        Vehicle *vehicle = this->garage->search_by_weight( 0);

        if ( vehicle == nullptr){
            this->fulfills_orders_for_minors( order);
            return;
        }
        order->add_vehicle( vehicle);
        vehicle->set_available(false);
        weight -= vehicle->get_capacidade();
    }
    return;
    
}

void Adm::fulfills_orders_for_minors( Order *order){
    /*
    Função de atende pedidos usando a menor quantidade de pedidos possivel
    */ 

    int weight = order->get_weight();

    Vehicle *vehicle = this->garage->search_by_weight( 0);

    if( vehicle == nullptr){
        return;
    }
    order->add_vehicle( vehicle);
    vehicle->set_available(false);
    
}

void Adm::fulfill_orders( bool priority){
    // priority: o pedido sera encaminhado para veiculos com capacidade maior se true
    // senão, o trabalho sera dividido para veiculos menores
    while ( !this->orders.empty()){
        Order *order = this->orders.front();
        this->orders.pop_front();
        if( priority){
            this->fulfills_orders_for_minors( order);
            std::cout<< "Foi atendido \n";
        }
        else{
            this->fulfill_orders_without_quantity(order);
        }
    }
    
}
