#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <list>
#include "Order.hpp"

class Order;

class Client {
private:
    // Class list variables
    static std::list<Client*> instances;
    static int prox_id;

    // New objects variables
    int id;
    std::string name;
    std::string cpf;
    std::string adress;
    std::string phone;
    std::string email;
    std::list<Order*> orders;

    // Function to map oject in the list
    void increment_id();

public:
    // A list for all new clients
    static std::list<Client*>& get_instances();

    // Constructor and deconstructor
    Client(std::string name, std::string cpf, std::string adress, std::string phone, std::string email);
    ~Client();

    // Getters
    int get_id() const;
    std::string get_name() const;
    std::string get_cpf() const;
    std::string get_adress() const;
    std::string get_phone() const;
    std::string get_email() const;

    // Setters
    int set_name(std::string name);
    int set_cpf(std::string cpf);
    int set_adress(std::string adress);
    int set_phone(std::string phone);
    int set_email(std::string email);

    // Operators for cout and ==
    bool operator==( const Client& other);
    friend std::ostream& operator<<( std::ostream& os, const Client& obj);

    // List atualization
    void add_order(Order *order);
    void delete_order(Order *order);
    void delete_orders();
};

#endif
