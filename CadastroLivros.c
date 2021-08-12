#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <conio.c>
#define TAM 1000
#define TAMTITULO 100
#define TAMAUTOR 100
#define TAMTEXTO 1000
#define ARQUIVO "livros.txt"

//Declaração de Funções

void limpaBuffer();
void pausar();
int strLen(char texto[]);
void mensagem(char texto[]);
void backup();

//Estruturas

struct livro{
	char titulo[TAMTITULO];
	char autor[TAMAUTOR];
	int volume;
	int edicao;
};

struct coluna{
	char texto[20];
	int tamanho;
} colunas[5] = {{"Codigo", 6}, {"Titulo", 6}, {"Autor", 5}, {"Volume", 6}, {"Edicao", 6}};

struct livro livros[TAM];

//Variaveis

int contadorLivros = 0;
char op = '\0';
char titulo[TAMTITULO] = {'\0'};
char autor[TAMAUTOR] = {'\0'};
int volume = 0;
int edicao = 0;
int codigo = 0;
char texto[TAMTEXTO] = {'\0'};
char opConf = '\0';
char dados[TAMTEXTO] = {'\0'};
int i = 0, j = 0;

void main(void) {
	setlocale(LC_ALL, "portuguese");
	
	backup(); //Carregando os dados de um arquivo
	
	do{
		textcolor(6);
		mensagem("SISTEMA DA BIBLIOTECA");
		textcolor(7);
		
		puts("\tC - CADASTRAR LIVRO");
		puts("\tE - EDITAR LIVRO");
		puts("\tD - DELETAR LIVRO");
		puts("\tB - BUSCAR LIVRO");
		
		printf("\n\tDigite sua opção: ");
		op = fgetc(stdin);
		limpaBuffer();
		
		//Verificando a opção selecinada
		
		switch(toupper(op)){
			case 'C':
				clrscr();
				
				//Titulo
				
				do{
					textcolor(6);
					mensagem("CADASTRAR LIVRO");
					textcolor(7);
					
					printf("\n Digite o titulo do livro: ");
					fgets(texto, TAMTITULO, stdin);
					limpaBuffer();
					
					texto[strLen(texto) - 1] = '\0';
					
					if(strLen(texto) == 0){
						textcolor(4);
						mensagem("DIGITE O TITULO DO LIVRO!");
						textcolor(7);
						pausar();
					}
					
					clrscr();
				}while(strLen(texto) == 0);
				
				strcpy(titulo, texto);
				strcpy(texto, "");
				
				//Nome do autor
				
				do{
					textcolor(6);
					mensagem("CADASTRAR LIVRO");
					textcolor(7);
					
					printf("\n Digite o nome do autor do livro: ");
					fgets(texto, TAMAUTOR, stdin);
					limpaBuffer();
					
					texto[strLen(texto) - 1] = '\0';
					
					if(strLen(texto) == 0){
						textcolor(4);
						mensagem("DIGITE O NOME DO AUTOR DO LIVRO!");
						textcolor(7);
						pausar();
					}
					
					clrscr();
				}while(strLen(texto) == 0);
				
				strcpy(autor, texto);
				strcpy(texto, "");
				
				//Volume
				
				do{
					textcolor(6);
					mensagem("CADASTRAR LIVRO");
					textcolor(7);
					
					printf("\n Digite o volume do livro: ");
					scanf("%[0-9]s", &texto);
					limpaBuffer();
					
					if(strLen(texto) == 0){
						textcolor(4);
						mensagem("DIGITE O VOLUME DO LIVRO!");
						textcolor(7);
						pausar();
					}
					
					clrscr();
				}while(strLen(texto) == 0);
				
				volume = atoi(texto);
				strcpy(texto, "");
				
				//Edição
				
				do{
					textcolor(6);
					mensagem("CADASTRAR LIVRO");
					textcolor(7);
					
					printf("\n Digite a edição do livro: ");
					scanf("%[0-9]s", &texto);
					limpaBuffer();
					
					if(strLen(texto) == 0){
						textcolor(4);
						mensagem("DIGITE A EDIÇÃO DO LIVRO!");
						textcolor(7);
						pausar();
					}
					
					clrscr();
				}while(strLen(texto) == 0);
				
				edicao = atoi(texto);
				strcpy(texto, "");
				
				textcolor(6);
				mensagem("CADASTRAR LIVRO");
				textcolor(7);
				
				printf("\n--- DADOS DO LIVRO ---\n\n");
				printf(" TITULO: %s\n", titulo);
				printf(" AUTOR: %s\n", autor);
				printf(" VOLUME: %i\n", volume);
				printf(" EDIÇÃO: %i\n", edicao);
				printf("------------------------\n");
				
				opConf = '\0';
				
				printf("\n Deseja finalizar o cadastro[S-N]: ");
				opConf = fgetc(stdin);
				setbuf(stdin, NULL);
				
				if(toupper(opConf) == 'S'){
					//Salvando os dados no vetor de struct
							
					strcpy(livros[contadorLivros].titulo, titulo);
					strcpy(livros[contadorLivros].autor, autor);
					livros[contadorLivros].volume = volume;
					livros[contadorLivros].edicao = edicao;
					
					//Salvando os dados no arquivo de backup
					
					FILE *file = fopen(ARQUIVO, "a");
					
					if(file == NULL){
						file = fopen(ARQUIVO, "w");
					}
					
					strcpy(dados, titulo);
					strcat(dados, "\n");
					strcat(dados, autor);
					strcat(dados, "\n");
					sprintf(texto, "%i", volume);
					strcat(dados, texto);
					strcat(dados, "\n");
					sprintf(texto, "%i", edicao);
					strcat(dados, texto);
					strcat(dados, "\n");	
					
					fprintf(file, dados);
					
					fclose(file);
					
					contadorLivros++;
					
					textcolor(2);
					mensagem("LIVRO CADASTRADO COM SUCESSO!");
					textcolor(7);
				}else{
					textcolor(4);
					mensagem("LIVRO NÃO CADASTRADO, O CADASTRO FOI CANCELADO!");
					textcolor(7);
				}
				
				pausar();
				
				break;
			case 'E':
				clrscr();
				
				strcpy(titulo, "");
				strcpy(autor, "");
				volume = 0;
				edicao = 0;
				
				textcolor(6);
				mensagem("EDITAR LIVRO");
				textcolor(7);
						
				printf("\n Digite o código do livro: ");
				scanf("%[0-9]i", &texto);
				setbuf(stdin, NULL);
				
				if(strlen(texto) > 0){
					codigo = atoi(texto);
					codigo--;
				}else{
					codigo = -1;
				}
				
				clrscr();
					
				if(codigo >= 0 && codigo < contadorLivros){
					textcolor(6);
					mensagem("EDITAR LIVRO");
					textcolor(7);
					
					printf("\n--- DADOS DO LIVRO SELECIONADO ---\n\n");
					printf(" TITULO: %s\n", livros[codigo].titulo);
					printf(" AUTOR: %s\n", livros[codigo].autor);
					printf(" VOLUME: %i\n", livros[codigo].volume);
					printf(" EDIÇÃO: %i\n", livros[codigo].edicao);
					printf("\n----------------------------------\n\n");
					
					printf(" OBS: Só informe os dados dos campos em que você deseja editar,\n já os campos em que você não quer editar,\n basta pressionar ENTER.\n");
					
					//Titulo
						
					printf("\n Digite o titulo do livro: ");
					fgets(texto, TAMTITULO, stdin);
					limpaBuffer();
					
					texto[strLen(texto) - 1] = '\0';
					
					strcpy(titulo, texto);
					strcpy(texto, "");
					
					//Nome do autor
						
					printf("\n Digite o nome do autor do livro: ");
					fgets(texto, TAMAUTOR, stdin);
					limpaBuffer();
						
					texto[strLen(texto) - 1] = '\0';
					
					strcpy(autor, texto);
					strcpy(texto, "");
					
					//Volume
						
					printf("\n Digite o volume do livro: ");
					scanf("%[0-9]s", &texto);
					limpaBuffer();
					
					volume = atoi(texto);
					strcpy(texto, "");
					
					//Edição
						
					printf("\n Digite a edição do livro: ");
					scanf("%[0-9]s", &texto);
					limpaBuffer();
					
					edicao = atoi(texto);
					strcpy(texto, "");
					
					clrscr();
					
					//Verificando quais dados não foram preenchidos
					
					if(strlen(titulo) == 0){
						strcpy(titulo, livros[codigo].titulo);
					}
					
					if(strlen(autor) == 0){
						strcpy(autor, livros[codigo].autor);
					}
					
					if(volume == 0){
						volume = livros[codigo].volume;
					}
					
					if(edicao == 0){
						edicao = livros[codigo].edicao;
					}
					
					//Finalização da edição
					
					textcolor(6);
					mensagem("EDITAR LIVRO");
					textcolor(7);
					
					printf("\n--- DADOS DO LIVRO ---\n\n");
					printf(" TITULO: %s\n", titulo);
					printf(" AUTOR: %s\n", autor);
					printf(" VOLUME: %i\n", volume);
					printf(" EDIÇÃO: %i\n", edicao);
					printf("------------------------\n");
					
					opConf = '\0';
					
					printf("\n Deseja finalizar a edição[S-N]: ");
					opConf = fgetc(stdin);
					setbuf(stdin, NULL);
					
					if(toupper(opConf) == 'S'){
						//Salvando os dados no vetor de struct
								
						strcpy(livros[codigo].titulo, titulo);
						strcpy(livros[codigo].autor, autor);
						livros[codigo].volume = volume;
						livros[codigo].edicao = edicao;
						
						//Salvando os dados no arquivo de backup
						
						FILE *file = fopen(ARQUIVO, "w");
						
						strcpy(dados, "");
						
						for(i = 0; i < contadorLivros; i++){
							strcat(dados, livros[i].titulo);
							strcat(dados, "\n");
							strcat(dados, livros[i].autor);
							strcat(dados, "\n");
							sprintf(texto, "%i", livros[i].volume);
							strcat(dados, texto);
							strcat(dados, "\n");
							sprintf(texto, "%i", livros[i].edicao);
							strcat(dados, texto);
							strcat(dados, "\n");
						}	
						
						fprintf(file, dados);
						
						fclose(file);
						
						textcolor(2);
						mensagem("LIVRO EDITADO COM SUCESSO!");
						textcolor(7);
					}else{
						textcolor(4);
						mensagem("LIVRO NÃO EDITADO, A EDIÇÃO FOI CANCELADA!");
						textcolor(7);
					}
				}else{
					textcolor(4);
					mensagem("CÓDIGO INVÁLIDO");
					textcolor(7);
				}
				
				pausar();
				
				break;
			case 'D':
				clrscr();
				
				strcpy(titulo, "");
				strcpy(autor, "");
				volume = 0;
				edicao = 0;
				
				textcolor(6);
				mensagem("EDITAR LIVRO");
				textcolor(7);
						
				printf("\n Digite o código do livro: ");
				scanf("%[0-9]i", &texto);
				setbuf(stdin, NULL);
				
				if(strlen(texto) > 0){
					codigo = atoi(texto);
					codigo--;
				}else{
					codigo = -1;
				}
				
				clrscr();
					
				if(codigo >= 0 && codigo < contadorLivros){
					textcolor(6);
					mensagem("DELETAR LIVRO");
					textcolor(7);
					
					printf("\n--- DADOS DO LIVRO SELECIONADO ---\n\n");
					printf(" TITULO: %s\n", livros[codigo].titulo);
					printf(" AUTOR: %s\n", livros[codigo].autor);
					printf(" VOLUME: %i\n", livros[codigo].volume);
					printf(" EDIÇÃO: %i\n", livros[codigo].edicao);
					printf("\n----------------------------------\n\n");
					
					opConf = '\0';
					
					printf("\n Deseja finalizar a exclusão[S-N]: ");
					opConf = fgetc(stdin);
					setbuf(stdin, NULL);
					
					if(toupper(opConf) == 'S'){
						//Salvando os dados no vetor de struct
						
						for(i = codigo; i < contadorLivros; i++){	
							strcpy(livros[i].titulo, livros[i + 1].titulo);
							strcpy(livros[i].autor, livros[i + 1].autor);
							livros[i].volume = livros[i + 1].volume;
							livros[i].edicao = livros[i + 1].edicao;
						}
						
						contadorLivros--;
						
						//Salvando os dados no arquivo de backup
						
						FILE *file = fopen(ARQUIVO, "w");
						
						strcpy(dados, "");
						
						for(i = 0; i < contadorLivros; i++){
							strcat(dados, livros[i].titulo);
							strcat(dados, "\n");
							strcat(dados, livros[i].autor);
							strcat(dados, "\n");
							sprintf(texto, "%i", livros[i].volume);
							strcat(dados, texto);
							strcat(dados, "\n");
							sprintf(texto, "%i", livros[i].edicao);
							strcat(dados, texto);
							strcat(dados, "\n");
						}	
						
						fprintf(file, dados);
						
						fclose(file);
						
						textcolor(2);
						mensagem("LIVRO DELETADO COM SUCESSO!");
						textcolor(7);
					}else{
						textcolor(4);
						mensagem("LIVRO NÃO DELETADO, A EXCLUSÃO FOI CANCELADA!");
						textcolor(7);
					}
				}else{
					textcolor(4);
					mensagem("CÓDIGO INVÁLIDO");
					textcolor(7);
				}
				
				pausar();
				break;
			case 'B':
				do{
					clrscr();
				
					textcolor(6);
					mensagem("BUSCAR LIVRO");
					textcolor(7);
							
					puts(" C - CÓDIGO");
					puts(" V - VISUALIZAR TUDO");
					puts(" S - SAIR");
					
					printf("\n Digite sua opção: ");
					opConf = fgetc(stdin);
					setbuf(stdin, NULL);
					
					switch(toupper(opConf)){
						case 'C':
							printf("\n Digite o código do livro: ");
							scanf("%[0-9]i", &texto);
							setbuf(stdin, NULL);
							
							if(strlen(texto) > 0){
								codigo = atoi(texto);
								codigo--;
							}else{
								codigo = -1;
							}
								
							if(codigo >= 0 && codigo < contadorLivros){		
								sprintf(texto, "%i", codigo);
								
								if(strlen(texto) > colunas[0].tamanho){
									colunas[0].tamanho = strlen(texto);
								}
								
								if(strlen(livros[codigo].titulo) > colunas[1].tamanho){
									colunas[1].tamanho = strlen(livros[codigo].titulo);
								}
								
								if(strlen(livros[codigo].autor) > colunas[2].tamanho){
									colunas[2].tamanho = strlen(livros[codigo].autor);
								}
								
								sprintf(texto, "%i", livros[codigo].volume);
								
								if(strlen(texto) > colunas[3].tamanho){
									colunas[3].tamanho = strlen(texto);
								}
								
								sprintf(texto, "%i", livros[codigo].edicao);
								
								if(strlen(texto) > colunas[4].tamanho){
									colunas[4].tamanho = strlen(texto);
								}
								
								int tam = 0;
								
								for(i = 0; i < 5; i++){
									tam += colunas[i].tamanho + 1;
								}
								
								//Desenhado as colunas
								
								for(i = 0; i < tam; i++){
									printf("-");
								}
								
								printf("\n");
								
								for(i = 0; i < 5; i++){
									printf("%s", colunas[i].texto);
										
									for(j = strlen(colunas[i].texto); j < colunas[i].tamanho; j++){
										printf(" ");
									}
									
									printf("|");
								}
								
								printf("\n");
								
								for(i = 0; i < tam; i++){
									printf("-");
								}
								
								//Desenhando linhas
								
								printf("\n");
								
								//Codigo
								
								sprintf(texto, "%i", (codigo + 1));
								
								printf("%s", texto);
								
								for(j = strlen(texto); j < colunas[0].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Titulo
								
								printf("%s", livros[codigo].titulo);
								
								for(j = strlen(livros[codigo].titulo); j < colunas[1].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Autor
								
								printf("%s", livros[codigo].autor);
								
								for(j = strlen(livros[codigo].autor); j < colunas[2].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Volume
								
								sprintf(texto, "%i", livros[codigo].volume);
								
								printf("%s", texto);
								
								for(j = strlen(texto); j < colunas[3].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Edição
								
								sprintf(texto, "%i", livros[codigo].edicao);
								
								printf("%s", texto);
								
								for(j = strlen(texto); j < colunas[3].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								printf("\n");
								
								for(i = 0; i < tam; i++){
									printf("-");
								}
								
								printf("\n\n");
							}else{
								textcolor(4);
								mensagem("CÓDIGO INVÁLIDO");
								textcolor(7);
							}
							
							pausar();
							clrscr();
							break;
						case 'V':	
							for(i = 0; i < contadorLivros; i++){
								sprintf(texto, "%i", i);
								
								if(strlen(texto) > colunas[0].tamanho){
									colunas[0].tamanho = strlen(texto);
								}
								
								if(strlen(livros[i].titulo) > colunas[1].tamanho){
									colunas[1].tamanho = strlen(livros[i].titulo);
								}
								
								if(strlen(livros[i].autor) > colunas[2].tamanho){
									colunas[2].tamanho = strlen(livros[i].autor);
								}
								
								sprintf(texto, "%i", livros[i].volume);
								
								if(strlen(texto) > colunas[3].tamanho){
									colunas[3].tamanho = strlen(texto);
								}
								
								sprintf(texto, "%i", livros[i].edicao);
								
								if(strlen(texto) > colunas[4].tamanho){
									colunas[4].tamanho = strlen(texto);
								}
							}
							
							int tam = 0;
							
							for(i = 0; i < 5; i++){
								tam += colunas[i].tamanho + 1;
							}
							
							
							//Desenhado as colunas
							
							for(i = 0; i < tam; i++){
								printf("-");
							}
							
							printf("\n");
							
							for(i = 0; i < 5; i++){
								printf("%s", colunas[i].texto);
									
								for(j = strlen(colunas[i].texto); j < colunas[i].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
							}
							
							printf("\n");
							
							for(i = 0; i < tam; i++){
								printf("-");
							}
							
							//Desenhando linhas
							
							printf("\n");
							
							for(i = 0; i < contadorLivros; i++){
								//Codigo
								
								sprintf(texto, "%i", (i + 1));
								
								printf("%s", texto);
								
								for(j = strlen(texto); j < colunas[0].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Titulo
								
								printf("%s", livros[i].titulo);
								
								for(j = strlen(livros[i].titulo); j < colunas[1].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Autor
								
								printf("%s", livros[i].autor);
								
								for(j = strlen(livros[i].autor); j < colunas[2].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Volume
								
								sprintf(texto, "%i", livros[i].volume);
								
								printf("%s", texto);
								
								for(j = strlen(texto); j < colunas[3].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								//Edição
								
								sprintf(texto, "%i", livros[i].edicao);
								
								printf("%s", texto);
								
								for(j = strlen(texto); j < colunas[3].tamanho; j++){
									printf(" ");
								}
								
								printf("|");
								
								printf("\n");
							}
							
							for(i = 0; i < tam; i++){
								printf("-");
							}
							
							printf("\n\n");
							
							pausar();
							clrscr();
							
							break;
					}
				}while(toupper(opConf) != 'S');
				
				clrscr();
				
				break;
			default:
				clrscr();
				textcolor(4);
				mensagem("OPÇÃO INVÁLIDA!");
				textcolor(7);
				pausar();
		}
		
		clrscr();
	}while(true);
}

//Funções

void limpaBuffer(){
	char c = '\0';
	
	while((c = getchar()) != '\n' && c != EOF);
}

void pausar(){
	printf("Pressione qualquer tecla para continuar..."); getch();
}

int strLen(char texto[]){
	int tamanho = 0;
	
	while(texto[tamanho] != '\0'){
		tamanho++;
	}
	
	return tamanho;
}

void mensagem(char texto[]){
	int ponta = 8;
	int i = 0;
	int tamanhoLinha = (ponta * 2) + strLen(texto);
	
	printf("\n");
	
	for(i = 0; i < tamanhoLinha; i++){
		printf("-");
	}
	
	printf("\n\n");
	
	for(i = 0; i < ponta; i++){
		printf(" ");
	}
	
	printf(texto);
	
	printf("\n\n");
	
	for(i = 0; i < tamanhoLinha; i++){
		printf("-");
	}
	
	printf("\n\n");
}

void backup(){
	FILE *file;
	
	file = fopen(ARQUIVO, "r");
	
	int i = 0;
	char texto[TAMTEXTO] = {'\0'};
	
	if(file != NULL){
		while(fgets(texto, TAMTEXTO, file) != NULL){
			texto[strlen(texto) - 1] = '\0'; //Removendo o \n
			
			if(i > 3){
				i = 0;
			}
			
			if(i == 0){
				strcpy(livros[contadorLivros].titulo, texto);
			}else if(i == 1){
				strcpy(livros[contadorLivros].autor, texto);
			}else if(i == 2){
				livros[contadorLivros].volume = atoi(texto);
			}else if(i == 3){
				livros[contadorLivros].edicao = atoi(texto);
				contadorLivros++;
			}
			
			i++;
		}
	}else{
		fopen(ARQUIVO, "w");
	}
	
	fclose(file);
}
