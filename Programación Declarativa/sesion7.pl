% EDURNE RUIZ HUGUET

% EJERCICIO 1
% Arbol(X, I, D) ↔ X es la raíz de un arbol binario que tiene como hijo izquierdo al también árbol binario I e hijo derecho al árbol binario D.

% maximo(A, X) ↔ A es un arbol binario de numeros enteros positivos dado y X es el elemento maximo de sus nodos. X vale 0 si el arbol es vacio.
% funcion auxiliar: max(X,Y,Z) ↔ Z es el máximo entre X e Y.
arbol(elem, izq, dcho).

maximo(void, 0).
maximo(arbol(R,IZQ, DCH),M) :- integer(R), R > 0, maximo(IZQ,M1), maximo(DCH,M2), (max(M1,M2,M1) -> max(M1,R,M); max(M2,R,M)). 

max(X,Y,X) :- X > Y, !.
max(X,Y,Y) :- X =< Y.

% EJERCICIO 2
% sublista(SXs,Xs) ↔ SXs es una sublista de la lista Xs.
% funciones auxiliares: prefijo(Xs, Ys) ↔ Xs es un prefijo de la lista Ys; sufijo(Xs, Ys) ↔ Xs es un sufijo de la lista Ys
% las necesitamos ya que una sublista SXs de Xs es el prefijo de un sufijo de Xs.

prefijo([], _).
prefijo([X|Xs], [X|Ys]):- prefijo(Xs, Ys).

sufijo(Xs, Xs).
sufijo(Xs, [_|Ys]) :- sufijo(Xs, Ys).

sublista([], _).
sublista(SL, L) :- sufijo(S, L), prefijo(SL, S).

% sublistas(LSX,Xs) ↔ LSX es la lista que contiene a todas las sublistas de Xs
sublistas(LSX, Xs) :- setof(Xss, sublista(Xss, Xs), LSX).

% EJERCICIO 3
% aplana(Xss, Xs) ↔ Xs es la lista que resulta de eliminar todos los corchetes en los subterminos de la lista Xss que sean listas

aplanar([],[]) :- !.
aplanar([X|Xs],L) :- !, aplanar(X,X1), aplanar(Xs,X2), junta(X1,X2,L).
aplanar(X,[X]).

junta([],X,X) :- !.
junta([X|Xs],Y,[X|Zs]) :- junta(Xs,Y,Zs).

% EJERCICIO 4
% hanoi(N, A, B, C, M) donde N es el num de fichas que hay que mover de la torre inicial, A es el nombre de la torre inicial, B es el nombre de la torre final, C es el nombre de la torre auxiliar y M es la
% secuencia de pares de movimientos de una torre a otra, hasta conseguir la traslacion de todas las fichas

mueve(1, X, _ , Z, [(X, Z)]).
mueve(N, X, Y, Z, P) :- M is (N - 1), mueve(M, X, Z, Y, P1), mueve(1, X, Y, Z, P2), mueve(M, Y, X, Z, P3), append(P1, P2, Q), append(Q, P3, P).



















