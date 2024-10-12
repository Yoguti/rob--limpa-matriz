#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class Parser {
public:
    struct MatrizInfo {
        int altura;
        int largura;
        int roboX;
        int roboY;
        std::vector<std::vector<int>> matriz;
    };

    MatrizInfo parse(const std::string& filename, int numCenario); 
    int contadordeCenarios(const std::string &texto); 

    bool validar(const std::string &texto); 
    MatrizInfo buscar(const std::string &texto); 
    MatrizInfo buscarCenario(const std::string &texto, int numCenario); 
};

#endif // PARSER_H
