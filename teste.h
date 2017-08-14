#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura de dados para armazenamento do Conjunto de Caracteres (Alafabeto) reconhecidos pelo autômato
typedef struct alfabeto{
	char letra;
	struct alfabeto *prox;
}ALFABETO;

void enfileira_alfa(ALFABETO **p, char letra);
void imprime_alfa(ALFABETO *p);
int vazio_alfa(ALFABETO *p);
int valida_alfa(ALFABETO *p, char letra); //Função para validação de caracter

void enfileira_alfa(ALFABETO **p, char letra){
	ALFABETO *p1 = (ALFABETO*)malloc(sizeof(ALFABETO)), *p2;
	p1->letra = letra;
	p1->prox = NULL;
	
	if ( vazio_alfa(*p) ){
		*p = p1;
	}else{
		p2 = *p;
		while (p2->prox != NULL)
			p2 = p2->prox;
		p2->prox = p1;
	}
}
int vazio_alfa(ALFABETO *p){
	return(p == NULL)?1:0;
}
int valida_alfa(ALFABETO *p, char letra){
	int cont = 0;
	//O laço percorre toda a fila do tipo ALFABETO
	//verificando a existência da letra passada pra função atual
	//no Conjunto Alfabeto
	while( !vazio_alfa(p) ){
		if ( p->letra == letra )
			cont++;
		p = p->prox;
	}
	//Caso exista um correspondente é retornado 1
	return ( cont == 1 )?1:0;
}

void imprime_alfa(ALFABETO *p){
	while( !vazio_alfa(p) ){
		printf("%c ",p->letra);
		p = p->prox;
	}
}

//Estrutura de dados para armazenamento dos conjuntos de estados do autômato
typedef struct estados{
	char estado[4];
	struct estados *prox;
}ESTADO;

void enfileira_est(ESTADO **p, char estado[]);
void imprime_est(ESTADO *p);
int vazio_est(ESTADO *p);
int valida_estado(ESTADO *est, char estado[]);
int valida_conjunto_est(ESTADO *est_princ, ESTADO *est_secun);
void filtra_estados(FILE **fp, ESTADO **p);

void enfileira_est(ESTADO **p, char estado[]){
	ESTADO *p1 = (ESTADO*)malloc(sizeof(ESTADO)), *p2;
	//p1->estado = estado;
	strcpy(p1->estado, estado);
	p1->prox = NULL;
	
	if ( vazio_est(*p) ){
		*p = p1;
	}else{
		p2 = *p;
		while (p2->prox != NULL)
			p2 = p2->prox;
		p2->prox = p1;
	}
}
int vazio_est(ESTADO *p){
	return(p == NULL)?1:0;
}

void imprime_est(ESTADO *p){
	while( !vazio_est(p) ){
		printf("%s ",p->estado);
		p = p->prox;
	}
}

int tam_est(char estado[]){
	int i = 0;
	while(estado[i] != '\0')
		i++;
		
	return i;
}

void filtra_estados(FILE **fp, ESTADO **p){
	char letra = ' ';
	while ( letra != '}' ){
		fscanf(*fp, "%c", &letra);
		if ( letra == 'q' ){
			int cont_est = 0;
			char estado_1[4] = {};		
			estado_1[cont_est] = letra;
			
			while ( letra != ',' && letra != '}' ){
				fscanf(*fp, "%c", &letra);
				if ( letra >= '0' && letra <= '9' || letra == 'f' ){
					cont_est++;
					estado_1[cont_est] = letra;
				}
			}
			if ( tam_est(estado_1) > 1 )
				enfileira_est(&*p,estado_1);
		}
	}
}

int valida_estado(ESTADO *est, char estado[]){
	int cont = 0;
	
	while ( !vazio_est(est) ){
		if ( strcmp(est->estado, estado) == 0 )
			cont++;
		est = est->prox;
	}
	return (cont == 1)?1:0;
}

int valida_conjunto_est(ESTADO *est_princ, ESTADO *est_secun){
	while ( !vazio_est(est_secun) ){
		if ( !valida_estado(est_princ,est_secun->estado) ){
			printf("Estado \'%s' Invalido", est_secun->estado);
			return 0;
		}
		est_secun = est_secun->prox;
	}
	return 1;
}

//Fila que armazena as Regras
typedef struct regras{
	char estado_origem[4];
	char estado_destino[4];
	char letra;
	struct regras *prox;
}REGRA;

int vazio_regra(REGRA *p);
void imprime_regra(REGRA *p);
void enfileira_regra(REGRA **p, char est_origem[], char letra, char est_destino[]);

void enfileira_regra(REGRA **p, char est_origem[], char letra, char est_destino[]){
	REGRA *p1 = (REGRA*)malloc(sizeof(REGRA)), *p2;
	
	strcpy(p1->estado_origem, est_origem);
	strcpy(p1->estado_destino, est_destino);
	p1->letra = letra;
	p1->prox = NULL;
	
	if ( vazio_regra(*p) ){
		*p = p1;
	}else{
		p2 = *p;
		while (p2->prox != NULL)
			p2 = p2->prox;
		p2->prox = p1;
	}
}
int vazio_regra(REGRA *p){
	return(p == NULL)?1:0;
}
void imprime_regra(REGRA *p){
	while( !vazio_regra(p) ){
		printf("%s, %c, %s\n",p->estado_origem, p->letra, p->estado_destino);
		p = p->prox;
	}
}

//Fila das Palavras
typedef struct palavras{
	char letra;
	struct palavras *prox;
}PALAVRA;

void enfileira_palavra(PALAVRA **p, char letra);
void ler_palavra(PALAVRA **p);
void imprime_palavra(PALAVRA *p);
char* prox_estado(REGRA *p, char estado_origem[], char letra);
int tam_palavra(PALAVRA *p);
int vazio_palavra(PALAVRA *p);
void imprime_passo(PALAVRA *p, char estado[], int posi);
void ler_automato(PALAVRA *palavra, REGRA *regra, ESTADO *estados_finais, char estado_inicio[]);
int valida_palavra(PALAVRA *p, ALFABETO *a);

void imprime_passo(PALAVRA *p, char estado[], int posi){
	int i = 0;
	
	while( !vazio_palavra(p) ){
		//printf("(%s,%c) -> %s\n", est_tmp,palavra->letra,estado_inicio);
		if ( posi != i )
			printf("%c",p->letra);		
		else
			printf("{%s,%c}",estado,p->letra);
		i++;
		p = p->prox;
	}
	
	if ( posi == i )
		printf("{%s}",estado);
		
	printf("\n");
}

void ler_automato(PALAVRA *palavra, REGRA *regra, ESTADO *estados_finais, char estado_inicio[]){
	PALAVRA *tmp = palavra;
	
	int tam = tam_palavra(palavra), i;
	char palavra_tmp[tam];
	char est_tmp[4];
	
	printf("Palavra: ");
	imprime_palavra(palavra);
	printf("\n");

	for ( i=0; i<tam; i++ ){		
		if ( prox_estado(regra,estado_inicio,palavra->letra) != NULL ){
			strcpy(est_tmp,estado_inicio);
			strcpy(estado_inicio,prox_estado(regra,estado_inicio,palavra->letra));
			
			palavra = palavra->prox;
		}else{
			imprime_passo(tmp,estado_inicio,i);
			printf("\nPALAVRA NAO ACEITA");
			return;
		}
		imprime_passo(tmp,est_tmp,i);
	}
	
	imprime_passo(tmp,estado_inicio,i);
	if ( valida_estado(estados_finais,estado_inicio) )
		printf("\nPALAVRA ACEITA");
	else
		printf("\nPALAVRA NAO ACEITA");
}

void ler_palavra(PALAVRA **p){
	char letra = ' ';
	
	while (letra != '\n'){
		letra = getchar();
		if (letra != '\n')
			enfileira_palavra(&*p, letra);
	}
}

void enfileira_palavra(PALAVRA **p, char letra){
	PALAVRA *p1 = malloc(sizeof(PALAVRA)), *p2;
	p1->letra = letra;
	p1->prox = NULL;
	
	if ( vazio_palavra(*p) ){
		*p = p1;
	}else{
		p2 = *p;
		while (p2->prox != NULL)
			p2 = p2->prox;
		p2->prox = p1;
	}
}

int vazio_palavra(PALAVRA *p){
	return(p == NULL)?1:0;
}

void imprime_palavra(PALAVRA *p){
	while( !vazio_palavra(p) ){
		printf("%c",p->letra);
		p = p->prox;
	}
}

int tam_palavra(PALAVRA *p){
	int cont=0;
	
	while(!vazio_palavra(p)){
		cont++;
		p = p->prox;
	}
	return cont;
}

int valida_palavra(PALAVRA *p, ALFABETO *a){
	while ( !vazio_palavra(p) ){
		if ( !valida_alfa(a,p->letra) ){
			return 0;
		}			
		p = p->prox;
	}
	return 1;
}

char* prox_estado(REGRA *p, char estado_origem[], char letra){
	while( !vazio_regra(p) ){
		if ( strcmp(estado_origem,p->estado_origem) == 0 && p->letra == letra)
			return p->estado_destino;
		p = p->prox;
	}	
	return NULL;
}
