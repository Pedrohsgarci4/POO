from transportadora.components.vehicles.vehicle import Vehicle

class Pickup(Vehicle):
    """
    Classe Pickup para gerenciar picapes, herdando da classe Vehicle.
    """
    _instances = []

    def __init__(self, placa: str = None, chassi: str = None, modelo: str = None, capacidade: int = None, ano: int = None, lat: float = None, lng: float = None):
        """
        Inicializa uma nova instância da classe Pickup.

        Args:
            placa (str): Placa da picape (deve ter 8 caracteres).
            chassi (str): Chassi da picape (deve ter 17 caracteres).
            modelo (str): Modelo da picape.
            capacidade (int): Capacidade de carga da picape.
            ano (int): Ano da picape (deve ser maior que 1885).
            lat (float): Latitude da localização da picape.
            lng (float): Longitude da localização da picape.

        Raises:
            ValueError: Se qualquer um dos parâmetros fornecidos for inválido.
        """
        super().__init__(placa, chassi, modelo, capacidade, ano, lat, lng)
        self.__class__._instances.append(self)

    
