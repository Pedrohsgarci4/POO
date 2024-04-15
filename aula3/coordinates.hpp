#ifndef COORDINATES_H
#define COORDINATES_H

#include<iostream>

class Coordinates{
private:
    double lat;
    double lng;
public:
    Coordinates( double lat = 0, double lng = 0);
    ~Coordinates();

    void set_coordinates( double lat, double lng);
    double* get_coordinates();

    bool operator==( const Coordinates& other);
    friend std::ostream& operator<<( std::ostream& os, const Coordinates & obj);
};


#endif