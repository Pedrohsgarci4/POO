#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <list>
#include "Order.hpp"

class Order;

class Client {
private:
    static std::list<Client*> instances;
    static int prox_id;

    int id;
    std::string name;
    std::string cpf;
    int idade;
    std::list<Order*> orders;

    void increment_id();

public:
    static std::list<Client*>& get_instances();

    Client(std::string cpf, std::string name, int idade);
    ~Client();

    int get_id();

    int set_name(std::string name);
    std::string get_name();

    int set_cpf(std::string cpf);
    std::string get_cpf();

    bool operator==( const Client& other);
    friend std::ostream& operator<<( std::ostream& os, const Client& obj);

    void add_order(Order *order);
    void delete_order(Order *order);
    void delete_orders();
};

#endif
