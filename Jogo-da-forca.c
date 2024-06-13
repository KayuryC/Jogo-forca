#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definindo valores
#define MAX_PALAVRAS 100 //Número máximo de palavras que podem ser adicionadas
#define MAX_TENTATIVAS 6 //Numero máximo de tentativas
#define TAM_MAX_PALAVRA 50 //Tamanho máximo de uma palavra

char *palavras[MAX_PALAVRAS];
int num_palavras = 7; // Número inicial de palavras

// Função para inicializar as palavras
void inicializar_palavras() {
	palavras[0] = "batman";
	palavras[1] = "superman";
	palavras[2] = "arlequina";
	palavras[3] = "joker";
	palavras[4] = "flash";
	palavras[5] = "shazam";
	palavras[6] = "robin";
}

//Função pra desenhar boneco da forca
void mostrar_forca(int erros) {
	switch (erros) {
		case 0:
			printf("\n\n\n\n\n\n");
			break;
		case 1:
			printf(" o\n\n\n\n\n");
			break;
		case 2:
			printf(" o\n |\n |\n\n\n");
			break;
		case 3:
			printf(" o\n/|\\\n |\n\n\n");
			break;
		case 4:
			printf(" o\n/|\\\n/ \n\n\n");
			break;
		case 5:
			printf(" o\n/|\\\n/ \\\n\n\n");
			break;
		case 6:
			printf(" o\n/|\\\n/ \\\n\nGame Over!\n");
			break;
	}
}
//Função para mascarar as palavras
void inicializar_mascara(char *mascara, const char *palavra) {
	int i; // Declarando a variável fora do loop
	for (i = 0; i < strlen(palavra); i++) {
		mascara[i] = '?';
	}
	mascara[i] = '\0'; // Adiciona o caractere nulo no final da string
}

// Função para revelar as letras corretas na máscara
int revelar_letra(char *mascara, const char *palavra, char letra) {
	int acertou = 0;
	int i; // Declarando a variável fora do loop
	for (i = 0; i < strlen(palavra); i++) {
		if (palavra[i] == letra) {
			if (mascara[i] == '?') { // Se a letra ainda não foi revelada
				mascara[i] = letra;
				acertou++;
			}
		}
	}
	return acertou;
}
//Função para checar mascara
int palavra_completa(const char *mascara) {
	return strchr(mascara, '?') == NULL; //Verifica se ainda existe algum "?" na mascara
}

//Função para adicionar uma nova palavra
void adicionar_palavra() {
	if (num_palavras < MAX_PALAVRAS) {
		system("cls");
		char nova_palavra[TAM_MAX_PALAVRA];
		printf("Digite a nova palavra: ");
		scanf("%s", nova_palavra);
		palavras[num_palavras] = strdup(nova_palavra);
		num_palavras++;
	} else {
		printf("Numero maximo de palavras atingido!\n");
	}
}
//Função para verificar se a letra ja foi inserida
int letra_repetida(char *letras_inseridas, char letra) {
	return strchr(letras_inseridas, letra) != NULL;
}
//Função Main
int main() {
	//Declarando variaveis
	srand(time(NULL)); // Inicializa o gerador de números aleatórios
	inicializar_palavras();//Iniciando função
	int tentativas_restantes = MAX_TENTATIVAS;//Define o número de tentativas erradas permitidas
	int pontos = 0; // Pontuação do jogador
	char letra; //Variavel para armazenar o palpite do jogador
	char letras_inseridas[26] = "";//Lista para armazenar as letras já inseridas
	int menu_principal;//Menu
	char opcao;//Para adicionar nome

	//Escolhe uma palavra aleatória da lista de palavras
	const char *palavra_secreta = palavras[rand() % num_palavras];
	char mascara[strlen(palavra_secreta) + 1]; //Máscara para a palavra secreta
	inicializar_mascara(mascara, palavra_secreta); //Inicializa a máscara com "?"


	//Menu
	printf("====Jogo da forca DC Comics===\n");
	printf("(1) Jogar\n(2) Sair\n\n");
	scanf("%d", &menu_principal);

	switch(menu_principal) {
		case 1:
			system("cls");//Apagar cmd
			//Adicionar uma nova palavra
			printf("Deseja adicionar novas palavras? (s/n): ");
			scanf(" %c", &opcao);
			while (opcao == 's') {
				adicionar_palavra();
				printf("Deseja adicionar outra palavra? (s/n): ");
				scanf(" %c", &opcao);
			}
			system("cls");
			printf("Sera sorteado um dos principais herois da DC, prepare-se...");
			sleep(4);
			system("cls");
			//Loop principal do jogo
			while(tentativas_restantes > 0 && !palavra_completa(mascara)) {
				printf("Palavra: %s\n", mascara);
				printf("Tentativas restantes: %d\n", tentativas_restantes);
				printf("Pontos: %d\n", pontos);
				printf("Digite uma letra: ");
				scanf(" %c", &letra); //Lê o palpite do jogador
				system("cls");
				//Verifica se a letra já foi inserida
				if (letra_repetida(letras_inseridas, letra)) {
					printf("Voce ja inseriu essa letra!\n");
					continue; //Volta para o início do loop sem penalizar o jogador
				}

				//Adiciona a letra à lista de letras já inseridas
				strncat(letras_inseridas, &letra, 1);

				//Verifica se o palpite está correto
				int acertos = revelar_letra(mascara, palavra_secreta, letra);
				if (acertos > 0) {
					printf("Voce acertou!\n");
					pontos += 2 * acertos; //Adiciona pontos para um palpite correto, considerando todas as ocorrências da letra
				} else {
					printf("Letra errada!\n");
					tentativas_restantes--; //Diminui o número de tentativas restantes
					pontos--; //Diminui pontos para um palpite errado
					//sleep(1);
					mostrar_forca(MAX_TENTATIVAS - tentativas_restantes); //Desenha o estado atual da forca
				}
			}
			//Verifica se o jogador ganhou ou perdeu
			if (palavra_completa(mascara)) {
				printf("Parabens, voce adivinhou a palavra: %s\n", palavra_secreta);
			} else {
				printf("Game Over! \nA palavra era: %s\n", palavra_secreta);
				break;
			}
			printf("Pontuacao final: %d\n", pontos);
			if (pontos > 0) {
				printf("Vitoria!\n");
			} else {
				printf("Game Over!\n");
			}
			break;
		case 2:
			system("cls");
			system("pause");
			break;
	}

	return 0;
}