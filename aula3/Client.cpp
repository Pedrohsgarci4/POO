#include "Client.hpp"
#include <stdexcept>


std::list<Client*> Client::instances;
int Client::prox_id = 0;

void Client::increment_id() {
    prox_id++;
}

std::list<Client*>& Client::get_instances() {
    return instances;
}

Client::Client(std::string cpf, std::string name, int idade) {
    if (cpf.size() != 14) {
        throw std::invalid_argument("CPF inválido");
    }
    this->cpf = cpf;

    if (name.empty()) {
        throw std::invalid_argument("Nome inválido");
    }
    this->name = name;

    if (idade < 17) {
        throw std::invalid_argument("Idade inválida");
    }
    this->idade = idade;

    this->id = prox_id;

    increment_id();

    instances.push_back(this);
}

Client::~Client() {
    instances.remove(this);
}

int Client::get_id() {
    return this->id;
}

int Client::set_name(std::string name) {
    if (!name.empty()) {
        this->name = name;
        return 1;
    }
    return 0;
}

std::string Client::get_name() {
    return this->name;
}

int Client::set_cpf(std::string cpf) {
    if (cpf.size() == 14) {
        this->cpf = cpf;
        return 1;
    }
    return 0;
}

std::string Client::get_cpf() {
    return this->cpf;
}

bool Client::operator==( const Client& other){
    return ( this->cpf == other.cpf) && (this->id == other.id);
}

std::ostream& operator<<( std::ostream& os, const Client& obj){
    os << "Cliente " << obj.name << " de CPF " << obj.cpf;
    return os;
}


void Client::add_order(Order* order) {
    this->orders.push_back(order);
}

void Client::delete_order(Order* order) {
    this->orders.remove(order);
}

void Client::delete_orders() {
    this->orders.clear();
}
