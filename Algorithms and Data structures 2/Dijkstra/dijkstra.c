#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "cost.h"
#include "graph.h"
#include "set.h"

static cost_t min_cost(cost_t c1, cost_t c2){

	cost_t min = c2;

	if (cost_lt(c1,c2))
	{
		min = c1;
	}

	return min;
}

static type_elem min_vert(set s0, cost_t a[]){

	set s = set_copy(s0);
	cost_t min = cost_inf();
	type_elem min_i = 0;


	while (!set_is_empty(s)){

		type_elem d = set_get(s);
		if (cost_le(a[d],min)){

			min = a[d];
			min_i = d;

		}
		s = set_elim(s,d);
			
	}
	s = set_destroy(s);	

	return min_i;

}



cost_t *dijkstra(graph_t graph, vertex_t init){

	// Declaro variables iniciales
	cost_t *resultado = calloc(graph_max_size(graph),sizeof(int));
	unsigned int c,d;
	set C;
	C = set_empty();

	// Añado al set auxiliar todos los "vertices" y elimino el inicial
	for (unsigned int i = 0; i < graph_max_size(graph) ; i++) {
		
		C = set_add(C,i);

	}
	C = set_elim(C,init);

	// Añado al resultado los costes preliminares desde vértice inical a cada otro vértice del grafo
	for (unsigned int i = 0; i < graph_max_size(graph) ; i++){

		resultado[i] = graph_get_cost(graph,init,i);

	}

	// Calculo los costes mínimos y los voy actualizando si encuentro uno menor (de init a v_i)
	while (!set_is_empty(C)){

		// Elijo elemento c de C tal que Resultado[c] sea mínimo y luego lo elimino de C porque ya habré calculado su costo al final de esta iteración

		c = min_vert(C,resultado);
		
		set aux = set_copy(C);
		
		C = set_elim(C,c);

		while (!set_is_empty(aux)){

			d = set_get(aux);

			cost_t different_cost = cost_sum(resultado[c],graph_get_cost(graph,c,d));
			cost_t current_cost = resultado[d];

			resultado[d] = min_cost(current_cost,different_cost);

			aux = set_elim(aux,d);

		}
		
	aux = set_destroy(aux);

	}

	C = set_destroy(C);

	return resultado;

}




