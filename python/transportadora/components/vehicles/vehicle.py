from geopy import Point
from  transportadora.components.component_manager import Component_Manager
from transportadora.components.coordinates import*

class Vehicle(Component_Manager):
    """
    Classe Vehicle para gerenciar veículos com informações como placa, chassi, modelo, capacidade de carga, ano e localização.
    """

    _instances = []
    _object_count = 0

    def __init__(self, license_plate: str = None, chassis: str = None, model: str = None, load_capacity: int = None, ano: int = None, lat: float = None, lng: float = None):
        """
        Inicializa uma nova instância da classe Vehicle.

        Args:
            license_plate (str): Placa do veículo (deve ter 8 caracteres).
            chassis (str): Chassi do veículo (deve ter 17 caracteres).
            model (str): Modelo do veículo.
            load_capacity (int): Capacidade de carga do veículo.
            ano (int): Ano do veículo (deve ser maior que 1885).
            lat (float): Latitude da localização do veículo.
            lng (float): Longitude da localização do veículo.

        Raises:
            ValueError: Se qualquer um dos parâmetros fornecidos for inválido.
        """
        self._available = True

        if not isinstance(license_plate, str) or len(license_plate) != 8:
            raise ValueError("Valor inválido para license_plate")
        self._license_plate = license_plate

        if not isinstance(chassis, str) or len(chassis) != 17:
            raise ValueError("Valor inválido para chassis")
        self._chassis = chassis

        if not isinstance(model, str):
            raise ValueError("Valor inválido para model")
        self._model = model

        if load_capacity < 1:
            raise ValueError("Valor inválido para load_capacity")
        self._load_capacity = load_capacity

        if ano < 1886:
            raise ValueError("Valor inválido para ano")
        self._ano = ano

        if not lat or not lng:
            raise ValueError("Coordenadas inválidas")
        self._coordinates = Point(lat, lng)

        self.loading = []

        self.__class__._object_count += 1
        self._id = self.__class__._object_count
        self.__class__._instances.append(self)

    @property
    def id(self):
        """Retorna o ID do veículo."""
        return self._id

    @property
    def license_plate(self):
        """Retorna a placa do veículo."""
        return self._license_plate

    @license_plate.setter
    def license_plate(self, license_plate):
        """
        Define uma nova placa para o veículo.

        Args:
            license_plate (str): Nova placa (deve ter 8 caracteres).

        Returns:
            int: 1 se a placa foi atualizada, 0 caso contrário.
        """
        if len(license_plate) == 8:
            self._license_plate = license_plate
            return 1
        return 0

    @property
    def chassis(self):
        """Retorna o chassi do veículo."""
        return self._chassis

    @chassis.setter
    def chassis(self, chassis):
        """
        Define um novo chassi para o veículo.

        Args:
            chassis (str): Novo chassi (deve ter 17 caracteres).

        Raises:
            ValueError: Se o chassi não tiver 17 caracteres.
        """
        if len(chassis) == 17:
            self._chassis = chassis
            return 
        raise ValueError

    @property
    def model(self):
        """Retorna o modelo do veículo."""
        return self._model

    @model.setter
    def model(self, model):
        """
        Define um novo modelo para o veículo.

        Args:
            model (str): Novo modelo.

        Raises:
            ValueError: Se o modelo não for uma string válida.
        """
        if model:
            self._model = model
            return 
        raise ValueError

    @property
    def load_capacity(self):
        """Retorna a capacidade de carga do veículo."""
        return self._load_capacity

    @load_capacity.setter
    def load_capacity(self, load_capacity):
        """
        Define uma nova capacidade de carga para o veículo.

        Args:
            load_capacity (int): Nova capacidade de carga (deve ser maior que 0).

        Raises:
            ValueError: Se a capacidade de carga for menor ou igual a 0.
        """
        if load_capacity > 0:
            self._load_capacity = load_capacity
            return 
        raise ValueError

    @property
    def year(self):
        """Retorna o ano do veículo."""
        return self._year

    @year.setter
    def year(self, ano):
        """
        Define um novo ano para o veículo.

        Args:
            ano (int): Novo ano (deve ser maior que 1885).

        Raises:
            ValueError: Se o ano for menor ou igual a 1885.
        """
        if ano > 1885:
            self._year = ano
            return 
        raise ValueError
    

    @property
    def coordinates(self) -> Coordinates:
        return self._coordinates
    
    
    @coordinates.setter
    def coordinates(self, coordinates : Coordinates) -> None:
        if not isinstance(coordinates, Coordinates):
            raise TypeError("Valor passado deve ser da classe Coordinates")
        self._coordinates = coordinates

    def fulfill_order(self, order, load_weight: int, volume: int):
        """
        Atualiza o estado do veículo para cumprir um pedido.

        Args:
            order: Pedido a ser cumprido.
            load_weight (int): Peso da carga do pedido.
            volume (int): Volume da carga do pedido.

        Adiciona o pedido à lista de carregamento e atualiza a capacidade de carga do veículo.
        """
        self.loading.append({'order': order, 'load_weight': load_weight, 'load_volume': volume})
        self._load_capacity -= load_weight
    
        if self.load_capacity <= 0:
            self.available = False

    def finish_order(self, order) -> None:
        """
        Finaliza um pedido e libera a capacidade de carga do veículo.

        Args:
            order: Pedido a ser finalizado.

        Remove o pedido da lista de carregamento e atualiza a capacidade de carga do veículo.
        """
        for p in self.loading:
            if p['order'] == order:
                self.load_capacity += p['load_weight']
                self.loading.remove(p)

    @property
    def available(self):
        """Retorna a disponibilidade do veículo."""
        return self._available

    @available.setter
    def available(self, status):
        """
        Define a disponibilidade do veículo.

        Args:
            status (bool): Novo status de disponibilidade.

        Raises:
            ValueError: Se o status não for um valor booleano.
        """
        if not isinstance(status, bool):
            raise ValueError("Status inválido")
        self._available = status

    def __eq__(self, other):
        """
        Verifica a igualdade entre dois veículos com base no ID.

        Args:
            other: Outro veículo a ser comparado.

        Returns:
            bool: True se os veículos tiverem o mesmo ID, False caso contrário.
        """
        return self.id == other.id

    def __str__(self):
        """Retorna uma representação em string do veículo."""
        return f"{self.model} / license_plate {self.license_plate}"
    
    def __repr__(self) -> str:
        return self.__str__()


    def __del__(self) -> None:
        """Remove a instância do veículo da lista de instâncias."""
        self.__class__._instances.remove(self)
