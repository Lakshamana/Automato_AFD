#include "biblio.h"
#include <locale.h>

int main() {
    FILE *file;
    Alfabeto *alfa = NULL;
    Alfabeto *w = NULL;
    Estado *kest = NULL;
    Estado *autom_st = NULL;
    Estado *kfinals = NULL;
    TRule *rule = NULL;
    char read = ' ', qi[5], qf[5], *q;
    int i = 0, j = 0;
    setlocale(LC_ALL, "portuguese");
    file = fopen("automato2.txt", "r");

    if(file == NULL){
        printf("Arquivo inexistente!");
        return 0;
    }else{
        while(read != ')'){
            fscanf(file, "%c", &read);
            if(read == ',')
                j++;
            if(j == 3){
                fscanf(file, "%s", qi);
                q = cutcommas(qi);
                if(seek_est(kest, q))
                    add_est(&autom_st, q);
                else{
                    printf("Estado inicial inexistente!");
                    return 0;
                }
                j++;
            }
            if(read == '{'){
                i++;
                switch(i){
                    case 1:
                        while(read != '}'){
                            fscanf(file, "%c", &read);
                            if(read != ',' && read != '}' && read != ' ')
                                if(!seek_alfa(alfa, read))
                                    add_alfa(&alfa, read);
                        }
                    break;
                    case 2:
                        read_est(&file, &kest);
                        if(!a_supof_b(kest, kest))
                            return 0;
                    break;
                    case 3:
                        read_est(&file, &kfinals);
                        if(!a_supof_b(kest, kfinals) || !a_supof_b(kfinals, kfinals))
                            return 0;
                    break;
                }
            }
        }
    }
    read_trule(&file, &rule, alfa, kest);
    if(!al1final(rule, kfinals)){
        printf("Pelo menos um estado de destino deve ser um estado final!");
        return 0;
    }
    printf("Alfabeto:\n");
    if(empty_alfa(alfa)){
        printf("\nAlfabeto vazio!");
        return 0;
    }
    show_alfa(alfa);
    printf("\n\nConjunto total de estados:\n");
    if(empty_est(kest)){
        printf("Conjunto de estados vazio!");
        return 0;
    }
    show_est(kest);
    printf("\n\nConjunto dos estados finais:\n");
    if(empty_est(kfinals)){
        printf("Conjunto de estados finais vazio!");
        return 0;
    }
    show_est(kfinals);
    printf("\n\nEstado inicial: %s", q);
    if(empty_est(autom_st)){
        printf("Estado inicial inexistente!");
        return 0;
    }
    printf("\n\nRegras:\n");
    if(empty_trule(rule)){
        printf("Conjunto de regras vazio!");
        return 0;
    }
    show_trule(rule);
    printf("\nDigite a palavra: ");
    if(!read_user_word(&w, alfa))
    	return 0;
	else{
        if(automate(w, rule, &autom_st, kfinals))
            printf("\nACEITA\n\nEstados percorridos:\n");
        else
            printf("\nRECUSADA\n\nEstados percorridos:\n");
        show_alfa(w);
        printf("\n");
        show_est(autom_st);
    }
    fclose(file);
    system("PAUSE");
	getchar();
    return 0;
}
