#include "biblio.h"
#include <locale.h>

int main(){
    FILE *file;
    Alfabeto *alfa = NULL;
    Estado *kest = NULL;
    Estado *autom_st = NULL;
    Estado *kfinal_st = NULL;
    TRule *rule = NULL;
    char read = ' ', qi[5], qf[5];
    int alt = 0, v = 0;
    setlocale(LC_ALL, "portuguese");
    
}
