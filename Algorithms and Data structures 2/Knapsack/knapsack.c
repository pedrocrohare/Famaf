#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "knapsack.h"

static value_t max_value(value_t a, value_t b) {

    return a < b ? b : a;
}

value_t knapsack_backtracking(item_t* items, unsigned int array_length, weight_t max_weight){

    if (items == NULL) {
        return 0;
    }

    //init res because compiler cries otherwise. (he/she has trust issues, I get it)

    value_t res = 0,load,donotload;
    
    if (max_weight == 0){ /* Case 1 */

        res = 0u;

    } else if (array_length == 0 && max_weight > 0) { /* Case 2 */

        res = 0u;

    } else {

        weight_t item_w = item_weight(items[array_length-1]);
        value_t item_v = item_value(items[array_length-1]);

        if ( array_length > 0 && item_w > max_weight) { /* Case 3 */

            res = knapsack_backtracking(items, array_length -1, max_weight);

        } else if (( array_length > 0) && (item_w <= max_weight)) { /* Case 4 */

            load = item_v + knapsack_backtracking(items,array_length-1,max_weight - item_w);
            donotload = knapsack_backtracking(items, array_length -1, max_weight);

            res = max_value(load,donotload);

        }

    }

    return res;
}


value_t knapsack_dynamic(item_t* items, unsigned array_length, weight_t max_weight){

    if (items == NULL) {
        return 0;
    }

    value_t load,donotload;

    //Make the table dynamically allocated.

    value_t **table = calloc(array_length + 1, sizeof(value_t *));

    for (unsigned int i = 0; i <= array_length ; i++){

        table[i] = calloc(max_weight +1, sizeof(value_t));

    }

    //Fill the table
    
    for (unsigned int i = 0; i <= array_length ; i++){ 
        
        table[i][0] = 0;
        
    }

    for (unsigned int i = 1; i <= max_weight ; i++){
        
        table[0][i] = 0;
        
    }

    //Sligthly modified pseudocode, indexing correctly this time.
    
    for (unsigned int i = 1; i <= array_length ; i++){
        
        for (unsigned int j = 1; j <= max_weight ; j++){
            
            value_t item_v = item_value(items[i-1]);
            weight_t item_w = item_weight(items[i-1]);

            if ( item_w > j){
                
                table[i][j] = table[i-1][j];

            } else {

                donotload = table[i-1][j];
                load = item_v + table[i-1][j- item_w];
                table[i][j] = max_value(load,donotload);
            
            }

        }
    }

    value_t res = table[array_length][max_weight];

    //free allocated memory
    for (unsigned int i = 0; i <= array_length; i++){
        free(table[i]);
    }
    free(table);

    return res;

}

value_t knapsack_dynamic_selection(item_t* items, bool* selected, unsigned int array_length, weight_t max_weight){
    
    //Check if there are any items at all.
    if (items == NULL) {
        return 0;
    }

    //Init selected with false, because my sack is empty at the beginning.
    for (unsigned int i = 0; i < array_length; i++){
        selected[i] = false;
    }
    
    value_t load,donotload;

    //Make the table dynamically allocated.

    value_t **table = calloc(array_length + 1, sizeof(value_t *));

    for (unsigned int i = 0; i <= array_length ; i++){

        table[i] = calloc(max_weight +1, sizeof(value_t));

    }

    //Fill the table
    
    for (unsigned int i = 0; i <= array_length ; i++){ 
        
        table[i][0] = 0;
        
    }

    for (unsigned int i = 1; i <= max_weight ; i++){
        
        table[0][i] = 0;
        
    }

    //Sligthly modified pseudocode, indexing correctly this time.
    
    for (unsigned int i = 1; i <= array_length ; i++){
        
        for (unsigned int j = 1; j <= max_weight ; j++){
            
            value_t item_v = item_value(items[i-1]);
            weight_t item_w = item_weight(items[i-1]);

            if ( item_w > j){
                
                table[i][j] = table[i-1][j];

            } else {

                donotload = table[i-1][j];
                load = item_v + table[i-1][j- item_w];
                table[i][j] = max_value(load,donotload);
            
            }
        }
    }

    //Sligthly modified floyd's algorithm

    unsigned int s = max_weight;
    unsigned int r = array_length;

    while (table[r][s] > 0) {

        if (table[r][s] != table[r-1][s]){

            selected[r-1] = true;
            s = s - item_weight(items[r-1]);

        }

        r = r -1;

    }
    
    
    value_t res = table[array_length][max_weight];

    //free allocated memory
    for (unsigned int i = 0; i <= array_length; i++){
        free(table[i]);
    }
    free(table);

    return res;
                                       
}




