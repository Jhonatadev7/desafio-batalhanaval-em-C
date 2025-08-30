#include <stdio.h>

#define TAMANHO 10      // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3         // Valor que representa um navio no tabuleiro
#define AGUA 0          // Valor que representa água no tabuleiro
#define HABILIDADE 5    // Valor que representa área afetada por habilidade
#define TAMANHO_NAVIO 3 // Comprimento fixo dos navios
#define TAM_HAB 5       // Tamanho fixo das matrizes de habilidades (5x5)

// ---------- Funções de posicionamento de navios ----------
int posicionaHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] == NAVIO) return 0;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
    return 1;
}

int posicionaVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] == NAVIO) return 0;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
    return 1;
}

int posicionaDiagonalPrincipal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO || coluna + TAMANHO_NAVIO > TAMANHO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] == NAVIO) return 0;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }
    return 1;
}

int posicionaDiagonalSecundaria(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO || coluna - (TAMANHO_NAVIO - 1) < 0) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] == NAVIO) return 0;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }
    return 1;
}

// ---------- Funções de habilidades especiais ----------
// Preenche matriz de cone (5x5)
void criaCone(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i)) {
                habilidade[i][j] = 1; // Dentro do cone
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Preenche matriz de cruz (5x5)
void criaCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    int meio = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == meio || j == meio) {
                habilidade[i][j] = 1; // Linha central e coluna central
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Preenche matriz de octaedro (5x5) - formato losango
void criaOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    int meio = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio) {
                habilidade[i][j] = 1; // Dentro do losango
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Sobrepõe habilidade no tabuleiro em torno de (linhaOrigem, colunaOrigem)
void aplicaHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HAB][TAM_HAB], int linhaOrigem, int colunaOrigem) {
    int meio = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int linha = linhaOrigem + (i - meio);
                int coluna = colunaOrigem + (j - meio);

                // Verifica se está dentro do tabuleiro
                if (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO) {
                    if (tabuleiro[linha][coluna] == AGUA) {
                        tabuleiro[linha][coluna] = HABILIDADE;
                    }
                }
            }
        }
    }
}

// ---------- Função para exibir tabuleiro ----------
void exibeTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n--- TABULEIRO BATALHA NAVAL ---\n\n");
    printf("   ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == AGUA) printf(" . ");      // Água
            else if (tabuleiro[i][j] == NAVIO) printf(" N "); // Navio
            else if (tabuleiro[i][j] == HABILIDADE) printf(" * "); // Habilidade
        }
        printf("\n");
    }
}

// ---------- Programa principal ----------
int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa tabuleiro
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posiciona navios fixos
    posicionaHorizontal(tabuleiro, 2, 4);
    posicionaVertical(tabuleiro, 5, 7);
    posicionaDiagonalPrincipal(tabuleiro, 0, 0);
    posicionaDiagonalSecundaria(tabuleiro, 0, 9);

    // Cria matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    criaCone(cone);
    criaCruz(cruz);
    criaOctaedro(octaedro);

    // Aplica habilidades no tabuleiro em posições fixas
    aplicaHabilidade(tabuleiro, cone, 4, 4);
    aplicaHabilidade(tabuleiro, cruz, 7, 2);
    aplicaHabilidade(tabuleiro, octaedro, 6, 6);

    // Exibe tabuleiro final
    exibeTabuleiro(tabuleiro);

    return 0;
}
