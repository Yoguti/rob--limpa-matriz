#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "parser.h"
#include "cenario.h"

// ASCII Art
void displayTitle() {
    std::cout << R"(
           _________________
        __/ =         =    /|      (era pra ser um robozinho) - Klaus S.
       /    /         /   --/|
      /  -____________-    / /
     /                    / /
    |--________________--/ /
    |  |     ufsc     |  |/
    |--|______________|--/ 
    )" << std::endl;
}

void displayBox(const std::string &content) {
    std::cout << "+------------------------+" << std::endl;
    std::cout << "| " << content << std::endl;
    std::cout << "+------------------------+" << std::endl;
}

void displayBulletPoint(const std::string &content) {
    std::cout << "• " << content << std::endl;
}

int main() {
    displayTitle();
    std::cout << "Bem-vindo ao Processador de Cenários!" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    Parser parser;
    Cenario cenario;
    std::string filename;
    
    std::cout << "Por favor, insira o nome do arquivo XML: ";
    std::cin >> filename;

    std::ifstream arquivo(filename);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo " << filename << std::endl;
        return 1;
    }

    // Lê o conteúdo do arquivo
    std::string texto;
    char caracter;
    while (arquivo.get(caracter)) {
        texto += caracter;
    }
    arquivo.close();

    // Testa a validação de aninhamento das tags
    try {
        if (!parser.validar(texto)) {
            throw std::runtime_error("Erro: Aninhamento das tags XML inválido.");
        }
        displayBox("O aninhamento das tags XML está correto.");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Testa a contagem de cenários
    try {
        int numCenarios = parser.contadordeCenarios(texto);
        displayBulletPoint("Número total de cenários disponíveis: " + std::to_string(numCenarios));

        // Verifica se há cenários disponíveis
        if (numCenarios == 0) {
            std::cerr << "Erro: Não existem cenários disponíveis." << std::endl;
            return 1;
        }

        // Variáveis para armazenar resultados para a lista final
        std::vector<int> areas;
        std::vector<std::pair<int, int>> roboPosicoes;

        // Testa cada cenário individualmente
        for (int i = 1; i <= numCenarios; ++i) {
            try {
                std::cout << "Testando o cenário " << i << "..." << std::endl;
                Parser::MatrizInfo info = parser.parse(filename, i); // Chama o parse para cada cenário
                std::cout << "Cenário " << i << " processado com sucesso!" << std::endl;
                displayBox("Altura: " + std::to_string(info.altura) + "\nLargura: " + std::to_string(info.largura));
                displayBulletPoint("Posição do robô: (" + std::to_string(info.roboX) + ", " + std::to_string(info.roboY) + ")");

                // Exibe a matriz
                std::cout << "Matriz:\n";
                for (const auto& linha : info.matriz) {
                    for (int valor : linha) {
                        std::cout << valor << " ";
                    }
                    std::cout << "\n";
                }

                // Calcula a área do componente conexo
                int area = cenario.calcularArea(info.matriz, info.roboX, info.roboY);
                areas.push_back(area);
                roboPosicoes.push_back({info.roboX, info.roboY});
                
                std::cout << "Área do componente conexo: " << area << " pontos\n";
            } catch (const std::runtime_error &e) {
                std::cerr << "Erro ao processar o cenário " << i << ": " << e.what() << std::endl;
            }
        }

        // Exibe a lista final com as informações de todos os cenários
        std::cout << "\n+------------------------+\n";
        std::cout << "| Resumo dos Cenários      |\n";
        std::cout << "+------------------------+\n";
        for (int i = 0; i < areas.size(); ++i) {
            std::cout << "Matriz " << (i+1) << " - Posição inicial do robô: ("
                      << roboPosicoes[i].first << ", " << roboPosicoes[i].second 
                      << ") - Área a ser limpa: " << areas[i] << " pontos\n";
        }

    } catch (const std::runtime_error &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0; 
}
