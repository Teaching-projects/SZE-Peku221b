%Az összes beépített fgv meg egyéb fontos dolog használatához a "globals.mzn" file belinkelése
include "globals.mzn";

%Bemenő paraméterek: kertek száma, termények száma
int: kertek=5;
int: noveny=4;

set of int: Kertek = 1..kertek;
set of int: Noveny=1..noveny; %amit termel

%Segédhalmazok a termények kategóriáihoz, feltételeknél használjuk
set of int: Gyumolcsok = 1..4;
set of int: Zoldsegek = 5..8;
set of int: Viragok = 9..12;

% Az adott termények azonosítása
enum TERMENY = {alma, korte, mogyoro, cseresznye, sargarepa, petrezselyem, tok, hagyma, oszirozsa, rozsa, tulipan, liliom};

% Tulajok
enum TULAJ = {Luke, Sam, Hank, Paul, Zick};

%Tulajok és kertek kapcsolata
array[Kertek] of var TULAJ: tulaj;

%Termesztés
array[Kertek, Noveny] of var TERMENY: termeszt;

% +1 extra feltétel: egy embernek pontosan 1 kertje van(azaz minden tulaj különböző)
constraint alldifferent(tulaj);
constraint alldifferent(Kertek);

% 2. Everybody grows exactly 4 different varieties
%%constraint forall(k in Kertek, n in Noveny)(alldifferent(termeszt[k,n]));

% 3. Each variety is at least in one garden.
constraint forall(t in TERMENY, n in Noveny)( at_least(1,[termeszt[k, n] | k in Kertek ], 1));

% 4. Only one variety is in 4 gardens.
%constraint forall(t in TERMENY, n in Noveny)(exactly(1, [(termeszt[k,n]=t) |k in Kertek ], 4));

% 5. Only in one garden are all 3 kinds of crops.
constraint exactly(1, [bool2int(sum(z in Zoldsegek, n in Noveny)(termeszt[k,n]=z)>0 /\ sum(gy in Gyumolcsok, n in Noveny)(termeszt[k,n]=gy)>0 /\ sum(v in Viragok, n in Noveny)(termeszt[k,n]=v)>0) | k in Kertek], 1);

% 6. Only in one garden are all 4 varieties of one kind of crops.
%constraint exactly(1, [bool2int(sum(z in Zoldsegek, n in Noveny)(termeszt[k,n]=z)=26 \/ sum(gy in Gyumolcsok, n in Noveny)(termeszt[k,n]=gy)=10 \/ sum(v in Viragok, n in Noveny)(termeszt[k,n]=v)=42) | k in Kertek], 1);

% 7. Pear is only in the two border gardens.
constraint forall(n in Noveny)(termeszt[1,n]=2);
constraint forall(n in Noveny)(termeszt[5,n]=2);
constraint forall(k in 2..kertek-1, n in Noveny)(termeszt[k,n]!=2);

% 8. Paul's garden is in the middle with no lily.
constraint forall(n in Noveny)(termeszt[3,n]!=12);
constraint tulaj[3]=4;

% 9. Aster grower doesn't grow vegetables.
constraint forall(k in Kertek, z in Zoldsegek, n in Noveny)(termeszt[k,n]=9 -> termeszt[k,n]!=z);

% 10. Rose growers don't grow parsley.
constraint forall(k in Kertek, n in Noveny)(termeszt[k,n]=10 -> termeszt[k,n]!=6);

% 11. Nuts grower has also gourd and parsley.
constraint forall(k in Kertek,n in Noveny)(termeszt[k,n]=3 -> termeszt[k,n]=7 /\ termeszt[k,n]=6);

% 12. In the first garden are apples and cherries.
%constraint forall(n in Noveny)(termeszt[1,n]=1);
%constraint forall(n in Noveny)(termeszt[1,n]=4);

% 13. Only in two gardens are cherries.
%constraint forall(n in Noveny)(exactly(2,[termeszt[k,n]| k in Kertek], 4 ));

% 14. Sam has onions and cherries.
%constraint forall(t in TULAJ, n in Noveny)(tulaj[t]=2 -> termeszt[t,n]=8);
%constraint forall(t in TULAJ, n in Noveny)(tulaj[t]=2 -> termeszt[t,n]=4);

% 15. Luke grows exactly two kinds of fruit.
%constraint forall(gy in Gyumolcsok, n in Noveny)(exactly(2,[tulaj[t]=2 -> termeszt[k,n]=gy | k in Kertek, t in TULAJ], gy));

% 16. Tulip is only in two gardens.
%constraint forall(n in Noveny)(exactly(2,[termeszt[k,n] | k in Kertek ], 11));

% 17. Apple is in a single garden.
constraint forall(n in Noveny)(exactly(1,[termeszt[k,n] | k in Kertek], 1));

% 18. Only in one garden next to Zick's is parsley.
%constraint forall(k in 2..kertek-1,)(tulaj[k]=5 -> (termeszt[k-1]=6)+(termeszt[k+1]=6)=6);
constraint forall(n in Noveny)(tulaj[1]=5 -> termeszt[2,n]=6);
constraint forall(n in Noveny)(tulaj[kertek]=5 -> termeszt[kertek-1,n]=6);
constraint forall(n in Noveny)(exactly(1,[termeszt[k,n] | k in Kertek], 6));

% 19. Sam's garden is not on the border.
constraint tulaj[1]!=2;
constraint tulaj[kertek]!=2;

% 20. Hank grows neither vegetables nor asters.
constraint forall(t in TULAJ, z in Zoldsegek, n in Noveny)(tulaj[t]=3 -> (termeszt[t,n]!=z));
constraint forall(t in TULAJ, n in Noveny)(tulaj[t]=3 -> (termeszt[t,n]!=9));

% 21. Paul has exactly three kinds of vegetable.
%constraint forall(z in Zoldsegek, n in Noveny)(exactly(3, [tulaj[t]=4->termeszt[t,n]=z | t in TULAJ ], z));

solve satisfy;

