#include <iostream>


using namespace std;
/*
1) Descrever a frota de veículos (carro, camionete, caminhão). Cada veículo tem suas
particularidades específicas (capacidade de carga, ano de fabricação, chassi,
modelo, localização, etc…).
2) Descrever os clientes
3) Descrever os pedidos de transportes (e.g., cliente que solicita, tipo de transporte,
local de coleta, local de entrega, peso da carga, volume da carga).

*/




class Vehicle{
    /*
    Classe base para qualquer veiculo criada a fim de conter atributos e metodos base
    */
    private:
        static int prox_id;
        int id;
        string placa;
        string chassi;
        string modelo;
        int capacidade;
        int ano;
        string adress;

        void increment_id(){
            prox_id++;
        }
    
    public:
        // Criando um construtor mais simples a fins de teste
        Vehicle (){
            this->id = prox_id;
            increment_id();
        }
        Vehicle( string placa, string chassi, string modelo, int capacidade, int ano, string adress){
            this->id = prox_id;
            increment_id();
            this->placa = placa;
            this->chassi =  chassi;
            this->modelo = modelo;
            this->capacidade = capacidade;
            this->ano = ano;
            this->adress = adress;
        }

        void set_placa( string placa){
            this->placa = placa;
        }
        string get_placa(){
            return this->placa;
        }

        void set_chassi( string chassi){
            this->chassi = chassi;
        }
        string get_chassi(){
            return this->chassi;
        }

        void set_modelo( string modelo){
            this->modelo = modelo;
        }
        string get_modelo(){
            return this->modelo;
        }

        void set_capacidade( int capacidade){
            this->capacidade = capacidade;
        }
        int get_capacidade(){
            return this->capacidade;
        }

        void set_ano( int ano){
            this->ano = ano;
        }
        int get_ano(){
            return this->ano;
        }

        void set_adress( string adress){
            this->adress = adress;
        }
        string get_adress(){
            return this->adress;
        }
        
};

int Vehicle :: prox_id = 1;

class Car : public Vehicle{
    public:
        Car() : Vehicle(){

        }
        Car( string placa, string chassi, string modelo, int capacidade, int ano, string adress) : Vehicle( placa, chassi, modelo, capacidade, ano, adress){
            // Construtor vazio até futuras implementações
        }

        
};

class Truck : public Vehicle{
    public:
        Truck() : Vehicle(){

        }
        Truck( string placa, string chassi, string modelo, int capacidade, int ano, string adress) : Vehicle( placa, chassi, modelo, capacidade, ano, adress){
            // Construtor vazio até futuras implementações
        }
};
class Pickup : public Vehicle{
    public:
        Pickup() : Vehicle(){

        }
        Pickup ( string placa, string chassi, string modelo, int capacidade, int ano, string adress) : Vehicle( placa, chassi, modelo, capacidade, ano, adress){
            // Construtor vazio até futuras implementações
        }
        
};



class Order{
    private:
        static int prox_id;         // Variavel usada pra criar id's autoincrementados e unicos
        int id;
        int order_id;
        int client_id;
        string description;
        string collection_point;
        string delivery_point;
        int weight;
        int size;

        // Os atributos a seguir sao vetores dinamicos para armazenar o endereço de veiculos associados a um pedido
        Car **fleet_of_cars;
        Pickup **fleet_of_pickups;
        Truck **fleet_of_trucks;

        void increment_id(){
            prox_id++;
        }
        

    public:
        Order( int client_id, string description, string collection_point, string delivery_point, int weight, int size){
            this->id = prox_id;
            increment_id();
            this->client_id = client_id;
            this->description = description;
            this->collection_point = collection_point;
            this->delivery_point = delivery_point;
            this->weight = weight;
            this->size = size;

            // Inicializando os ponteiros como null
            this->fleet_of_cars = nullptr;
            this->fleet_of_pickups = nullptr;
            this->fleet_of_trucks = nullptr;
        }

        int get_client_id(){
            return client_id;
        }

        void set_client_id( int id){
            this->client_id = id;
        }

        string get_description(){
            return description;
        }

        void set_description( string description){
            this->description = description;
        }

        string get_collection_point(){
            return collection_point;
        }

        void set_collection_point( string collection_point){
            this->collection_point = collection_point;
        }

        string get_delivery_point(){
            return delivery_point;
        }
        
        void set_delivery_point( string delivery_point){
            this->delivery_point = delivery_point;
        }

        int get_weight(){
            return weight;
        }

        void set_weight( int weight){
            this->weight = weight;
        }

        int get_size(){
            return size;
        }        

        void set_size( int size){
            this->size = size;
        }

        void  set_fleet_of_cars( Car *vet[], int size){
            this->fleet_of_cars = new Car*[size];

            for( int i = 0; i < size; i++){
                this->fleet_of_cars[i]= vet[i];
            }
        }
        Car** get_fleet_of_cars(){
            return this->fleet_of_cars;
        }

        void set_fleet_of_pickups( Pickup *vet[], int size){
            this->fleet_of_pickups = new Pickup*[size];

            for( int i  = 0; i<size; i++){
                this->fleet_of_pickups[i] = vet[i];
            }
        }
        Pickup** get_flee_of_pickups(){
            return this->fleet_of_pickups;
        }

        void set_fleet_of_trucks( Truck *vet[], int size){
            this->fleet_of_trucks = new Truck*[size];

            for( int i  = 0; i<size; i++){
                this->fleet_of_trucks[i] = vet[i];
            }
        }
        Truck **get_fleet_of_trucks(){
            return this->fleet_of_trucks;
        }
        
};

int Order::prox_id = 1;

class Client{
    private:
        string name;
        int cpf;
        int idade;
        Order **orders;

    public:
        Client(){
            // Vazio
        }
        Client( int cpf, string name, int idade){
            this->name = name;
            this->cpf = cpf;
            this->idade = idade;
            this->orders = nullptr;
        }

        void set_name(string name){
            this->name = name;
        }

        string get_name(){
            return this->name;
        }

        void set_cpf(int cpf){
            this->cpf = cpf;
        }

        int get_cpf(){
            return this->cpf;
        }


};

int main(){
    Car uno;
    Car **vet = new Car*[1];
    vet[0] = &uno;

    uno.set_placa("ifhrbyfbnfonell");
    uno.set_modelo("Uno com escada");

    Client cliente( 1748456743, "Pedro", 18);

    Order pedido(1, "Entrega de cafe", "Nossa senhora", "lab", 3, 1);
    pedido.set_fleet_of_cars( vet, 1);

    cout << "Pedido "<< pedido.get_description() << "sera feito por " << uno.get_modelo() << "\n";
}