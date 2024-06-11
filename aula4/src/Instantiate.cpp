#include "../include/Instantiate.hpp"
#include "../include/Order.hpp"
#include "../include/Client.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "../json.hpp"

using json = nlohmann::json;

struct Coordenadas
{
    double latitude;
    double longitude;
};

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size * nmemb;
    try
    {
        s->append((char *)contents, newLength);
    }
    catch (std::bad_alloc &e)
    {
        // Handle memory problem
        return 0;
    }
    return newLength;
}

// Função para codificar o endereço e fazer a solicitação HTTP
std::string geocodeAddress(const std::string &endereco)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        throw std::runtime_error("Erro ao inicializar o CURL.");
    }

    char *enderecoEscaped = curl_easy_escape(curl, endereco.c_str(), endereco.length());
    if (!enderecoEscaped)
    {
        curl_easy_cleanup(curl);
        throw std::runtime_error("Erro ao codificar o endereço.");
    }

    std::string url = "https://nominatim.openstreetmap.org/search?q=" + std::string(enderecoEscaped) + "&format=json&addressdetails=1";
    curl_free(enderecoEscaped);
    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "MyApp/1.0 (your-email@example.com)");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        throw std::runtime_error("Erro na solicitação: " + std::string(curl_easy_strerror(res)));
    }

    return readBuffer;
}

// Função para analisar o JSON e extrair as coordenadas
std::pair<double, double> parseCoordinates(const std::string &jsonResponse)
{
    auto dados = json::parse(jsonResponse);
    if (!dados.empty())
    {
        double latitude = std::stod(dados[0]["lat"].get<std::string>());
        double longitude = std::stod(dados[0]["lon"].get<std::string>());
        return {latitude, longitude};
    }
    else
    {
        throw std::runtime_error("Endereço não encontrado.");
    }
}

// Função que combina a geocodificação e a análise para retornar as coordenadas
std::pair<double, double> getCoordinates(const std::string &endereco)
{
    std::string jsonResponse = geocodeAddress(endereco);
    return parseCoordinates(jsonResponse);
}

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
            std::pair<double, double> coords1 = getCoordinates(row[5]);
            std::pair<double, double> coords2 = getCoordinates(row[6]);

            if (row[1] == client->get_cpf())
            {
                Order *newObject = new Order(client->get_id(), Coordinates(coords1.first, coords2.second), Coordinates(coords2.first, coords2.second), std::stof(row[7]), std::stof(row[8]), row[9]);
            }
        }
    }
}

void registerFile(std::string csvFile, std::string newCSVFile)
{
    clean_csv(csvFile, newCSVFile);
    create_order(newCSVFile);
}