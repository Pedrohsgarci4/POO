from transportadora.components.component_manager import Component_Manager

class Client(Component_Manager):
    """
    Classe Client para gerenciar clientes.
    """
    _instances = []
    _object_count = 0

    def __init__(self, name: str, cpf: str, phone_number: str = "", email: str = "", age: int = 18) -> None:
        """
        Inicializa uma nova instância da classe Client.

        Args:
            name (str): Nome do cliente.
            cpf (str): CPF do cliente.
            phone_number (str, opcional): Número de telefone do cliente.
            email (str, opcional): Email do cliente.
            age (int, opcional): Idade do cliente. Default é 18.

        Raises:
            TypeError: Se qualquer um dos parâmetros fornecidos não for uma string.
        """
        if not all(map(lambda x: isinstance(x, str), [name, cpf, phone_number, email])):
            raise TypeError("Todos os campos devem ser strings.")

        self._name = name
        self._cpf = cpf
        self._phone_number = phone_number
        self._email = email
        self._age = age

        self.__class__._object_count += 1
        self._id = self.__class__._object_count

        self.__class__._instances.append(self)

    def id(self):
        """
        Retorna o ID do cliente.

        Returns:
            int: ID do cliente.
        """
        return self._id

    @property
    def name(self):
        """
        Retorna o nome do cliente.

        Returns:
            str: Nome do cliente.
        """
        return self._name

    @name.setter
    def name(self, name: str):
        """
        Define o nome do cliente.

        Args:
            name (str): Nome do cliente.

        Raises:
            TypeError: Se o nome não for uma string.
            ValueError: Se o nome estiver vazio.
        """
        if not isinstance(name, str):
            raise TypeError("O nome deve ser uma string.")
        if name == "":
            raise ValueError("O nome não pode estar vazio.")
        self._name = name

    @property
    def cpf(self):
        """
        Retorna o CPF do cliente.

        Returns:
            str: CPF do cliente.
        """
        return self._cpf

    @cpf.setter
    def cpf(self, cpf: str):
        """
        Define o CPF do cliente.

        Args:
            cpf (str): CPF do cliente.

        Raises:
            TypeError: Se o CPF não for uma string.
            ValueError: Se o CPF estiver vazio.
        """
        if not isinstance(cpf, str):
            raise TypeError("O CPF deve ser uma string.")
        if cpf == "":
            raise ValueError("O CPF não pode estar vazio.")
        self._cpf = cpf

    @property
    def phone_number(self):
        """
        Retorna o número de telefone do cliente.

        Returns:
            str: Número de telefone do cliente.
        """
        return self._phone_number

    @phone_number.setter
    def phone_number(self, phone_number: str):
        """
        Define o número de telefone do cliente.

        Args:
            phone_number (str): Número de telefone do cliente.

        Raises:
            TypeError: Se o número de telefone não for uma string.
            ValueError: Se o número de telefone estiver vazio.
        """
        if not isinstance(phone_number, str):
            raise TypeError("O número de telefone deve ser uma string.")
        if phone_number == "":
            raise ValueError("O número de telefone não pode estar vazio.")
        self._phone_number = phone_number

    @property
    def email(self):
        """
        Retorna o email do cliente.

        Returns:
            str: Email do cliente.
        """
        return self._email

    @email.setter
    def email(self, email: str):
        """
        Define o email do cliente.

        Args:
            email (str): Email do cliente.

        Raises:
            TypeError: Se o email não for uma string.
            ValueError: Se o email estiver vazio.
        """
        if not isinstance(email, str):
            raise TypeError("O email deve ser uma string.")
        if email == "":
            raise ValueError("O email não pode estar vazio.")
        self._email = email

    @property
    def age(self):
        """
        Retorna a idade do cliente.

        Returns:
            int: Idade do cliente.
        """
        return self._age

    @age.setter
    def age(self, age: int):
        """
        Define a idade do cliente.

        Args:
            age (int): Idade do cliente.

        Raises:
            TypeError: Se a idade não for um inteiro.
        """
        if not isinstance(age, int):
            raise TypeError("A idade deve ser um inteiro.")
        self._age = age
