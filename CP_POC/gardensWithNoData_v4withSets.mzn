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
array[Kertek] of var set of Termenyek: termeszt;

%Tömb az adott sorszámú kert tulajdonosának azonosítására
array[Kertek] of var Tulaj: tulaj;

%Termények nevei, majd a kiíratáshoz fog kelleni
array[Termenyek] of string: termenyNev;

%Tulajdonosok nevei, szintén kiíratáshoz kell majd
array[Kertek] of string: tulajNev;

% +1 extra feltétel: egy embernek pontosan 1 kertje van(azaz minden tulaj különböző)
constraint alldifferent(tulaj);

% 2. Everybody grows exactly 4 different varieties
constraint forall(k in Kertek)(card(termeszt[k])=4);

% 3. Each variety is at least in one garden.
constraint card(array_union(termeszt))=termenyek;

% 4. Only one variety is in 4 gardens.
constraint exactly(1, [sum(bool2int([t in termeszt[k] | k in Kertek])) | t in Termenyek], 4);

% 5. Only in one garden are all 3 kinds of crops.
constraint exactly(1, [bool2int(card(termeszt[k] intersect Zoldsegek)>0 /\ card(termeszt[k] intersect Gyumolcsok)>0 /\ card(termeszt[k] intersect Viragok)>0) | k in Kertek], 1);

% 6. Only in one garden are all 4 varieties of one kind of crops.
constraint exactly(1, [bool2int(card(termeszt[k] intersect Zoldsegek)=4 \/ card(termeszt[k] intersect Gyumolcsok)=4 \/ card(termeszt[k] intersect Viragok)=4) | k in Kertek], 1);

% 7. Pear is only in the two border gardens.
constraint 2 in termeszt[1];
constraint 2 in termeszt[kertek];
constraint forall(k in 2..kertek-1)(not(2 in termeszt[k]));

% 8. Paul's garden is in the middle with no lily.
constraint not(12 in termeszt[3]);
constraint tulaj[3]=4;

% 9. Aster grower doesn't grow vegetables.
constraint forall(k in Kertek, z in Zoldsegek)(9 in termeszt[k] -> card(Zoldsegek intersect termeszt[k])=0);

% 10. Rose growers don't grow parsley.
constraint forall(k in Kertek)(10 in termeszt[k] -> not(6 in termeszt[k]));

% 11. Nuts grower has also gourd and parsley.
constraint forall(k in Kertek)(3 in termeszt[k] -> 7 in termeszt[k] /\ 6 in termeszt[k]);

% 12. In the first garden are apples and cherries.
constraint 1 in termeszt[1];
constraint 4 in termeszt[1];

% 13. Only in two gardens are cherries.
%constraint exactly(2, termeszt, 4..4);

% 14. Sam has onions and cherries.
constraint forall(t in Tulaj)(tulaj[t]=2 -> 8 in termeszt[t] /\ 4 in termeszt[t]);

% 15. Luke grows exactly two kinds of fruit.
constraint forall(t in Tulaj)(tulaj[t]=1 -> card(Gyumolcsok intersect termeszt[t])=2);

% 16. Tulip is only in two gardens.
%constraint exactly(2, termeszt, 11..11);

% 17. Apple is in a single garden.
%constraint exactly(1, termeszt, 1..1);

% 18. Only in one garden next to Zick's is parsley.
constraint forall(k in 1..kertek-1)(tulaj[k]=5 -> 6 in termeszt[k+1]) xor forall(k in 2..kertek)(tulaj[k]=5 -> 6 in termeszt[k-1]);

% 19. Sam's garden is not on the border.
constraint tulaj[1]!=2;
constraint tulaj[kertek]!=2;

% 20. Hank grows neither vegetables nor asters.
constraint forall(t in Tulaj)(tulaj[t]=3 -> card(Zoldsegek intersect termeszt[t])=0 /\ not(9 in termeszt[t]));

% 21. Paul has exactly three kinds of vegetable.
constraint forall(t in Tulaj)(tulaj[t]=4 -> card(Zoldsegek intersect termeszt[t])=3);

solve satisfy;

%output [show(tulajNev[fix(tulaj[1])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,1])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[2])]) ++ ":\t\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,2])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[3])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,3])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[4])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,4])=1]++["\n"];
%output [show(tulajNev[fix(tulaj[5])]) ++ ":\t"]++[show(termenyNev[t]) ++ " " | t in Termenyek where fix(termeszt[t,5])=1]++["\n"];