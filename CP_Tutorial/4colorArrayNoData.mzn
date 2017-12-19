int: maxSzin;
int: orszagokSzama;

set of int: Szinek   = 1..maxSzin;
set of int: Orszagok = 1..orszagokSzama;

array[Szinek] of string: szinNev;
array[Orszagok] of string: orszagNev;

array[Orszagok,Orszagok] of int: szomszedos;

array[Orszagok] of var Szinek: szin;

constraint forall(o1 in Orszagok, o2 in Orszagok where szomszedos[o1,o2]=1) (
  szin[o1] != szin[o2]
);

solve satisfy;

output [ show(orszagNev[o]) ++ ": " ++ show(szinNev[fix(szin[o])]) ++ "\n" | o in Orszagok ]