#include "teste.h"

int main()
{
	FILE *fp;
	ALFABETO *alf = NULL;
	ESTADO *est = NULL;
	ESTADO *est_finais = NULL;
	REGRA *regra = NULL;
	PALAVRA *palavra = NULL;
	char letra = ' ', estado_inicio[4], estado_fim[4];
	int cont = 0, cont_virg = 0;

	fp = fopen("automato2.txt", "r");

	while ( letra != ')' ){
		fscanf(fp, "%c", &letra);

		if ( letra == ',' )
			cont_virg++;

		if ( cont_virg == 3 ){
			fscanf(fp, "%s", estado_inicio);
			estado_inicio[strlen(estado_inicio)-1] = '\0'; //elimina virgula do fim da String

			if ( !valida_estado(est,estado_inicio) ){
				printf("Estado Inicial Invalido!");
				return 0;
			}
			cont_virg++;
		}

		if (letra == '{'){
			cont++;

			switch(cont){
				case 1:
					while ( letra != '}' ){
						fscanf(fp, "%c", &letra);
						if ( letra >= 'a' && letra <= 'z' ){
							if ( valida_alfa(alf,letra) ){
								printf("Elemento \'%c' Repetido", letra);
								return 0;
							}
							enfileira_alfa(&alf,letra);
						}
					}
					break;
				case 2:
					filtra_estados(&fp,&est);
					if ( !valida_conjunto_est(est,est) ){
						return 0;
					}
					break;
				case 3:
					filtra_estados(&fp,&est_finais);
					if ( !valida_conjunto_est(est,est_finais) || !valida_conjunto_est(est_finais,est_finais)){
						return 0;
					}
					break;
				default:
					printf("ERRO!");
			}
		}
	}

	char est_origem[4], elemento[3], est_destino[4];
	while( fscanf(fp, "%s %s %s", est_origem, elemento, est_destino) != EOF ){
		//elimina a ',' (vírgula) da string
		est_origem[strlen(est_origem)-1] = '\0';
		elemento[strlen(elemento)-1] = '\0';

		if ( valida_alfa(alf,elemento[0]) && valida_estado(est,est_origem) && valida_estado(est,est_destino) ) {
			enfileira_regra(&regra, est_origem, elemento[0], est_destino);
		}else{
			printf("Regra \'%s, %s, %s' invalida!",est_origem, elemento, est_destino);
			return 0;
		}
	}

	printf("Alfabeto: ");
	imprime_alfa(alf);
	printf("\nEstados: ");
	imprime_est(est);
	printf("\nEstado Inicial: %s", estado_inicio);
	printf("\nEstados Finais: ");
	imprime_est(est_finais);
	printf("\nRegras: \n");
	imprime_regra(regra);
	fclose(fp);

	printf("\nInforme a palavra: ");
	ler_palavra(&palavra);

	if ( valida_palavra(palavra,alf) )
		ler_automato(palavra,regra,est_finais,estado_inicio);
	else
		printf("PALAVRA NAO ACEITA");
	printf("\n");
	system("pause");
	return 0;
}


