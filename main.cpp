#include <iostream>
#include <vector>
#include <conio.h> // _kbhit() e _getch()
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;
bool genius(int dificuldade);

int main(){
    bool executando = true;
    int dificuldade = 1; // default fácil

    srand(time(NULL)); // seed random
    system("cls");

    while(executando){
        cout << "\t\tGenius\t\t";
        cout << "\n1. Jogar\n2. Dificuldade\n3. Sobre\n4. Fim\n";
        int escolha;
        cin >> escolha;
        
        if (escolha == 1){
            cout << "Iniciando o jogo...\n";
            executando = genius(dificuldade); // loop do jogo return false se escolher não jogar true se continuar
        } else if(escolha == 2){
            cout << "Escolha a dificuldade:\n1. Facil\n2. Medio\n3. Dificil\n";
            cin >> dificuldade;
            if(dificuldade < 1 || dificuldade > 3){
                cout << "ERROR: Dificuldade inválida\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                executando = false;
            }
        } else if(escolha == 3){
            cout << "Equipe de desenvolvimento:\n- Pedro Henrique R. J. Nicolini\n- Luiz Eduardo F. N. Goncalves\n";
            cout << "Maio/2026\n";
            cout << "Professor: Thiago Felski\nDisciplina: Algoritmos e Programacao\n";
        } else if(escolha == 4){
            cout << "Encerrando o jogo...\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
            executando = false;
        }
    }
    
    system("cls");
    return 0;
}

bool genius(int dificuldade){
    const int facil = 3, medio = 4, dificil = 5;
    int tamanho = 0;
    int tempo_soneca = 5;
    int tamanho_rodada = 2;
    vector<int> vetor;
    string dificuldade_string;

    if(dificuldade == 1){
        dificuldade_string = "facil"; // define pra frase de vitória
        tamanho = 10; // tamanho vetor
        tempo_soneca = 5; // tempo entre números aparecer
        tamanho_rodada = 2; // tamanho rodada
        vetor.resize(tamanho); // define tamanho do vetor
        for(int i = 0; i < tamanho; i++){
            vetor[i] = rand() % facil + 1; // preenche vetor
        }
    } else if(dificuldade == 2){
        dificuldade_string = "medio";
        tamanho = 12;
        tempo_soneca = 3;
        tamanho_rodada = 3;
        vetor.resize(tamanho);
        for(int i = 0; i < tamanho; i++){
            vetor[i] = rand() % medio + 1;
        }
    } else if(dificuldade == 3){
        dificuldade_string = "dificil";
        tamanho = 16;
        tempo_soneca = 2;
        tamanho_rodada = 4;
        vetor.resize(tamanho);
        for(int i = 0; i < tamanho; i++){
            vetor[i] = rand() % dificil + 1;
        }
    } else {
        cout << "ERROR: Dificuldade inválida\n";
        return false;
    }

    system("cls");
    cout << "Prepare-se...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "Memorize a sequencia:\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("cls");

    vector<int> resposta(tamanho, 0); // preenche vetor com 0 do tamanho do vetor normal
    bool perdeu = false;
    int corretos = 0;
    int rodada = 1;

    for(int start = 0; start < tamanho; start += tamanho_rodada){

        int fim_rodada = min(start + tamanho_rodada, tamanho); // pega min entre round posicao atual do vetor + tamanho rodada
        int tamanho_grupo = fim_rodada - start;

        // Mostrar o grupo de números um a um e esperar tempo_soneca entre cada número.
        for(int i = start; i < fim_rodada; i++){
            system("cls");
            cout << "Posicao " << i + 1 << " : [ " << vetor[i] << " ]";
            std::this_thread::sleep_for(std::chrono::seconds(tempo_soneca));
        }

        system("cls");
        cout << "Digite a rodada " << rodada << " de " << tamanho_grupo << " numeros:\n";
        rodada++;

        for(int i = start; i < fim_rodada; i++){
            time_t inicio = time(NULL);
            bool digitou = false;

            while(difftime(time(NULL), inicio) < 2){
                if (_kbhit()){
                    char letra = _getch();
                    if (letra >= '1' && letra <= '5'){ // verifica se é um digito válido
                        resposta[i] = letra - '0'; // conversão pra int
                        cout << "\nVoce digitou: " << resposta[i] << "\n";
                        digitou = true;
                        break;
                    } else {
                        cout << "\nEntrada inválida! Digite um número de 1 a 5.\n";
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            if (!digitou){
                cout << "\nTempo esgotado! Voce perdeu!\n";
                perdeu = true;
                break;
            }
        }

        if(perdeu) break;
    }

    if(!perdeu){
        for (int i = 0; i < tamanho; i++){
            if(resposta[i] == vetor[i]){
                corretos++;
            }
        }
    }

    cout << "\nSequencia correta:\n";
    for (int i = 0; i < tamanho; i++){
        cout << vetor[i] << " ";
    }
    cout << "\nSua resposta:\n";
    for (int i = 0; i < tamanho; i++){
        cout << resposta[i] << " ";
    }

    cout << "\n\nCalculando resultado...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    cout << "\nVoce acertou " << corretos << " de " << tamanho << " na dificuldade " << dificuldade_string << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    cout << "\nContinuar?(1. Sim - 2. Nao): ";
    int escolha;
    cin >> escolha;
    if(escolha == 1){
        system("cls");
        return true;
    }

    cout << "Encerrando o jogo...\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
    return false;
}
