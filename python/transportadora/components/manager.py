import csv
from geopy.distance import distance

from transportadora.components.component_manager import Component_Manager
from transportadora.components.garage import Garage
from transportadora.components.order import *


class Manager(Component_Manager):
    """
    Classe Manager para gerenciar pedidos e veículos em uma garagem.
    """
    _instances = []
    _object_count = 0

    def __init__(self, garage: Garage) -> None:
        """
        Inicializa uma nova instância da classe Manager.

        Args:
            garage (Garage): A garagem associada ao gerente.

        Raises:
            TypeError: Se garage não for uma instância de Garage.
        """
        if not isinstance(garage, Garage):
            raise TypeError('garage deve ser uma instância de Garage')
        self.garage = garage

        self._orders = []
        self._orders_fulfilled = []

        self.__class__._object_count += 1
        self._id = self.__class__._object_count

        self.__class__._instances.append(self)

    @property
    def orders(self) -> list:
        """
        Retorna uma cópia da lista de pedidos pendentes.

        Returns:
            list: Lista de pedidos pendentes.
        """
        return self._orders.copy()

    @orders.setter
    def orders(self, orders: list[Order]) -> None:
        """
        Define a lista de pedidos pendentes.

        Args:
            orders (list[Order]): Lista de pedidos.

        Raises:
            TypeError: Se qualquer item na lista não for uma instância de Order.
        """
        if not all(isinstance(order, Order) for order in orders):
            raise TypeError("Todos os itens da lista devem ser instâncias de Order")
        self._orders = orders

    @property
    def orders_fulfilled(self) -> list:
        """
        Retorna uma cópia da lista de pedidos atendidos.

        Returns:
            list: Lista de pedidos atendidos.
        """
        return self._orders_fulfilled.copy()

    @orders_fulfilled.setter
    def orders_fulfilled(self, orders: list[Order]) -> None:
        """
        Define a lista de pedidos atendidos.

        Args:
            orders (list[Order]): Lista de pedidos atendidos.

        Raises:
            TypeError: Se qualquer item na lista não for uma instância de Order.
        """
        if not all(isinstance(order, Order) for order in orders):
            raise TypeError("Todos os itens da lista devem ser instâncias de Order")
        self._orders_fulfilled = orders


    def read_orders( self, filename : str) -> list:
        with open(filename, mode='r', newline='', encoding='utf-8') as file:
            csv_reader = csv.reader(file)

            header = next(csv_reader)  # Lê o cabeçalho se existir

            for index, row in enumerate(csv_reader):
                print(index)
                name = row[0]
                cpf = row[1]
                
                phone_number = row[3]
                email = row[4]
                collect_point = row[5]
                droppoff_point = row[6]
                weigth = int(row[7])
                volume = int(row[8])
                priority = row[9] == "sim"

                

                client = Client(name, cpf, phone_number, email)

                order = Order(client, collect_point, droppoff_point, weigth, volume, priority)
                print(f'Pedido {order} criado')
                
                self.add_order(order)


    def add_order(self, order: Order) -> None:
        """
        Adiciona um pedido à lista de pedidos pendentes.

        Args:
            order (Order): Pedido a ser adicionado.

        Raises:
            TypeError: Se order não for uma instância de Order.
        """
        if not isinstance(order, Order):
            raise TypeError("order deve ser uma instância de Order")
        self._orders.append(order)

    def remove_order(self, order: Order) -> None:
        """
        Remove um pedido da lista de pedidos pendentes.

        Args:
            order (Order): Pedido a ser removido.
        """
        self._orders.remove(order)

    def fulfill_orders(self, distance: int = 1000, n_vehicles: int = 1, limit: int = 10) -> None:
        """
        Atende os pedidos com base na proximidade dos veículos disponíveis na garagem.

        Args:
            distance (int, opcional): Distância máxima para considerar veículos disponíveis. Default é 1000 km.
            n_vehicles (int, opcional): Número inicial de veículos para tentar atender um pedido. Default é 1.
            limit (int, opcional): Limite superior de veículos a serem utilizados para atender um pedido. Default é 10.
        """
        priority_orders = sorted([order for order in self._orders if order.priority], key=lambda order: order.load_weight)

        for order in priority_orders:
            vehicles = [vehicle for vehicle in self.garage.find_by_proximity(order.collection_point, distance) if vehicle.available]

            n = n_vehicles

            while not order.is_fulfilled():
                filtered_vehicles = [vehicle for vehicle in vehicles if vehicle.load_capacity >= order.load_weight / n]

                if filtered_vehicles:
                    filtered_vehicles.sort(key=lambda vehicle: vehicle.load_capacity)
                    vehicle = filtered_vehicles[0]
                    order.add_vehicle(vehicle, order.load_weight / n, order.load_volume / n)
                else:
                    n += 1
                    if n > limit:
                        break

            if order.is_fulfilled():
                print(f'<Pedido {order.id} atendido>')
                self._orders.remove(order)
                self._orders_fulfilled.append(order)
            else:
                print(f'<Pedido {order.id} não atendido>')

        orders = sorted([order for order in self._orders if not order.priority], key=lambda order: order.load_weight)

        for order in orders:
            vehicles = [vehicle for vehicle in self.garage.find_by_proximity(order.collection_point, distance) if vehicle.available]

            n = n_vehicles

            while not order.is_fulfilled():
                filtered_vehicles = [vehicle for vehicle in vehicles if vehicle.load_capacity >= order.load_weight / n]

                if filtered_vehicles:
                    filtered_vehicles.sort(key=lambda vehicle: vehicle.load_capacity)
                    vehicle = filtered_vehicles[0]
                    vehicle.fulfill_order(order, order.load_weight / n, order.load_volume / n)
                else:
                    n += 1
                    if n > limit:
                        break

            if order.is_fulfilled():
                print(f'<Pedido {order.id} atendido>')
                self._orders.remove(order)
                self._orders_fulfilled.append(order)
            else:
                print(f'<Pedido {order.id} não atendido>')
