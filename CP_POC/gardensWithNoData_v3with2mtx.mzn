%Az összes beépített fgv meg egyéb fontos dolog használatához a "globals.mzn" file belinkelése
include "globals.mzn";

%Bemenő paraméterek: kertek száma, termények száma
int: kertek;
int: termenyek;

%Indexelésre használt halmazok
set of int: Kertek = 1..kertek;
set of int: Termenyek = 1.. termenyek;
set of int: Tulaj = 1..kertek;

%Segédhalmazok a termények kategóriáihoz, feltételeknél használjuk
set of int: Gyumolcsok;
set of int: Zoldsegek;
set of int: Viragok;

%Nagy bináris mátrix, megadja hogy melyik kertben mit termesztenek
array[Termenyek, Kertek] of var {0, 1}: termeszt;

%mátrix a kertek és tulajok kapcsolatához
array[Kertek, Tulaj] of var {0, 1}: tulaj;

%Termények nevei, majd a kiíratáshoz fog kelleni
array[Termenyek] of string: termenyNev;

%Tulajdonosok nevei, szintén kiíratáshoz kell majd
array[Kertek] of string: tulajNev;

% +1 extra feltétel: egy embernek pontosan 1 kertje van(azaz minden tulaj különböző)
constraint forall(k in Kertek)(sum(t in Tulaj)(tulaj[k,t])=1);
constraint forall(t in Tulaj)(sum(k in Kertek)(tulaj[k,t])=1);

% 2. Everybody grows exactly 4 different varieties
constraint forall(k in Kertek)(sum(t in Termenyek)(termeszt[t,k])=4);

% 3. Each variety is at least in one garden.
constraint forall(t in Termenyek)(sum(k in Kertek)(termeszt[t,k])>=1);

% 4. Only one variety is in 4 gardens.
constraint exactly(1, [sum(k in Kertek)(termeszt[t, k]) | t in Termenyek], 4);

% 5. Only in one garden are all 3 kinds of crops.
constraint exactly(1, [bool2int(sum(z in Zoldsegek)(termeszt[z, k])>0 /\ sum(gy in Gyumolcsok)(termeszt[gy, k])>0 /\ sum(v in Viragok)(termeszt[v, k])>0) | k in Kertek], 1);

% 6. Only in one garden are all 4 varieties of one kind of crops.
constraint exactly(1, [bool2int(sum(z in Zoldsegek)(termeszt[z, k])=4 \/ sum(gy in Gyumolcsok)(termeszt[gy, k])=4 \/ sum(v in Viragok)(termeszt[v, k])=4) | k in Kertek], 1);

% 7. Pear is only in the two border gardens.
constraint termeszt[2,1]=1;
constraint termeszt[2,kertek]=1;
constraint forall(k in 2..kertek-1)(termeszt[2,k]=0);

% 8. Paul's garden is in the middle with no lily.
constraint termeszt[12,3]=0;
constraint tulaj[3,4]=1;

% 9. Aster grower doesn't grow vegetables.
constraint forall(k in Kertek, z in Zoldsegek)(termeszt[9,k]=1 -> termeszt[z,k]=0);

% 10. Rose growers don't grow parsley.
constraint forall(k in Kertek)(termeszt[10,k]=1 -> termeszt[6,k]=0);

% 11. Nuts grower has also gourd and parsley.
constraint forall(k in Kertek)(termeszt[3,k]=1 -> termeszt[7,k]=1 /\ termeszt[6,k]=1);

% 12. In the first garden are apples and cherries.
constraint termeszt[1,1]=1;
constraint termeszt[4,1]=1;

% 13. Only in two gardens are cherries.
constraint sum(k in Kertek)(termeszt[4,k])=2;

% 14. Sam has onions and cherries.
constraint forall(k in Kertek)(tulaj[k,2]=1 -> termeszt[8,k]=1 /\ termeszt[4,k]=1);

% 15. Luke grows exactly two kinds of fruit.
constraint forall(k in Kertek)(tulaj[k,1]=1 -> sum(gy in Gyumolcsok)(termeszt[gy,k])=2);

% 16. Tulip is only in two gardens.
constraint sum(k in Kertek)(termeszt[11,k])=2;

% 17. Apple is in a single garden.
constraint sum(k in Kertek)(termeszt[1,k])=1;

% 18. Only in one garden next to Zick's is parsley.
%constraint forall(t in Tulaj)(tulaj[t]=5 -> termeszt[6,t-1]=1 xor termeszt[6,t+1]=1);
constraint sum(k in Kertek)(termeszt[6,k])=1;

% 19. Sam's garden is not on the border.
constraint forall(k in Kertek)(tulaj[1,2]!=1);
constraint forall(k in Kertek)(tulaj[kertek,2]!=1);

% 20. Hank grows neither vegetables nor asters.
constraint forall(k in Kertek)(tulaj[k,3]=1 -> sum(z in Zoldsegek)(termeszt[z,k])=0 /\ termeszt[9,k]=0);

% 21. Paul has exactly three kinds of vegetable.
constraint forall(k in Kertek)(tulaj[k,4]=1 -> sum(z in Zoldsegek)(termeszt[z,k])=3);

solve satisfy;

%output [show(tulajNev[fix(tulaj[1])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,1])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[2])]) ++ ":\t\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,2])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[3])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,3])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[4])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,4])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[5])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,5])=1]++["\n"];