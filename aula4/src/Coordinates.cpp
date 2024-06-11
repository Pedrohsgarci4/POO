#include "../include/Coordinates.hpp"

Coordinates::Coordinates( double lat, double lng){
    if (lat < -90 || lat > 90 || lng < -180 || lng > 180) {
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


double Coordinates::toRadians(double d) {
    return d * PI / 180.0;
}

double Coordinates::calculate_distance( Coordinates &c1, Coordinates& c2){
    double lat1 = toRadians( c1.lat);
    double lat2 = toRadians( c2.lat);
    double lng1 = toRadians( c1.lng);
    double lng2 = toRadians( c2.lng);

    // Fórmula de Haversine
    double dlng = lng2 - lng1;
    double dlat = lat2 - lat1;
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlng / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;

}


bool Coordinates::operator==( const Coordinates& other){
    return this->lat == other.lat && this->lng == other.lng;
}

std::ostream& operator<<( std::ostream& os, const Coordinates& obj){
    os << "Latitude: "<< obj.lat << "\nLongitude: " << obj.lng;
    return os;
}

