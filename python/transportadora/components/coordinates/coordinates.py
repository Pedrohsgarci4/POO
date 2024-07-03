from geopy.distance import geodesic
from geopy.point import Point
from random import uniform
import requests

class Coordinates:
    """
    Classe Coordinates para gerenciar coordenadas geográficas, incluindo latitude, longitude e endereço associado.
    """

    reference_point = Point(0, 0)  # Define um ponto de referência padrão

    def __init__(self, lat, lng, address) -> None:
        """
        Inicializa uma nova instância da classe Coordinates.

        Args:
            lat (float): Latitude das coordenadas.
            lng (float): Longitude das coordenadas.
            address (str): Endereço associado às coordenadas.
        """
        self.latitude = lat
        self.longitude = lng
        self._address = address

    def __iter__(self):
        """
        Permite a iteração direta para obter latitude e longitude.

        Returns:
            iter: Iterador para latitude e longitude.
        """
        return iter((self.latitude, self.longitude)) 

    def __str__(self) -> str:
        """
        Retorna uma representação em string das coordenadas.

        Returns:
            str: Representação em string das coordenadas.
        """
        return f'<Coordinates {self.address} / {self.latitude} {self.longitude} >'    

    @property
    def address(self) -> str:
        """
        Retorna o endereço associado às coordenadas.

        Returns:
            str: Endereço associado.
        """
        return self._address

    @address.setter
    def address(self, address: str) -> None:
        """
        Define um novo endereço para as coordenadas.

        Args:
            address (str): Novo endereço.

        Raises:
            TypeError: Se o endereço não for uma string.
        """
        if not isinstance(address, str):
            raise TypeError("Address must be a string")
        self._address = address

    @classmethod
    def random_coordinates(cls, address: str) -> object:
        """
        Gera coordenadas aleatórias próximas ao ponto de referência.

        Args:
            address (str): Endereço associado às coordenadas geradas.

        Returns:
            Coordinates: Instância da classe Coordinates com coordenadas aleatórias.
        """
        point = geodesic(meters=1000).destination(cls.reference_point, uniform(0, 360))
        lat = point.latitude
        lng = point.longitude
        return cls(lat, lng, address)  

    @classmethod
    def get_coordinates(cls, address):
        """
        Obtém coordenadas geográficas para um endereço específico usando o Google Maps.

        Args:
            address (str): Endereço para o qual obter as coordenadas.

        Returns:
            Coordinates: Instância da classe Coordinates com as coordenadas obtidas ou aleatórias em caso de falha.
        """
        try:
            url = f'https://www.google.com/maps/?q={address.replace(" ", "+").replace("/", "+")}'
            response = requests.get(url)
    
            if response.status_code == 200:
                content = response.text
                start = content.find('?center=') + len('?center=')
                end = content.find('&amp;zoom', start)
    
                if start != -1 and end != -1:
                    coordinates = content[start:end].replace('%2C', ' ').split(' ')
    
                    lat, lng = map(float, coordinates)
                    return cls(lat, lng, address)
        except:
            pass

        return cls.random_coordinates(address)
