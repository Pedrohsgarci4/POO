from transportadora.components.vehicles.vehicle import Vehicle

class Truck(Vehicle):
    """
    Classe Truck para gerenciar caminhões, herdando da classe Vehicle.
    """
    _instances = []

    def __init__(self, placa: str = None, chassi: str = None, modelo: str = None, capacidade: int = None, ano: int = None, lat: float = None, lng: float = None):
        """
        Inicializa uma nova instância da classe Truck.

        Args:
            placa (str): Placa do caminhão (deve ter 8 caracteres).
            chassi (str): Chassi do caminhão (deve ter 17 caracteres).
            modelo (str): Modelo do caminhão.
            capacidade (int): Capacidade de carga do caminhão.
            ano (int): Ano do caminhão (deve ser maior que 1885).
            lat (float): Latitude da localização do caminhão.
            lng (float): Longitude da localização do caminhão.

        Raises:
            ValueError: Se qualquer um dos parâmetros fornecidos for inválido.
        """
        super().__init__(placa, chassi, modelo, capacidade, ano, lat, lng)
        self.__class__._instances.append(self)

