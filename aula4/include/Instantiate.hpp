#ifndef INSTANTIATE_HPP
#define INSTANTIATE_HPP

#include "../include/Instantiate.hpp"
#include "../include/Order.hpp"
#include "../include/Client.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void clean_csv(std::string csvFile, std::string newCSVFile);

void create_order(std::string csv);

void registerFile(std::string csvFile, std::string newCSVFile);

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);

std::string geocodeAddress(const std::string &endereco);

std::pair<double, double> parseCoordinates(const std::string &jsonResponse);

std::pair<double, double> getCoordinates(const std::string &endereco);

#endif