
%%% Parameterek

int: maxSzin;        % Hasznalhato szinek szama
int: orszagokSzama;  % Szinezendo orszagok szama

% Generalt halmazok
set of int: Szinek   = 1..maxSzin;
set of int: Orszagok = 1..orszagokSzama;

% Nevek a kiiratashoz
array[Szinek] of string: szinNev;
array[Orszagok] of string: orszagNev;

% Szomszedossagi matrix az orszagokra
array[Orszagok,Orszagok] of int: szomszedos;

%%% Valtozok

% Minden orszaghoz egy valtozo ami megmondja, hogy milyen szinure szinezzuk
array[Orszagok] of var Szinek: szin;

%%% Korlatozasok

constraint forall(o1 in Orszagok, o2 in Orszagok where szomszedos[o1,o2]=1) ( % Minden szomszedos orszag parra:
  szin[o1] != szin[o2] % A szinuk ne legyen azonos
);

% Megoldo meghivasa
solve satisfy;

% Megoldas kiiratasa
output [ show(orszagNev[o]) ++ ": " ++ show(szinNev[fix(szin[o])]) ++ "\n" | o in Orszagok ]