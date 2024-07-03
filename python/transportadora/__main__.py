from random import randint

from transportadora.components import *


def add_vehicles( garage, n_vehicles):
    for n in range(n_vehicles):
        point = Coordinates.random_coordinates('')

        garage.add_vehicle( Vehicle("EUR-40U5", "XXXXXXXXXXXXXXXXX", 'Fiat uno turbinado', randint(500, 1000),2012, point.latitude, point.longitude))

def main():
    point = Coordinates.random_coordinates('Garagem')

    garage = Garage( point.latitude, point.longitude)


    manager = Manager(garage)

    manager.read_orders('./dados_entregas.csv')

    add_vehicles(garage, 5000)

    manager.fulfill_orders( 5000, limit=10)
    

        
    


if __name__ == '__main__':
    main()