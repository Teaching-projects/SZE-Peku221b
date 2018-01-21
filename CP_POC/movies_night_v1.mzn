include "globals.mzn";

%Bemenő paraméter és segédhalmaz az indexeléshez: hány ember van
int: db;
set of int: Db = 1..db;

%A tulajdonságok nevei a kiíratáshoz
array[Db] of string: shirtData;
array[Db] of string: nameData;
array[Db] of string: movieData;
array[Db] of string: snackData;
array[Db] of string: ageData;

%Tulajdonságonként egy bináris mtx
array[Db, Db] of var {0, 1}: shirt;
array[Db, Db] of var {0, 1}: name;
array[Db, Db] of var {0, 1}: movie;
array[Db, Db] of var {0, 1}: snack;
array[Db, Db] of var {0, 1}: age;

%Mindegyik mtx minden sor- és oszlopösszege 1
constraint forall(d1 in Db)(sum(d2 in Db)(shirt[d1, d2])=1 /\ sum(d2 in Db)(shirt[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(name[d1, d2])=1 /\ sum(d2 in Db)(name[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(movie[d1, d2])=1 /\ sum(d2 in Db)(movie[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(snack[d1, d2])=1 /\ sum(d2 in Db)(snack[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(age[d1, d2])=1 /\ sum(d2 in Db)(age[d2, d1])=1);

%Joshua is in one of the ends.
constraint name[2,1]+name[2,db]=1;