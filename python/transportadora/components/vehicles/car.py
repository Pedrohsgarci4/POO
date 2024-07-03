from  transportadora.components.vehicles.vehicle import Vehicle

class Car(Vehicle):
    """
    Classe Car para gerenciar carros, herdando da classe Vehicle.
    """
    _instances = []

    def __init__(self, placa: str = None, chassi: str = None, modelo: str = None, capacidade: int = None, ano: int = None, lat: float = None, lng: float = None):
        """
        Inicializa uma nova instância da classe Car.

        Args:
            placa (str): Placa do carro (deve ter 8 caracteres).
            chassi (str): Chassi do carro (deve ter 17 caracteres).
            modelo (str): Modelo do carro.
            capacidade (int): Capacidade de carga do carro.
            ano (int): Ano do carro (deve ser maior que 1885).
            lat (float): Latitude da localização do carro.
            lng (float): Longitude da localização do carro.

        Raises:
            ValueError: Se qualquer um dos parâmetros fornecidos for inválido.
        """
        super().__init__(placa, chassi, modelo, capacidade, ano, lat, lng)  
