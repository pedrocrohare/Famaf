#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>   /* Definition of bool      */
#include "type_elem.h" /* Definition of type_elem */

typedef struct s_set * set;

/* CONSTRUCTORS */

set set_empty(void);
/*
    Pre: {}
    Usage: set s = set_empty(); 
    Pos: {set_cardinal(s) == 0}
*/

set set_add(set s, type_elem e);
/*
    Pre: {set_cardinal(s) == N}
    Usage: s = set_add(s,e);
    Pos: {set_member(e,s) == true /\ set_cardinal(s) == N+1 }
*/

/* OPERATIONS   */

unsigned int set_cardinal(set s);
/*
    Pre: {unsigned int n, set s}
    Usage: n = set_cardinal(s);
    Pos: {n == amount of elements in the set}
*/

bool set_is_empty(set s);
/*
    Pre: {bool e, set s}
    Usage: e = set_is_empty(s);
    Pos: { e == (s == NULL)}
*/

bool set_member(type_elem e, set s);
/*
    Pre: {bool e, set s, type_elem e}
    Usage: e = set_member(s,e);
    Pos: {e == ¿e ∈ s?  }
*/

set set_elim(set s, type_elem e);
/*
    Pre: {set_member(e, s) == true}
    Usage: s = set_elim(s, e);
    Pos: {set_member(e, s) == false}
*/

set set_union(set s, set s0);
/*
    Pre: {set s, set s0}
    Usage: s = set_union(s, s0);
    Pos: {∀ x ∈ s0: x ∈ s}
*/

set set_inters(set s, set s0);
/*
    Pre: {set_cardinal(s0) == N}
    Usage: s = set_inters(s, s0);
    Pos: {set_cardinal(s) == N /\ ∀ x ∉ s0: x ∉ s}
*/

set set_dif(set s, set s0);
/*
    Pre: {}
    Usage: s = set_dif(s, s0);
    Pos: {∀ x ∈ s0: x ∉ s}
*/

type_elem set_get(set s);
/*
    Pre: {type_elem h, set_is_empty(s) != false}
    Usage: h = set_get(s);
    Pos: {set_memeber(h,s) == true}
*/

set set_copy(set s);
/*
    Pre: {set s0}
    Usage: s0 = set_copy(s);
    Pos: {∀ x ∈ s: x ∈ s0 /\ ∀ x ∈ s0: x ∈ s }
*/

set set_destroy(set s);
/*
    Pre: {set_is_empty(s) != NULL}
    Usage: set_is_empty(s)
    Pos: {allocated memory is deallocated}
*/

#endif
