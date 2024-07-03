from geopy import Point
from geopy.distance import geodesic

from transportadora.components.coordinates import Coordinates
from transportadora.components.vehicles.vehicle import Vehicle
from transportadora.components.component_manager import Component_Manager

class Garage(Component_Manager):
    """
    Classe Garage para gerenciar garagens que contêm veículos e suas coordenadas.
    """
    _instances = []
    _object_count = 0

    def __init__(self, lat: float, lng: float, vehicles: list[Vehicle] = [], address: str = "") -> None:
        """
        Inicializa uma nova instância da classe Garage.

        Args:
            lat (float): Latitude da localização da garagem.
            lng (float): Longitude da localização da garagem.
            vehicles (list[Vehicle], opcional): Lista de veículos na garagem. Default é uma lista vazia.
            address (str, opcional): Endereço da garagem. Default é uma string vazia.

        Raises:
            ValueError: Se lat ou lng não forem fornecidos.
            TypeError: Se vehicles não for uma lista.
        """
        if not lat or not lng:
            raise ValueError("Latitude e longitude são obrigatórias.")
        
        self._coordinates = Coordinates(lat, lng, address)

        if not isinstance(vehicles, list):
            raise TypeError("Vehicles deve ser uma lista.")
        self._vehicles = vehicles

        self.__class__._object_count += 1
        self._id = self.__class__._object_count

        self.__class__._instances.append(self)
    
    @property
    def coordinates(self) -> Coordinates:
        """
        Retorna as coordenadas da garagem.

        Returns:
            Coordinates: As coordenadas da garagem.
        """
        return self._coordinates
    
    @coordinates.setter
    def coordinates(self, coordinates: Coordinates) -> None:
        """
        Define as coordenadas da garagem.

        Args:
            coordinates (Coordinates): As novas coordenadas da garagem.

        Raises:
            TypeError: Se coordinates não for uma instância de Coordinates.
        """
        if not isinstance(coordinates, Coordinates):
            raise TypeError("coordinates deve ser uma instância de Coordinates.")
        self._coordinates = coordinates
    
    @property
    def vehicle(self) -> list:
        """
        Retorna uma cópia da lista de veículos na garagem.

        Returns:
            list: Lista de veículos na garagem.
        """
        return self._vehicles.copy()

    @vehicle.setter
    def vehicle(self, vehicles: list[Vehicle]) -> None:
        """
        Define a lista de veículos na garagem.

        Args:
            vehicles (list[Vehicle]): Lista de veículos.

        Raises:
            TypeError: Se qualquer item na lista não for uma instância de Vehicle.
        """
        if not all(isinstance(v, Vehicle) for v in vehicles):
            raise TypeError("Todos os itens da lista devem ser instâncias de Vehicle.")
        self._vehicles = vehicles

    def add_vehicle(self, vehicle: Vehicle) -> None:
        """
        Adiciona um veículo à garagem.

        Args:
            vehicle (Vehicle): Veículo a ser adicionado.

        Raises:
            TypeError: Se vehicle não for uma instância de Vehicle.
        """
        if not isinstance(vehicle, Vehicle):
            raise TypeError("O veículo deve ser uma instância de Vehicle.")
        self._vehicles.append(vehicle)

    def remove_vehicle(self, vehicle: Vehicle) -> None:
        """
        Remove um veículo da garagem.

        Args:
            vehicle (Vehicle): Veículo a ser removido.

        Raises:
            ValueError: Se o veículo não estiver na lista de veículos.
        """
        if vehicle not in self._vehicles:
            raise ValueError(f"{vehicle} não está na lista de veículos.")
        self._vehicles.remove(vehicle)
    
    def find_by_proximity(self, coordinates: Coordinates, distance: int) -> list[Vehicle]:
        """
        Encontra veículos dentro de uma determinada distância das coordenadas fornecidas.

        Args:
            coordinates (Coordinates): As coordenadas a serem usadas como ponto de referência.
            distance (int): A distância máxima (em quilômetros) para encontrar veículos.

        Returns:
            list[Vehicle]: Lista de veículos encontrados dentro da distância especificada.
        """
        vehicles = []
        for vehicle in self.vehicle:
            if geodesic(vehicle.coordinates, coordinates).kilometers < distance:
                vehicles.append(vehicle)
        return vehicles
    

    def find_vehicle_by(self, value, attribute_name):
        """
        Encontra um vehicle pelo valor de um atributo específico.

        Args:
            value: O valor do atributo a ser procurado.
            attribute_name (str): O nome do atributo a ser procurado.

        Returns:
            object: A instância encontrada, ou None se não for encontrada.
        """
        return next((vehicle for vehicle in self._vehicles if getattr(vehicle, attribute_name) == value), None)
