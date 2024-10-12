#include "cenario.h"

int Cenario::calcularArea(const std::vector<std::vector<int>>& matriz, int roboX, int roboY) {
    int altura = matriz.size();
    int largura = matriz[0].size();

    // Matriz R de zeros com o mesmo tamanho da matriz de entrada
    std::vector<std::vector<int>> R(altura, std::vector<int>(largura, 0));

    // Fila para armazenar os pontos da vizinhança
    std::queue<Coordenada> fila;

    // Inserir a posição inicial do robô na fila
    fila.push(Coordenada(roboX, roboY));
    R[roboX][roboY] = 1; // Marca como visitado

    int area = 1; // Contador para o número de pontos no componente conexo

    // Movimentos para os vizinhos (vizinhança-4)
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // Enquanto a fila não estiver vazia
    while (!fila.empty()) {
        Coordenada atual = fila.front();
        fila.pop();

        // Percorrer os quatro vizinhos
        for (int i = 0; i < 4; ++i) {
            int novoX = atual.x + dx[i];
            int novoY = atual.y + dy[i];

            // Verificar se o vizinho está dentro da matriz e não foi visitado
            if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < largura && matriz[novoX][novoY] == 1 && R[novoX][novoY] == 0) {
                // Inserir o vizinho na fila e marcar como visitado
                fila.push(Coordenada(novoX, novoY));
                R[novoX][novoY] = 1;
                area++; // Incrementa a área do componente conexo
            }
        }
    }

    // Retorna o tamanho da área conectada
    return area;
}
