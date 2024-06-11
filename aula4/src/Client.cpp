#include "../include/Client.hpp"
#include <stdexcept>

// ###############################
// class list variables definition
// ###############################

std::list<Client*> Client::instances;
int Client::prox_id = 0;

void Client::increment_id() { prox_id++; }

std::list<Client*>& Client::get_instances(){ return instances; }

// ######################
// Constructor definition
// ######################

Client::Client(std::string name, std::string cpf, std::string adress, std::string phone, std::string email)
{
    if (cpf.size() != 14) { throw std::invalid_argument("CPF inválido"); }
    this->cpf = cpf;

    if (name.empty()) { throw std::invalid_argument("Nome inválido"); }
    this->name = name;

    if (adress.empty()) { throw std::invalid_argument("Endereco inválido"); }
    this->adress = adress;

    if (phone.empty()) { throw std::invalid_argument("Telefone inválido"); }
    this->phone = phone;

    if (email.empty()) { throw std::invalid_argument("E-mail inválido"); }
    this->email = email;

    this->id = prox_id;

    increment_id();

    instances.push_back(this);
}

// #############################################################
// More list functions and variables definitions and alterations
// #############################################################

Client::~Client() { instances.remove(this); }

int Client::get_id() const { return this->id; }

// ###################
// Getters and Setters
// ###################

int Client::set_name(std::string name)
{
    if (!name.empty()) {
        this->name = name;
        return 1;
    }
    return 0;
}
std::string Client::get_name() const { return this->name; }

int Client::set_cpf(std::string cpf) {
    if (cpf.size() == 14) {
        this->cpf = cpf;
        return 1;
    }
    return 0;
}
std::string Client::get_cpf() const { return this->cpf; }

int Client::set_adress(std::string adress)
{
    if (!adress.empty())
    {
        this->adress = adress;
        return 1;
    }
    return 0;
}
std::string Client::get_adress() const { return this->adress; }

int Client::set_phone(std::string phone)
{
    if (!phone.empty())
    {
        this->phone = phone;
        return 1;
    }
    return 0;
}
std::string Client::get_phone() const { return this->phone; }

int Client::set_email(std::string email)
{
    if (!email.empty())
    {
        this->email = email;
        return 1;
    }
    return 0;
}
std::string Client::get_email() const { return this->email; }

// ############################################
// operators for cout and comparison definition
// ############################################

bool Client::operator==( const Client& other){
    return ( this->cpf == other.cpf) && (this->id == other.id);
}

std::ostream& operator<<( std::ostream& os, const Client& obj){
    os << "Cliente " << obj.name << " de CPF " << obj.cpf;
    return os;
}

// ###############################
// More list functions definitions
// ###############################

void Client::add_order(Order* order) { this->orders.push_back(order); }

void Client::delete_order(Order* order) { this->orders.remove(order); }

void Client::delete_orders() { this->orders.clear(); }