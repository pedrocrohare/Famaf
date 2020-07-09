#include <stdio.h> /* printf()...           */
#include "set.h"   /* Interfaz del TAD set  */
#include <stdlib.h>

static void
print_set(set s)
{
    /* Muestra por pantalla el contenido de un conjunto de enteros */
    /*
     * Es crucial que las funciones:
     *   - set_copy()
     *   - set_get()
     *   - set_elim()
     *   - set_is_empty()
     *
     * estén bien programadas para que se muestre correctamente.
     */
    set saux = set_copy(s);
    printf("{");
    while (!set_is_empty(saux))
    {
        type_elem e;
        e = set_get(saux);
        printf("%i", e);
        saux = set_elim(saux, e);
        if (!set_is_empty(saux))
            printf(", ");
    }
    printf("}");
    saux = set_destroy(saux);
}

static void
show_status(set s, const char *name)
{
    /*
     * Muestra por pantalla: - La etiquena 'name'
     *                       - El contendio del conjunto
     *                       - Su longitud
     *                       - Si es o no vacío
     */
    /* Se muestra la etiqueta */
    printf("{ %s == ", name);
    /* Se muestra el contenido del conjunto */
    print_set(s);
    printf(" /\\ ");
    /* Se muestra el cardinal */
    printf("|%s| = %i /\\ ", name, set_cardinal(s));
    /* Se indica si es vacío o no */
    if (set_is_empty(s))
        printf("empty");
    else
        printf("not empty");
    printf(" }");
    printf("\n\n");
}

int main()
{
    printf("\n\n\n");
    printf("Usando set_empty, set_add, y dos ciclos, inicializo los conjuntos s1 y s2, quedan así:\n\n");
    set s1 = set_empty();
    set s2 = set_empty();
    for (unsigned int i = 0; i < 23; i += 2){
        s1 = set_add(s1,i);
    }
    for (unsigned int  i = 15; i < 30; i++){
        s2 = set_add(s2,i);
    }
    
    show_status(s1,"Set 1");
    printf("\n");
    show_status(s2,"Set 2");


    printf("\n\nComputo inters(s1,s2), se guarda en c1: \n\n");
    s1 = set_inters(s1,s2);
    show_status(s1,"Set 1");
    printf("\n");
    show_status(s2,"Set 2");

    printf("\n\nComputo dif(s2,s1), y la guardo en s2: \n\n");
    s2 = set_dif(s2,s1);
    show_status(s1,"Set 1");
    printf("\n");
    show_status(s2,"Set 2");

    printf("\n\nComputo get(s2), y la imprimo: \n\n");
    int a = set_get(s2);
    printf("\nGet de s2 = %d\n\n",a);

    printf("\nReinicializo los conjuntos con los valores anteriores y calculo su unión y la guardo en s1:\n");
    for (unsigned int i = 0; i < 23; i += 2){
        s1 = set_add(s1,i);
    }
    for (unsigned int  i = 15; i < 30; i++){
        s2 = set_add(s2,i);
    }
    
    show_status(s1,"Set 1");
    printf("\n");
    show_status(s2,"Set 2");

    s1 = set_union(s1,s2);
    show_status(s1,"Set s1 unión s2");


    printf("\nDestruyo a los sets y los imprimo:\n\n");
    
    s1 = set_destroy(s1);
    s2 = set_destroy(s2);
    show_status(s1,"S1");
    show_status(s2,"S2");

    printf("\nComo las demás funciones (member, set_is_empty, etc...) están siendo usadas por las anterior probadas, no veo necesario explicitar que funcionan, ya que las que probamos funcionan.\n\n\n");

    return 0;
}
