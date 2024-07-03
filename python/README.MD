# Transportadora

## Descrição do Projeto

Este projeto é uma simulação de uma transportadora que gerencia pedidos, veículos e garagens, com funcionalidades para adicionar, remover e encontrar veículos, bem como gerenciar pedidos e sua execução. O projeto é escrito em Python e utiliza uma abordagem orientada a objetos.

## Estrutura do Projeto

### Classes Principais

1. **Component_Manager**
2. **Coordinates**
3. **Vehicle**
4. **Garage**
5. **Manager**
6. **Order**
7. **Client**

### Descrição das Classes

#### 1. Component_Manager

A classe `Component_Manager` serve como uma classe base para gerenciar instâncias de componentes. Ela mantém uma lista de todas as instâncias criadas e fornece métodos para buscar instâncias por ID e por atributos.

- **Atributos:**
  - `_instances`: Lista de instâncias.
  - `_object_count`: Contador de objetos.

- **Métodos:**
  - `find_by_id(cls, value)`: Encontra uma instância pelo ID.
  - `find_by(cls, value, attribute_name)`: Encontra uma instância pelo valor de um atributo.
  - `all(cls)`: Retorna todas as instâncias.
  - `__del__()`: Remove a instância da lista de instâncias ao ser deletada.

#### 2. Coordinates

A classe `Coordinates` representa coordenadas geográficas (latitude e longitude) e um endereço. Ela inclui um método estático para obter coordenadas de um endereço utilizando uma API de geocodificação.

- **Atributos:**
  - `latitude`: Latitude das coordenadas.
  - `longitude`: Longitude das coordenadas.
  - `address`: Endereço das coordenadas.

- **Métodos:**
  - `__init__(latitude, longitude, address="")`: Inicializa uma instância de coordenadas.
  - `get_coordinates(address)`: Obtém as coordenadas de um endereço fornecido.

#### 3. Vehicle

A classe `Vehicle` representa um veículo na frota da transportadora. Ela armazena informações sobre a capacidade de carga do veículo e sua disponibilidade.

- **Atributos:**
  - `load_capacity`: Capacidade de carga do veículo.
  - `available`: Disponibilidade do veículo.

- **Métodos:**
  - `fulfill_order(weight, order)`: Cumpre um pedido atribuído ao veículo.
  - `finish_order(order)`: Finaliza um pedido atribuído ao veículo.

#### 4. Garage

A classe `Garage` representa uma garagem que contém veículos. Ela gerencia a adição e remoção de veículos, bem como a busca de veículos por proximidade.

- **Atributos:**
  - `_coordinates`: Coordenadas da garagem.
  - `_vehicles`: Lista de veículos na garagem.

- **Métodos:**
  - `__init__(lat, lng, vehicles=[], address="")`: Inicializa uma garagem com coordenadas e veículos.
  - `add_vehicle(vehicle)`: Adiciona um veículo à garagem.
  - `remove_vehicle(vehicle)`: Remove um veículo da garagem.
  - `find_by_proximity(coordinates, distance)`: Encontra veículos dentro de uma distância específica.

#### 5. Manager

A classe `Manager` gerencia uma garagem e seus pedidos. Ela adiciona, remove e cumpre pedidos utilizando os veículos disponíveis na garagem.

- **Atributos:**
  - `garage`: Garagem gerenciada pelo manager.
  - `_orders`: Lista de pedidos.
  - `_orders_fulfilled`: Lista de pedidos cumpridos.

- **Métodos:**
  - `__init__(garage)`: Inicializa um manager com uma garagem.
  - `add_order(order)`: Adiciona um pedido à lista de pedidos.
  - `remove_order(order)`: Remove um pedido da lista de pedidos.
  - `fulfill_orders(distance=1000, n_vehicles=1, limit=10)`: Cumpre os pedidos utilizando veículos dentro de uma distância específica.

#### 6. Order

A classe `Order` representa um pedido feito por um cliente. Ela armazena informações sobre o ponto de coleta, ponto de entrega, peso da carga, volume da carga e prioridade do pedido.

- **Atributos:**
  - `client`: Cliente que fez o pedido.
  - `collection_point`: Ponto de coleta das coordenadas.
  - `dropoff_point`: Ponto de entrega das coordenadas.
  - `load_weight`: Peso da carga do pedido.
  - `load_volume`: Volume da carga do pedido.
  - `priority`: Prioridade do pedido.
  - `description`: Descrição do pedido.
  - `status`: Status do pedido.
  - `_vehicles`: Lista de veículos atribuídos ao pedido.

- **Métodos:**
  - `__init__(client, collect_point, dropoff_point, load_weight, load_volume, priority=0, description="")`: Inicializa um pedido com os detalhes fornecidos.
  - `add_vehicle(vehicle, weight, volume)`: Adiciona um veículo ao pedido.
  - `remove_vehicle(vehicle)`: Remove um veículo do pedido.
  - `is_fulfilled()`: Verifica se o pedido foi cumprido.

#### 7. Client

A classe `Client` representa um cliente que faz pedidos. Ela armazena informações básicas do cliente.

- **Atributos:**
  - `name`: Nome do cliente.
  - `address`: Endereço do cliente.
  - `contact`: Informação de contato do cliente.

- **Métodos:**
  - `__init__(name, address, contact)`: Inicializa um cliente com os detalhes fornecidos.

## Execução do Projeto

Para executar este projeto, certifique-se de ter Python instalado e siga os seguintes passos:

1. Clone o repositório.
2. Instale as dependências utilizando `pip3 install -r requirements.txt`.
3. Execute o script principal para iniciar a simulação.

```bash
python3 -m transportadora
```

