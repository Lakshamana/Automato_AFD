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
                            if(read != ',' && read != '}')
                                if(!seek_alfa(alfa, read))
                                    add_alfa(&alfa, read);
                        }
                    break;
                    case 2:
                        read_est(&file, &kest);
                    break;
                    case 3:
                        read_est(&file, &kfinals);
                    break;
                }
            }
        }
    }
    read_trule(&file, &rule, alfa, kest);
    printf("Alfabeto:\n");
    show_alfa(alfa);
    printf("\nConjunto total de estados:\n");
    show_est(kest);
    printf("\nConjunto dos estados finais:\n");
    show_est(kfinals);
    printf("\nEstado inicial: %s", q);
    printf("\nRegras:\n");
    show_trule(rule);

    printf("Digite a palavra: ");
    read_user_word(&w, alfa);
    if(automate(w, rule, &autom_st, kfinals))
        printf("ACEITA");
    else
        printf("RECUSADA");
    fclose(file);
    system("pause");
    return 0;
}
