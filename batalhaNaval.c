#include <stdio.h>

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se é possível posicionar navio
int podePosicionar(int tabuleiro[TAM][TAM], int posicoes[3][2]) {
    for (int i = 0; i < 3; i++) {
        int x = posicoes[i][0], y = posicoes[i][1];
        if (x < 0 || x >= TAM || y < 0 || y >= TAM || tabuleiro[x][y] != AGUA)
            return 0;
    }
    return 1;
}

// Função para posicionar navio
void posicionarNavio(int tabuleiro[TAM][TAM], int posicoes[3][2]) {
    for (int i = 0; i < 3; i++) {
        int x = posicoes[i][0], y = posicoes[i][1];
        tabuleiro[x][y] = NAVIO;
    }
}

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n   ");
    for (int i = 0; i < TAM; i++) printf("%c ", 'A' + i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA) printf("~ ");
            else if (tabuleiro[i][j] == NAVIO) printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");
            else printf("? ");
        }
        printf("\n");
    }
}

// Cria habilidade em cone
void aplicarHabilidadeCone(int tabuleiro[TAM][TAM], int origemX, int origemY) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = origemY - i; j <= origemY + i; j++) {
            int x = origemX + i;
            if (x >= 0 && x < TAM && j >= 0 && j < TAM && tabuleiro[x][j] == AGUA)
                tabuleiro[x][j] = HABILIDADE;
        }
    }
}

// Cria habilidade em cruz
void aplicarHabilidadeCruz(int tabuleiro[TAM][TAM], int origemX, int origemY) {
    for (int i = -2; i <= 2; i++) {
        int x = origemX + i;
        int y = origemY + i;
        if (origemX + i >= 0 && origemX + i < TAM && tabuleiro[origemX + i][origemY] == AGUA)
            tabuleiro[origemX + i][origemY] = HABILIDADE;
        if (origemY + i >= 0 && origemY + i < TAM && tabuleiro[origemX][origemY + i] == AGUA)
            tabuleiro[origemX][origemY + i] = HABILIDADE;
    }
}

// Cria habilidade em octaedro (losango)
void aplicarHabilidadeOctaedro(int tabuleiro[TAM][TAM], int origemX, int origemY) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                int x = origemX + i - 2;
                int y = origemY + j - 2;
                if (x >= 0 && x < TAM && y >= 0 && y < TAM && tabuleiro[x][y] == AGUA)
                    tabuleiro[x][y] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posições dos 4 navios
    int navioH[3][2] = {{2, 2}, {2, 3}, {2, 4}};
    int navioV[3][2] = {{5, 5}, {6, 5}, {7, 5}};
    int navioDiag1[3][2] = {{0, 0}, {1, 1}, {2, 2}};
    int navioDiag2[3][2] = {{0, 9}, {1, 8}, {2, 7}};

    // Posicionamento validado
    if (podePosicionar(tabuleiro, navioH)) posicionarNavio(tabuleiro, navioH);
    if (podePosicionar(tabuleiro, navioV)) posicionarNavio(tabuleiro, navioV);
    if (podePosicionar(tabuleiro, navioDiag1)) posicionarNavio(tabuleiro, navioDiag1);
    if (podePosicionar(tabuleiro, navioDiag2)) posicionarNavio(tabuleiro, navioDiag2);

    // Aplicação das habilidades
    aplicarHabilidadeCone(tabuleiro, 4, 2);      // Cone partindo de (4,2)
    aplicarHabilidadeCruz(tabuleiro, 6, 6);      // Cruz centrada em (6,6)
    aplicarHabilidadeOctaedro(tabuleiro, 5, 8);  // Octaedro centrado em (5,8)

    exibirTabuleiro(tabuleiro);

    return 0;
}
