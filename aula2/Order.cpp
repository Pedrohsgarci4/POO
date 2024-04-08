#include "Order.hpp"
#include <stdexcept>

std::list<Order*> Order::instances;
int Order::prox_id = 1;

void Order::increment_id() {
    prox_id++;
}

Order::Order(int client_id, std::string description, std::string collection_point, std::string delivery_point, int weight, int size) {
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

Order::~Order() {
    Client* c = this->get_client();
    if (c != nullptr) {
        c->delete_order(this);
    }
    instances.remove(this);
}

Client* Order::get_client(){
    return client;
}

std::string Order::get_description() {
    return description;
}

int Order::set_description(std::string description) {
    if (description.size()) {
        this->description = description;
        return 1;
    }
    return 0;
}

std::string Order::get_collection_point() {
    return collection_point;
}

int Order::set_collection_point(std::string collection_point) {
    if (collection_point.size()) {
        this->collection_point = collection_point;
        return 1;
    }
    return 0;
}

std::string Order::get_delivery_point() {
    return delivery_point;
}

int Order::set_delivery_point(std::string delivery_point) {
    if (delivery_point.size()) {
        this->delivery_point = delivery_point;
        return 1;
    }
    return 0;
}

int Order::get_weight() {
    return weight;
}

int Order::set_weight(int weight) {
    if (weight > 0) {
        this->weight = weight;
        return 1;
    }
    return 0;
}

int Order::get_size() {
    return size;
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
}

void Order::remove_vehicle(Vehicle* vehicle) {
    this->vehicles.remove(vehicle);
}

void Order::clear_list_vehicle() {
    this->vehicles.clear();
}
