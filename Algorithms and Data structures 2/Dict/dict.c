#include "dict.h"
#include "key_value.h"
#include <stdlib.h>
#include <stdio.h>


struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

dict_t dict_empty() {
    dict_t dict = NULL;
    return dict;
}
static bool dict_is_empty(dict_t dict) {
    return dict == NULL;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    
    if (dict_is_empty(dict)){
        dict = calloc(1,sizeof(struct _node_t));
        dict->key = word;
        dict->value = def; 
        dict->left = dict_empty();
        dict->right = dict_empty(); 
    }else{
        if (key_eq(word,dict->key)){
            dict->value = value_destroy(dict->value);
            dict->key = key_destroy(dict->key);
            dict->value = def;
            dict->key = word;
        } else if (key_less(word,dict->key)){
            dict->left = dict_add(dict->left,word,def);
        } else {
            dict->right = dict_add(dict->right,word,def);
        }
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t value;

    if (key_eq(word,dict->key)){
        value = dict->value;
    } else if (key_less(word,dict->key)){
        value = dict_search(dict->left,word);
    } else {
        value = dict_search(dict->right,word);
    }    
    return value;
}

bool dict_exists(dict_t dict, key_t word) {
    bool res = false;

    if (!dict_is_empty(dict)) {
        if (key_eq(word,dict->key)){
            res = true;
        } else {
            res = dict_exists(dict->left,word) || dict_exists(dict->right,word);
        }
    }
    return res;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;
    
    if (!dict_is_empty(dict)) {
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }

    return length;
}

//Funciones auxiliares para remove
static key_t max_left_key(dict_t dict){
    key_t key;

    if (dict_is_empty(dict->right)) {
        key = dict->key;
    } else{
        key = max_left_key(dict->right);
    }
    return key;
}

static value_t max_left_value(dict_t dict){
    value_t value;

    if (dict_is_empty(dict->right)) {
        value = dict->value;
    } else{
        value = max_left_value(dict->right);
    }
    return value;
}

static dict_t max_left_remove(dict_t dict){
    dict_t daux = dict_empty();    

    if(dict_is_empty(dict->right)){
        daux = dict->left;
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict = daux;
    } else{
        dict->right = max_left_remove(dict->right);
    }

    return dict;
}


dict_t dict_remove(dict_t dict, key_t word) {
    dict_t daux = dict_empty();

    if (key_eq(word,dict->key)){

        if(dict->left == NULL) {
            daux = dict->right;
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);
            dict = daux;
        } else {
            dict->key = max_left_key(dict->left);
            dict->value = max_left_value(dict->left);
            dict->left = max_left_remove(dict->left);
        }
        
    } else if (key_less(word, dict->key)){
        dict->left = dict_remove(dict->left, word);
    } else{
        dict->right = dict_remove(dict->right, word);
    }
    
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    if(!dict_is_empty(dict)){
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict = NULL;
    }
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    if (dict != NULL)
    {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    dict = dict_remove_all(dict);
    return dict;
}
