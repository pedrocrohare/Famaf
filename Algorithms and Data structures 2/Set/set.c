#include "set.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>

struct s_set {
    list ord_list;
};

set set_empty(void){

    set set= malloc(sizeof(struct s_set));

    set->ord_list = list_empty();

    return set;
}

set set_add(set s, type_elem e){

    unsigned int n = 0u;
    list laux = list_copy(s->ord_list);
    bool is_member = false;
    type_elem d;

    while (!list_is_empty(laux) && !is_member){
        d = list_head(laux);

        if (d == e){
            is_member = true;
        } else if (d<e){
            n += 1;
        }
        
        laux = list_tail(laux);
    }

    if (! is_member){
        s->ord_list = list_add_at(s->ord_list,n,e);
    }
    
    list_destroy(laux);
    return s;
}

unsigned int set_cardinal(set s){
    return list_length(s->ord_list);
}

bool set_is_empty(set s){
    bool res = list_is_empty(s->ord_list);

    return res;
}

bool set_member(type_elem e, set s){

    list laux = list_copy(s->ord_list);
    bool is_member = false;
    type_elem d;

    while (!list_is_empty(laux) && !is_member){
        d = list_head(laux);

        if (d == e) {
            is_member = true;
        }

        laux = list_tail(laux);
    }
    
    laux = list_destroy(laux);
    return is_member;
}

set set_elim(set s, type_elem e){

    unsigned int n = 0u;
    list laux = list_copy(s->ord_list);
    bool is_member = false;
    type_elem d;

    while (!list_is_empty(laux) && !is_member){
        d = list_head(laux);

        if (d == e){
            is_member = true;
        } else if (d<e){
            n += 1;
        }
        
        laux = list_tail(laux);
    }

    if (is_member){
        s->ord_list = list_elim_at(s->ord_list,n);
    }
    
    list_destroy(laux);
    return s;
}

set set_union(set s, set s0){

    list laux = list_copy(s0->ord_list);
    type_elem d;

    while (!list_is_empty(laux)){
        d = list_head(laux);
        if (!set_member(d,s)){
            s = set_add(s,d);
        }
        laux = list_tail(laux);
    }
    
    laux = list_destroy(laux);
    return s;
}

set set_inters(set s, set s0){

    list laux = list_copy(s->ord_list);
    type_elem d;

    while (!list_is_empty(laux)){
        d = list_head(laux);

        if (!set_member(d,s0)){
            s = set_elim(s,d);
        }

        laux = list_tail(laux);
    }

    laux = list_destroy(laux);
    return s;
}

set set_dif(set s, set s0){

    list laux = list_copy(s->ord_list);
    type_elem d;

    while (!list_is_empty(laux)){
        d = list_head(laux);

        if (set_member(d,s0)){
            s = set_elim(s,d);
        }

        laux = list_tail(laux);
    }

    laux = list_destroy(laux);
    return s;
}

type_elem set_get(set s){
    assert(!set_is_empty(s));
    return list_head(s->ord_list);
}

set set_copy(set s){
    set copy = set_empty();
    copy->ord_list = list_copy(s->ord_list);
    return copy;
}

set set_destroy(set s){
    s->ord_list = list_destroy(s->ord_list);
    free(s);
    return s;
}
