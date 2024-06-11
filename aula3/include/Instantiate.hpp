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

#endif