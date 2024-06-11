#include "../include/Order.hpp"
#include <stdexcept>

std::list<Order*> Order::instances;
int Order::prox_id = 1;

void Order::increment_id() {
    prox_id++;
}

Order::Order(int client_id,  Coordinates collection_point, Coordinates delivery_point, float weight, float volume, std::string priority) {
    this->id = prox_id;
    increment_id();

    this->client = nullptr;
    for (Client *client : Client::get_instances())
    {
        if (client->get_id() == client_id)
        {
            this->client = client;
            client->add_order(this);
            break;
        }
    }

    this->collection_point = collection_point;
    this->delivery_point = delivery_point;

    if (weight <= 0)
        throw std::invalid_argument("Valor inválido para peso");
    this->weight = weight;

    if (volume <= 0)
        throw std::invalid_argument("Valor inválido para volume");
    this->volume = volume;

    if (priority != "sim" || priority != "não")
        throw std::invalid_argument("Valor inválido para prioridade");
    this->priority = priority;

    instances.push_back(this);
}

Order::~Order() {
    Client* c = this->get_client();
    if (c != nullptr) c->delete_order(this);
    instances.remove(this);
}

int Order::get_id() const { return this->id; }

Client* Order::get_client() const { return client; }

Coordinates Order::get_collection_point() const { return collection_point; }
Coordinates Order::get_collection_point() const { return collection_point; }

Coordinates Order::get_delivery_point() const { return delivery_point; }
Coordinates Order::get_delivery_point() const { return delivery_point; }

float Order::get_weight() const { return this->weight; }

float Order::get_volume() const { return volume; }



int Order::set_collection_point(double lat, double lng) {
    this->collection_point.set_coordinates( lat, lng);
    return 1;
}



int Order::set_delivery_point( double lat, double lng) {
    this->delivery_point.set_coordinates( lat, lng);
    return 1;
}


int Order::set_weight(float weight) {
    if (weight > 0) {
        this->weight = weight;
        return 1;
    }
    return 0;
}

int Order::set_volume(float volume) {
    if (volume > 0) {
        this->volume = volume;
        return 1;
    }
    return 0;
}

int Order::set_priority(std::string priority)
{
    if (priority == "sim" || priority == "não")
    {
        this->priority = priority;
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

