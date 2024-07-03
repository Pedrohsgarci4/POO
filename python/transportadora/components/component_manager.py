class Component_Manager:
    """
    Classe base para gerenciar instâncias de componentes.
    """
    _instances = []

    def __init__(self) -> None:
        """
        Inicializa uma nova instância do Component_Manager.
        """
        pass

    @classmethod
    def find_by_id(cls, value):
        """
        Encontra uma instância pelo seu ID.

        Args:
            value (int): O ID da instância a ser encontrada.

        Returns:
            object: A instância encontrada, ou None se não for encontrada.
        """
        return next((obj for obj in cls._instances if obj.id == value), None)
    
    @classmethod
    def find_by(cls, value, attribute_name):
        """
        Encontra uma instância pelo valor de um atributo específico.

        Args:
            value: O valor do atributo a ser procurado.
            attribute_name (str): O nome do atributo a ser procurado.

        Returns:
            object: A instância encontrada, ou None se não for encontrada.
        """
        return next((obj for obj in cls._instances if getattr(obj, attribute_name) == value), None)
    
    @classmethod
    def all(cls):
        """
        Retorna todas as instâncias gerenciadas pelo Component_Manager.

        Returns:
            list: Lista de todas as instâncias.
        """
        return cls._instances

    def __del__(self):
        """
        Remove a instância da lista de instâncias quando ela é deletada.
        """
        if self in self.__class__._instances:
            self.__class__._instances.remove(self)


    def __repr__(self) -> str:
        return self.__str__()
