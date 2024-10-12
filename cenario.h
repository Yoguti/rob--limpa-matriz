#ifndef CENARIO_H
#define CENARIO_H

#include <vector>
#include <queue>

class Cenario {
public:
    struct Coordenada {
        int x, y;
        Coordenada(int x_, int y_) : x(x_), y(y_) {}
    };

    int calcularArea(const std::vector<std::vector<int>>& matriz, int roboX, int roboY);
};

#endif // CENARIO_H
