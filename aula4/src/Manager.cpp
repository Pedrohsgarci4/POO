#include<iostream>
#include "../include/Manager.hpp"


Manager::Manager( Garage* garage){
    this->garage = garage;
}

Manager::~Manager() { }


int Manager::add_order( Order* order){
    if( order == nullptr){
        return 1;
    }
    this->orders.push_back(order);
    return 0;
}

int Manager::add_order( int client_id, Coordinates collection_point, Coordinates delivery_point, float weight, float size, std::string priority)
{
    Order * order = new Order(client_id, collection_point, delivery_point, weight, size, priority);

    this->orders.push_back( order);

    return 0;
}

bool Manager::fulfill_order( Order *order, int num){
    /*
    Função de atende pedidos sem se importar com a quantidade se veiculos 
    Num = numero de veiculos que serão usados a principio 
    */ 
    int weight = order->get_weight();

    int i = num;
    while (weight > 0){
        // Busca baseado na metade do peso
        Vehicle *vehicle = this->garage->search_by_weight( weight/i);

        // se naõ encontrar dividira o peso ainda mais na proxima interação;
        if ( vehicle == nullptr){
            i++; 
            if ( i > 15) {
                return false;
                std::cout << "Capacidade de carros disponiveis muito menor que o necessário\n";
            }
        }
        else{
            order->add_vehicle( vehicle);
            vehicle->set_available(false);

            weight -= vehicle->get_capacidade();
            i = num;
        }
        
    }
    return true;
    
}

bool Manager::fulfill_order_with_quantify( Order *order){
    /*
    Função de atende pedidos usando a menor quantidade de veiculos possivel
    */ 

    int weight = order->get_weight();

    Vehicle *vehicle = this->garage->search_by_weight( order->get_weight());

    if( vehicle == nullptr){
        return fulfill_order( order);
    }
    order->add_vehicle( vehicle);
    vehicle->set_available(false);
    return true;
}

void Manager::fulfill_orders( bool priority){
    // priority: o pedido sera encaminhado para veiculos com capacidade maior se true
    // senão o trabalho sera dividido para veiculos menores

    auto order = this->orders.begin(); // Percorrendo lista
    while (order != this->orders.end()){
        auto current  = order;
        bool status = false;
        if( priority){
            status = this->fulfill_order_with_quantify( *order);   
        }
        else{
            status = this->fulfill_order(*order);
        }
        if( status){
            std::cout << "Foi atendido\n";
            order++;
            this->orders.remove( *current);
        }
        else{
            std::cout << "Nao foi atendido\n";
            order++;
        }
    }
}

bool Manager::operator==( const Manager& other){
    return this->garage == other.garage;
}

std::ostream& operator<<( std::ostream& os, const Manager& obj){
    return os << obj.garage << std::endl;
}
