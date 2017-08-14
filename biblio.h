#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct alf{
    char carac;
    struct alf *prox;
}Alfabeto;

/*
*   int seek_alfa(Alfabeto *ptr);
*   void add_alfa(Alfabeto **ptr, char data);
*   void show_alfa(Alfabeto *ptr);
*   void empty_alfa(Alfabeto *ptr);
*/

int seek_alfa(Alfabeto *ptr, char data){
    if(ptr != NULL)
        while(ptr != NULL){
            if(ptr->carac == data)
                return 1;
            ptr = ptr->prox;
        }
        return 0;
}

void add_alfa(Alfabeto **ptr, char data){
    Alfabeto *p1 = NULL;
    p1 = *ptr;
    if(p1 == NULL){
        p1 = malloc(sizeof(Alfabeto));
        if(p1 != NULL){
            p1->carac = data;
            p1->prox = NULL;
            *ptr = p1;
        }else{
            Alfabeto *p2 = NULL;
            while(p1->prox != NULL)
                p1 = p1->prox;
            p2 = malloc(sizeof(Alfabeto));
            if(p2 != NULL){
                p2->carac = data;
                p1->prox p2;
                p2->prox = NULL;
            }
        }
    }
}

void show_alfa(Alfabeto *ptr){
    while(ptr != NULL){
        printf("%c", ptr->carac);
        ptr = ptr->prox;
    }
}

int empty_alfa(Alfabeto *ptr){
    return (ptr == NULL) ? 1 : 0;
}

typedef struct est{
    char e[5];
    struct est *prox;
}Estado;

/*
*   int seek_est(Estado *ptr, char *data);
*   void add_est(Estado **ptr, char *data);
*   void show_est(Estado *ptr);
*   void empty_alfa(Estado *ptr);
*   void read_est(FILE **file, Estado **ptr);
*   int a_subof_b(Estado *p1, Estado *p2);
*/

int seek_est(Estado *ptr, char *data){
    if(ptr != NULL)
        while(ptr != NULL){
            if(strcmp(ptr->e, data) == 0)
                return 1;
               ptr = ptr->prox;
        }
    return 0;
}

void add_est(Estado **ptr, char *data){
    Estado *p1 = NULL;
    p1 = *ptr;
    if(p1 == NULL){
        p1 = malloc(sizeof(Estado));
        if(p1 != NULL){
            strcpy(p1->e, data);
            p1->prox = NULL;
            *ptr = p1;
        }else{
            Estado *p2 = NULL;
            while(p1->prox != NULL)
                p1 = p1->prox;
            p2 = malloc(sizeof(Estado));
            if(p2 != NULL){
                strcpy(p2->e, data);
                p1->prox p2;
                p2->prox = NULL;
            }
        }
    }
}

void show_est(Estado *ptr){
    while(ptr != NULL){
        printf("%s", ptr->e);
        ptr = ptr->prox;
    }
}

void empty_est(Estado *ptr){
    return (ptr == NULL) ? 1 : 0;
}

void read_est(FILE **file, Estado **ptr){
    char read = ' ';
    while(read != '}'){
        fscanf(*file, "%c", &read);
        if(read == 'q'){
            char get[5];
            int i = 0;
            while(read != ','){
                fscanf(*file, "%c", &read);
                get[i] = read;
                i++;
            }
        }
        if(!seek_est(ptr, ptr->e))
            add_est(ptr, ptr->e);
    }
}

int a_subof_b(Estado *p1, Estado *p2){
    if(p2 != NULL)
        while(p2 != NULL){
            if(seek_est(p1, p2->e))
                return 1;
            p2 = p2->prox;
        }
    return 0;
}

typedef struct rule{
   char e_in[5];
   char e_out[5];
   char carac;
   struct rule *prox;
}TRule;


/*
*   void add_trule(TRule **ptr, char *ei, char *eo, char data);
*   int empty_trule(TRule *ptr);
*   int al1final(TRule *p1, Estado *p2);
*   void show_trule(TRule *ptr);
*   seek_trule(TRule *ptr);
*   read_trule(FILE **file, TRule **ptr);
*/

void add_trule(TRule **ptr, char *ei, char data, char *eo){
    TRule *p1 = NULL;
    p1 = *ptr;
    if(p1 == NULL){
        p1 = malloc(sizeof(TRule));
        if(p1 != NULL){
            p1->carac = data;
            strcpy(p1->e_in, ei);
            strcpy(p1->e_out, eo);
            p1->prox = NULL;
            *ptr = p1;
        }else{
            TRule *p2 = NULL;
            while(p1->prox != NULL)
                p1 = p1->prox;
            p2 = malloc(sizeof(TRule));
            if(p2 != NULL){
                p2->carac = data;
                strcpy(p2->e_in, ei);
                strcpy(p2->e_out, eo);
                p1->prox p2;
                p2->prox = NULL;
            }
        }
    }
}

void show_trule(TRule *ptr){
    while(ptr != NULL){
        printf("%s, %s, %s", ptr->e_in, ptr->carac, ptr->e_out);
        ptr = ptr->prox;
    }
}

int empty_trule(TRule *ptr){
    return (ptr == NULL) ? 1 : 0;
}

int seek_trule(TRule *ptr, char *ei, char c, char *eo){
    if(ptr != NULL)
        while(p1 != NULL){
            if(strcmp(ptr->e_in, ei) == 0 && ptr->carac == c && strcmp(ptr->e_out, eo) == 0)
                return 1;
            ptr = ptr->prox;
        }
    return 0;
}

int al1final(TRule *p1, Estado *p2){
    if(p1 != NULL)
        while(p1 != NULL){
            if(seek_est(p2, p1->e_out)) //A lista de estados especificada (p2) é a lista de estados finais.
                return 1;
            p1 = p1->prox;
        }
    return 0;
}

void read_trule(FILE **file, TRule **ptr){
    char ei[5], c, eo[5];
    while(fscanf(*file, "%s %s %s", ei, c, eo) != EOF){

    }
}
