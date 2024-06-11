#include "../include/Instantiate.hpp"
#include "../include/Order.hpp"
#include "../include/Client.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void clean_csv(std::string csvFile, std::string newCSVFile)
{
    std::ifstream arquivo(csvFile);
    std::ofstream novoArquivo(newCSVFile);

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de leitura!" << std::endl;
        return;
    }

    if (!novoArquivo.is_open())
    {
        std::cerr << "Erro ao criar o arquivo de escrita!" << std::endl;
        return;
    }

    int countBreak = 6;

    char caractere;
    while (arquivo.get(caractere))
    {

        if (caractere == '\n')
        {
            countBreak++;
            if (countBreak % 7 == 0)
                novoArquivo.put('\n');
        }
        else
            novoArquivo.put(caractere);
    }
    arquivo.close();

}

void create_order(std::string csv)
{
    std::ifstream file(csv);
    std::string line;
    std::vector<std::string> row;
    std::string currentItem;

    while (std::getline(file, line))
    {
        row.clear();
        currentItem.clear();
        int enable = 0;

        for (char c : line)
        {
            if (c == '"')
            {
                if (enable == 1) enable = 0;
                else enable = 1;
            }

            if (c == ',' && enable == 0)
            {
                row.push_back(currentItem);
                currentItem.clear();
            }
            else currentItem += c;
        }

        std::list<Client*>& allClients = Client::get_instances();
        for (Client* client : allClients)
        {
            if (row[1] == client->get_cpf())
            {
                Order *newObject = new Order(client->get_id(), row[5], row[6], std::stof(row[7]), std::stof(row[8]), row[9]);
            }
        }
    }
}

void registerFile(std::string csvFile, std::string newCSVFile)
{
    clean_csv(csvFile, newCSVFile);
    create_order(newCSVFile);
}