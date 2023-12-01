% library_recommendations.pl

% Define the module
:- module(library_recommendations, [displayRecommendations/0, suggestLibrary/2, main/0]).

% Display library of books recommendations
displayRecommendations :-
    write('Select your first library of books preference:'), nl,
    write('1. Horror Books'), nl,
    write('2. Comedy Books'), nl,
    write('3. Autobiography Books'), nl,
    write('Enter the number of your first library preference: ').

% Suggest a book based on preferences
suggestLibrary(Pref1, Pref2) :-
    (Pref1 = 1, Pref2 = 2, write('Based on your preferences, you might enjoy reading "The Hitchhiker\'s Guide to the Galaxy" by Douglas Adams.'), nl;
    Pref1 = 1, Pref2 = 3, write('Based on your preferences, you might enjoy reading "Becoming" by Michelle Obama.'), nl;
    Pref1 = 2, Pref2 = 1, write('Based on your preferences, you might enjoy reading "The Shining" by Stephen King.'), nl;
    Pref1 = 2, Pref2 = 3, write('Based on your preferences, you might enjoy reading "Becoming" by Michelle Obama.'), nl;
    Pref1 = 3, Pref2 = 1, write('Based on your preferences, you might enjoy reading "The Shining" by Stephen King.'), nl;
    Pref1 = 3, Pref2 = 2, write('Based on your preferences, you might enjoy reading "The Hitchhiker\'s Guide to the Galaxy" by Douglas Adams.'), nl;
    write('Sorry, we couldn\'t provide a specific book suggestion based on your preferences.'), nl).

% Main program
main :-
    displayRecommendations(),
    write('Enter your first library of books preference: '),
    read(Pref1),
    (Pref1 >= 1, Pref1 =< 3 ->
        write('Select your second library of books preference:'), nl,
        write('1. Horror Books'), nl,
        write('2. Comedy Books'), nl,
        write('3. Autobiography Books'), nl,
        write('Enter the number of your second library preference: '),
        read(Pref2),
        (Pref2 >= 1, Pref2 =< 3 ->
            suggestLibrary(Pref1, Pref2);
            write('Invalid second library preference. Please enter a valid preference number.'), nl
        );
        write('Invalid first library preference. Please enter a valid preference number.'), nl).

% Entry point
:- main.