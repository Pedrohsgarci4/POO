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

void create_Order(std::string csv)
{
    std::ifstream file(csv);
    std::string line;
    std::vector<std::string> row;
    std::string currentItem;

    int tries = 0;

    while (std::getline(file, line) && tries < 3)
    {
        row.clear();
        currentItem.clear();
        int enable = 0;

        for (char c : line)
        {
            if (c == '"')
            {
                if (enable == 1)
                    enable = 0;
                else
                    enable = 1;
            }

            if (c == ',' && enable == 0)
            {
                row.push_back(currentItem);
                currentItem.clear();
            }
            else currentItem += c;
        }

        for (int i = 0; i < 10; i++)
        {
            std::cout << row[i] << " ";
        }
        std::cout << "\n";
        tries++;
    }
}

int main()
{
    clean_csv("C:/Users/lucas/OneDrive/Documents/test/dados_entregas.csv", "new_file.csv");
    create_Order("new_file.csv");
}