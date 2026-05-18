#include <iostream>
#include <vector> // alterar tamanho do vetor
#include <conio.h> // _kbhit() e _getch()
#include <time.h> // time_t e time() -> mais fácil pro resto
#include <thread> // sleep padrão do C++, deu problema o outro
#include <chrono> // usado pro sleep

using namespace std;
bool genius(int dificuldade);
					
int main(){
	bool executando = true;

	int dificuldade = 1; // default

	srand(time(NULL)); // seed aleatório
	system("cls"); // limpa a tela

	while(executando){
		cout << "		Genius		";
		cout << "\n1. Jogar\n2. Dificuldade\n3. Sobre\n4. Fim\n";
		int escolha;
		cin >> escolha;
		
		if (escolha == 1){
			cout << "Iniciando o jogo...\n";
			executando = genius(dificuldade); // -> LOOP DO JOGO
		}else if(escolha == 2){
			cout << "Escolha a dificuldade:\n1. Facil\n2. Medio\n3. Dificil\n";
			cin >> dificuldade;
			if(dificuldade < 1 || dificuldade > 3){
				cout << "ERROR: Dificuldade inválida\n";
				std::this_thread::sleep_for(std::chrono::seconds(2));
				executando = false;
			}
		}else if(escolha == 3){
			cout << "Equipe de desenvolvimento:\n- Pedro Henrique R. J. Nicolini\n- Luiz Eduardo F. N. Goncalves\n";
			cout << "Maio/2026\n";
			cout << "Professor: Thiago Felski\nDisciplina: Algoritmos e Programacao\n";
		}else if(escolha == 4){
			cout << "Encerrando o jogo...\n";
			executando = false;
		}
	}	
	
	system("cls");
	return 0;
}


bool genius(int dificuldade){
	const int facil = 3, medio = 4, dificil = 5;
	int tamanho = 0; // default;
	int tempo_soneca = 5; // default
	int digitos = 1;
	vector<int> vetor;
	string dificuldade_string;

	if(dificuldade == 1){ // fácil
		dificuldade_string = "facil";
		tamanho = 10; // ALTERAR PRA 10 DEPOIS DE TESTAR
		tempo_soneca = 5; 
		vetor.resize(tamanho);
		for(int i = 0; i < tamanho; i++){
			vetor[i] = rand() % facil + 1;  // 1 - 3
		}

	}else if(dificuldade == 2){ // médio
		dificuldade_string = "medio";
		tamanho = 12;
		tempo_soneca = 3;
		vetor.resize(tamanho);
		for(int i = 0; i < tamanho; i++){
			vetor[i] = rand() % medio + 1; // 1 - 4
		}

	}else if(dificuldade == 3){ // difícil
		dificuldade_string = "dificil";
		tamanho = 16;
		tempo_soneca = 2;
		vetor.resize(tamanho);
		for(int i = 0; i < tamanho; i++){
			vetor[i] = rand() % dificil + 1; // 1 - 5
		}	

	}else{
		cout << "ERROR: Dificuldade inválida\n";
		return false;	
	}

	system("cls"); // limpa a tela
	cout << "Prepare-se...\n";
	std::this_thread::sleep_for(std::chrono::seconds(2)); 
	cout << "Memorize a sequencia:\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	system("cls"); 

	// imprime genius
	for(int i = 0; i < tamanho; i++){
		cout << vetor[i] << " ";
		
		if(dificuldade == 1){
			if((i + 1) % 2 == 0){ // 2 em 2
				std::this_thread::sleep_for(std::chrono::seconds(tempo_soneca));
				system("cls");
			}
		}else if(dificuldade == 2){
			if((i + 1) % 3 == 0){ // 3 em 3
				std::this_thread::sleep_for(std::chrono::seconds(tempo_soneca));
				system("cls");
			}
		}else if(dificuldade == 3){
			if((i + 1) % 4 == 0){ // 4 em 4
				std::this_thread::sleep_for(std::chrono::seconds(tempo_soneca));
				system("cls");
			}
		}
	}
	
	cout << "Digite a sequencia: " << "\n";

	time_t inicio;
	vector<int> resposta(tamanho);

	for (int i = 0; i < tamanho; i++){
		inicio = time(NULL);
		bool digitou = false;

		while (difftime(time(NULL), inicio) < 2) {
			if (_kbhit()) {
				char letra = _getch();
				if (letra >= '1' && letra <= '5'){ // ALTERAR AQUI se for alterar o range
					resposta[i] = letra - '0'; // converte char para int -> STACKOVERFLOW salvando o dia
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

		if (!digitou) {
			cout << "\nTempo esgotado! Voce perdeu!\n";
			break;
		}
	}	
	int corretos = 0;
	for (int i = 0; i < tamanho; i++){	
		if(resposta[i] == vetor[i]){
			corretos++;
		}
	}

	cout << "\nSequencia correta: ";
	for (int i = 0; i < tamanho; i++){
		cout << vetor[i] << " ";
	}
	cout << "\nSua resposta: ";
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
	}else{
		cout << "Encerrando o jogo...\n";
	}

	return true;
}