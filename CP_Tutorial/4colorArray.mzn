int: maxSzin = 4;
int: orszagokSzama = 6;

set of int: Szinek   = 1..maxSzin;
set of int: Orszagok = 1..orszagokSzama;

array[Szinek] of string: szinNev = ["Green", "Yellow", "Red", "Blue"];
array[Orszagok] of string: orszagNev = ["Belgium", "Denmark", "France", "Germany", "Holland", "Luxemburg"];

array[Orszagok] of var Szinek: szin;

constraint szin[1] != szin[3];
constraint szin[1] != szin[4];
constraint szin[1] != szin[5];
constraint szin[1] != szin[6];
constraint szin[2] != szin[4];
constraint szin[3] != szin[4];
constraint szin[3] != szin[6];
constraint szin[4] != szin[5];
constraint szin[4] != szin[6];

solve satisfy;

output [ show(orszagNev[o]) ++ ": " ++ show(szinNev[fix(szin[o])]) ++ "\n" | o in Orszagok ]
