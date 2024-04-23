#include "../include/Order.hpp"
#include <stdexcept>

std::list<Order*> Order::instances;
int Order::prox_id = 1;

void Order::increment_id() {
    prox_id++;
}

Order::Order(int client_id, std::string description, Coordinates collection_point, Coordinates delivery_point, int weight, int size) {
    this->id = prox_id;
    increment_id();

    this->client = nullptr;
    for (Client* client : Client::get_instances()) {
        if (client->get_id() == client_id) {
            this->client = client;
            client->add_order(this);
            break;
        }
    }

    this->description = description;
    this->collection_point = collection_point;
    this->delivery_point = delivery_point;

    if (weight < 1) {
        throw std::invalid_argument("Valor inválido para weight");
    }
    this->weight = weight;

    if (size < 1) {
        throw std::invalid_argument("Valor inválido para size");
    }
    this->size = size;

    instances.push_back(this);
}

// Construtor sem descricao
Order::Order(int client_id, Coordinates collection_point, Coordinates delivery_point, int weight, int size) {
    this->id = prox_id;
    increment_id();

    this->client = nullptr;
    for (Client* client : Client::get_instances()) {
        if (client->get_id() == client_id) {
            this->client = client;
            client->add_order(this);
            break;
        }
    }

    this->collection_point = collection_point;
    this->delivery_point = delivery_point;

    if (weight < 1) {
        throw std::invalid_argument("Valor inválido para weight");
    }
    this->weight = weight;

    if (size < 1) {
        throw std::invalid_argument("Valor inválido para size");
    }
    this->size = size;

    instances.push_back(this);
}

Order::~Order() {
    Client* c = this->get_client();
    if (c != nullptr) {
        c->delete_order(this);
    }
    instances.remove(this);
}



int Order::get_id() const{
    return this->id;
}

Client* Order::get_client() const{
    return client;
}

std::string Order::get_description() const{
    return description;
}

Coordinates Order::get_collection_point() const{
    return collection_point;
}

Coordinates Order::get_delivery_point() const{
    return delivery_point;
}

int Order::get_weight() const{
    return this->weight;
}

int Order::get_size() const{
    return size;
}


int Order::set_description(std::string description) {
    if (description.size()) {
        this->description = description;
        return 1;
    }
    return 0;
}

int Order::set_collection_point(double lat, double lng) {
    this->collection_point.set_coordinates( lat, lng);
    return 1;
}

int Order::set_delivery_point( double lat, double lng) {
    
    this->delivery_point.set_coordinates( lat, lng);
    return 1;

}

int Order::set_weight(int weight) {
    if (weight > 0) {
        this->weight = weight;
        return 1;
    }
    return 0;
}

int Order::set_size(int size) {
    if (size > 0) {
        this->size = size;
        return 1;
    }
    return 0;
}




void Order::add_vehicle(Vehicle* vehicle) {
    this->vehicles.push_back(vehicle);
    vehicle->set_available(false);
}

void Order::remove_vehicle(Vehicle* vehicle) {
    this->vehicles.remove(vehicle);
}

void Order::clear_list_vehicle() {
    this->vehicles.clear();
}


bool Order::operator==( const Order& other){
    return this->get_id() == other.id;
}

std::ostream& operator<<(std::ostream& os, const Order& obj) {
    os << "<Pedido " << obj.get_id() << ">\nDe:\n" << obj.get_collection_point() << "\nPara:\n" << obj.get_delivery_point() << "\n";
    return os;
}

