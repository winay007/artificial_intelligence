% Facts
male(john).
male(robert).
male(michael).
male(william).
female(mary).
female(jennifer).
female(susan).
female(linda).
parent(john, robert).
parent(mary, robert).
parent(jennifer, john).
parent(william, john).
parent(john, michael).
parent(mary, michael).

% Define the mother and father predicates
mother(X, Y) :- female(X), parent(X, Y).
father(X, Y) :- male(X), parent(X, Y).

% Define the grandmother and grandfather predicates
grandmother(X, Z) :- mother(X, Y), parent(Y, Z).
grandfather(X, Z) :- father(X, Y), parent(Y, Z).

% Define the sibling predicate
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% Define the ancestor predicate to display all ancestors
ancestor(X, Y) :-
    findall(A, all_ancestors(X, Y, A), Ancestors),
    display_ancestors(X, Y, Ancestors).

all_ancestors(X, Y, [X, Y]) :-
    parent(X, Y).
all_ancestors(X, Y, [X | Rest]) :-
    parent(X, Z),
    all_ancestors(Z, Y, Rest).

% Helper predicate to display the list of ancestors
display_ancestors(X, Y, Ancestors) :-
    write("Ancestors of "), write(X), write(" and "), write(Y), write(": "), nl,
    print_ancestor_list(Ancestors).

print_ancestor_list([]).
print_ancestor_list([A | Rest]) :-
    write(A), nl,
    print_ancestor_list(Rest).

% Print all siblings of a person
print_all_siblings(Person) :-
    findall(S, sibling(S, Person), Siblings),
    write("All siblings of "), write(Person), write(": "), write(Siblings), nl.

% Print the entire family tree
print_family_tree(X) :- 
    write(X), write("'s family tree:\n"),
    write("Parents: "), findall(P, parent(P, X), Parents), write(Parents), nl,
    write("Siblings: "), findall(S, sibling(S, X), Siblings), write(Siblings), nl,
    write("Grandparents: "), findall(G, (grandmother(G, X); grandfather(G, X)), Grandparents), write(Grandparents), nl.