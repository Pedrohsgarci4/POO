#include "coordinates.hpp"

Coordinates::Coordinates( double lat, double lng){
    if (lat < -90 || lat > 90 || lng< -180 || lng > 180) {
         throw std::invalid_argument("Coordenadas inválidas. Latitude deve estar entre -90 e 90, e Longitude entre -180 e 180.");
    }
    this->lat = lat;
    this->lng = lng;
}

Coordinates::~Coordinates(){}

void Coordinates::set_coordinates( double lat, double lng){
    if (lat < -90 || lat > 90 || lng < -180 || lng > 180) {
        throw std::invalid_argument("Coordenadas inválidas. Latitude deve estar entre -90 e 90, e Longitude entre -180 e 180.");
    }
}

double* Coordinates::get_coordinates(){
    double *vec = new double[2];
    vec[0] = this->lat;
    vec[1] = this->lng;

    return vec;
}

bool Coordinates::operator==( const Coordinates& other){
    return this->lat == other.lat && this->lng == other.lng;
}

std::ostream& operator<<( std::ostream& os, const Coordinates& obj){
    os << "Latitude: "<< obj.lat << "\nLongitude: " << obj.lng;
    return os;
}

