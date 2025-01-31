#include <iostream>
#include <random>

using namespace std;

class GameManager {
private:
    random_device rd;                                 // Fonte de entropia
    mt19937 gen;                                      // Gerador Mersenne Twister
    uniform_int_distribution<> numero_portas_range;   // Distribuição para número de portas
    uniform_int_distribution<> segunda_chance_range;  // Distribuição para segunda chance
    int numero_portas;

public:
    // Construtor para inicializar variáveis
    GameManager(int num_portas)
        : gen(rd()),
          numero_portas_range(1, num_portas),
          segunda_chance_range(1, 2),
          numero_portas(num_portas) {}  // Corrigido para usar o parâmetro num_portas

    void desenhaPortas() {
        for (int i = 1; i <= numero_portas; i++) {
            cout << " ______ \n";
            cout << "|      |\n";
            cout << "|  " << i << "   |\n";
            cout << "|______|\n\n";
        }
    }

    bool secondChance() {
        int segunda_chance = segunda_chance_range(gen);
        int chance = 2;
        return segunda_chance == chance;
    }

    void playGame() {
        int porta_vitoria = numero_portas_range(gen);  // Porta correta gerada

        cout << "Existem " << numero_portas << " portas no jogo." << endl;
        desenhaPortas();  // Desenha as portas baseadas no número definido
        cout << "Qual voce vai escolher? " << endl;

        int entrada_user;
        cin >> entrada_user;

        cout << "Voce escolheu a porta numero " << entrada_user << "." << endl;

        if (entrada_user == porta_vitoria) {
            cout << "\033[1;32m"; // Verde
            cout << "Voce escolheu a porta certa! Pode sair com vida!" << endl;
            cout << "\033[0m"; // Reseta as cores
        } else {
            cout << "Voce escolheu a porta errada! Vamos ver se eu te dou outra chance..." << endl;
            if (secondChance()) {
                cout << "Você ganhou uma segunda chance! Escolha novamente uma porta: " << endl;
                cin >> entrada_user;

                if (entrada_user == porta_vitoria) {
                    cout << "\033[1;32m"; // Verde
                    cout << "Voce acertou na segunda chance! Pode sair com vida!" << endl;
                    cout << "\033[0m"; // Reseta as cores
                } else {
                    cout << "\033[1;31m"; // Vermelho em negrito
                    cout << "Infelizmente, ainda errou... A porta certa era a porta numero " << porta_vitoria << "." << endl;
                    cout << "AGORA MORRA! HUAHUAHUAHUAHUA!" << endl;
                    cout << "\033[0m"; // Reseta as cores
                }
            } else {
                cout << "\033[1;31m"; // Vermelho em negrito
                cout << "Sem sorte! Você não ganhou uma segunda chance..." << endl;
                cout << "A porta certa era a porta numero " << porta_vitoria << "." << endl;
                cout << "AGORA MORRA! HUAHUAHUAHUAHUA!" << endl;
                cout << "\033[0m"; // Reseta as cores
            }
        }
    }
};

int main() {
    GameManager game(4); // Inicializa o jogo com 4 portas
    game.playGame();     // Executa o jogo
    return 0;
}
