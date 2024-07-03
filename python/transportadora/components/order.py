from transportadora.components.coordinates import Coordinates
from transportadora.components.client import Client
from transportadora.components.component_manager import Component_Manager
from transportadora.components.vehicles.vehicle import Vehicle

class Order(Component_Manager):
    """
    Classe Order para gerenciar pedidos de transporte.
    """
    _instances = []
    _object_count = 0

    def __init__(
            self,
            client: Client,
            collect_point: str,
            dropoff_point: str,
            load_weight: int,
            load_volume: int,
            priority: int = 0,
            description: str = ""
    ) -> None:
        """
        Inicializa uma nova instância da classe Order.

        Args:
            client (Client): Cliente associado ao pedido.
            collect_point (str): Ponto de coleta do pedido.
            dropoff_point (str): Ponto de entrega do pedido.
            load_weight (int): Peso da carga.
            load_volume (int): Volume da carga.
            priority (int, opcional): Prioridade do pedido. Default é 0.
            description (str, opcional): Descrição do pedido. Default é "".

        Raises:
            TypeError: Se client não for uma instância de Client.
            ValueError: Se load_weight ou load_volume forem menores que 0.
        """
        if not isinstance(client, Client):
            raise TypeError("client deve ser uma instância de Client")
        self._client = client

        self._collection_point = Coordinates.get_coordinates(collect_point)
        self._dropoff_point = Coordinates.get_coordinates(dropoff_point)

        if load_volume < 0:
            raise ValueError("load_volume deve ser maior ou igual a 0")
        self._load_volume = load_volume

        if load_weight < 0:
            raise ValueError("load_weight deve ser maior ou igual a 0")
        self._load_weight = load_weight

        self.priority = priority
        self.description = description
        self.status = "create"
        self._vehicles = []

        self.__class__._object_count += 1
        self._id = self.__class__._object_count
        self.__class__._instances.append(self)

    @property
    def id(self):
        """
        Retorna o ID do pedido.

        Returns:
            int: ID do pedido.
        """
        return self._id

    @property
    def client(self) -> Client:
        """
        Retorna o cliente associado ao pedido.

        Returns:
            Client: Cliente associado ao pedido.
        """
        return self._client

    @client.setter
    def client(self, value: Client) -> None:
        """
        Define o cliente associado ao pedido.

        Args:
            value (Client): Novo cliente para o pedido.

        Raises:
            TypeError: Se value não for uma instância de Client.
        """
        if not isinstance(value, Client):
            raise TypeError("client deve ser uma instância de Client")
        self._client = value

    @property
    def collection_point(self) -> Coordinates:
        """
        Retorna o ponto de coleta do pedido.

        Returns:
            Coordinates: Ponto de coleta do pedido.
        """
        return self._collection_point

    @collection_point.setter
    def collection_point(self, value: str) -> None:
        """
        Define o ponto de coleta do pedido.

        Args:
            value (str): Novo ponto de coleta.
        """
        self._collection_point = Coordinates.get_coordinates(value)

    @property
    def dropoff_point(self) -> Coordinates:
        """
        Retorna o ponto de entrega do pedido.

        Returns:
            Coordinates: Ponto de entrega do pedido.
        """
        return self._dropoff_point

    @dropoff_point.setter
    def dropoff_point(self, value: str) -> None:
        """
        Define o ponto de entrega do pedido.

        Args:
            value (str): Novo ponto de entrega.
        """
        self._dropoff_point = Coordinates.get_coordinates(value)

    @property
    def load_weight(self) -> int:
        """
        Retorna o peso da carga do pedido.

        Returns:
            int: Peso da carga do pedido.
        """
        return self._load_weight

    @load_weight.setter
    def load_weight(self, value: int) -> None:
        """
        Define o peso da carga do pedido.

        Args:
            value (int): Novo peso da carga.

        Raises:
            ValueError: Se value for menor que 0.
        """
        if value < 0:
            raise ValueError("load_weight deve ser maior ou igual a 0")
        self._load_weight = value

    @property
    def load_volume(self) -> int:
        """
        Retorna o volume da carga do pedido.

        Returns:
            int: Volume da carga do pedido.
        """
        return self._load_volume

    @load_volume.setter
    def load_volume(self, value: int) -> None:
        """
        Define o volume da carga do pedido.

        Args:
            value (int): Novo volume da carga.

        Raises:
            ValueError: Se value for menor que 0.
        """
        if value < 0:
            raise ValueError("load_volume deve ser maior ou igual a 0")
        self._load_volume = value

    @property
    def priority(self) -> int:
        """
        Retorna a prioridade do pedido.

        Returns:
            int: Prioridade do pedido.
        """
        return self._priority

    @priority.setter
    def priority(self, value: int) -> None:
        """
        Define a prioridade do pedido.

        Args:
            value (int): Nova prioridade do pedido.
        """
        self._priority = value

    @property
    def vehicles(self):
        """
        Retorna a lista de veículos associados ao pedido.

        Returns:
            list: Lista de veículos associados ao pedido.
        """
        return self._vehicles.copy()

    @vehicles.deleter
    def vehicles(self):
        """
        Remove todos os veículos associados ao pedido.
        """
        for vehicle in self._vehicles:
            vehicle.finish_order(self)

    def is_fulfilled(self) -> bool:
        """
        Verifica se o pedido foi atendido.

        Returns:
            bool: True se o pedido foi atendido, False caso contrário.
        """
        return self.load_weight <= 0

    def add_vehicle(self, vehicle: Vehicle, weight: int, volume: int):
        """
        Adiciona um veículo ao pedido.

        Args:
            vehicle (Vehicle): Veículo a ser adicionado.
            weight (int): Peso da carga a ser transportada pelo veículo.
            volume (int): Volume da carga a ser transportada pelo veículo.

        Raises:
            TypeError: Se vehicle não for uma instância de Vehicle.
        """
        if not isinstance(vehicle, Vehicle):
            raise TypeError("vehicle deve ser uma instância de Vehicle")

        self._vehicles.append(vehicle)
        vehicle.fulfill_order(self, weight, volume)

        self.load_weight -= weight
        self.load_volume -= volume

        if self.load_weight <= 0:
            self.status = "fulfilled"

    def remove_vehicle(self, vehicle) -> None:
        """
        Remove um veículo do pedido.

        Args:
            vehicle (Vehicle): Veículo a ser removido.
        """
        if vehicle not in self._vehicles:
            return
        self._vehicles.remove(vehicle)
        vehicle.finish_order(self)

    def __str__(self):
        """
        Retorna uma string representando o pedido.

        Returns:
            str: Representação do pedido.
        """
        return f'Order id/{self.id}-status/{self.status}-client/{self.client.name}-collection_point/{self.collection_point.address}-dropoff_point/{self.dropoff_point.address}'
