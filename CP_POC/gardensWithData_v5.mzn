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

% 2. Everybody grows exactly 4 DIFFERENT varieties
%constraint forall(k in Kertek)(alldifferent([termeszt[k,n] | n in Noveny]));
%constraint forall(k in Kertek, n1 in Noveny, n2 in n1..noveny-1)(termeszt[k, n1] != termeszt[k, n2+1]);
% There are no difference in permutations
constraint forall(k in Kertek, n in 1..noveny-1)(termeszt[k,n] < termeszt[k,n+1]);

% 3. Each variety is at least in one garden.
constraint forall(t in TERMENY)(at_least(1, [termeszt[k, n] | k in Kertek, n in Noveny], t));

% 4. Only one variety is in 4 gardens.
%constraint forall(t in TERMENY, n in Noveny)(exactly(1, [(termeszt[k,n]=t) |k in Kertek ], 4));
constraint exactly(1, [count([termeszt[k,n] | k in Kertek, n in Noveny], t) | t in TERMENY], 4);

% 5. Only in one garden are all 3 kinds of crops.
%constraint exactly(1, [bool2int(sum(z in Zoldsegek, n in Noveny)(termeszt[k,n]=z)>0 /\ sum(gy in Gyumolcsok, n in Noveny)(termeszt[k,n]=gy)>0 /\ sum(v in Viragok, n in Noveny)(termeszt[k,n]=v)>0) | k in Kertek], 1);
constraint exactly(1, [bool2int(sum(gy in Gyumolcsok)(count([termeszt[k, n] | n in Noveny], TERMENY[gy]))>0 /\ sum(z in Zoldsegek)(count([termeszt[k, n] | n in Noveny], TERMENY[z]))>0 /\ sum(v in Viragok)(count([termeszt[k, n] | n in Noveny], TERMENY[v]))>0) | k in Kertek], 1);

% 6. Only in one garden are all 4 varieties of one kind of crops.
%constraint exactly(1, [bool2int(sum(z in Zoldsegek, n in Noveny)(termeszt[k,n]=z)=26 \/ sum(gy in Gyumolcsok, n in Noveny)(termeszt[k,n]=gy)=10 \/ sum(v in Viragok, n in Noveny)(termeszt[k,n]=v)=42) | k in Kertek], 1);
constraint exactly(1, [bool2int(sum(gy in Gyumolcsok)(count([termeszt[k, n] | n in Noveny], TERMENY[gy]))=4 \/ sum(z in Zoldsegek)(count([termeszt[k, n] | n in Noveny], TERMENY[z]))=4 \/ sum(v in Viragok)(count([termeszt[k, n] | n in Noveny], TERMENY[v]))=4) | k in Kertek], 1);

% 7. Pear is only in the two border gardens.
constraint exactly(1, [termeszt[1, n] | n in Noveny], korte);
constraint exactly(1, [termeszt[kertek, n] | n in Noveny], korte);
constraint forall(k in 2..kertek-1, n in Noveny)(termeszt[k, n] != korte);

% 8. Paul's garden is in the middle with no lily.
constraint forall(n in Noveny)(termeszt[3,n] != liliom);
constraint tulaj[3] = Paul;

% 9. Aster grower doesn't grow vegetables.
%constraint forall(k in Kertek, z in Zoldsegek, n in Noveny)(termeszt[k,n]=9 -> termeszt[k,n]!=z);
constraint forall(k in Kertek)(count([termeszt[k, n] | n in Noveny], oszirozsa)=1 -> exactly(0, [count([termeszt[k, n] | n in Noveny], TERMENY[z]) | z in Zoldsegek], 1));

% 10. Rose growers don't grow parsley.
%constraint forall(k in Kertek, n in Noveny)(termeszt[k,n]=10 -> termeszt[k,n]!=6);
constraint forall(k in Kertek)(count([termeszt[k, n] | n in Noveny], rozsa)=1 -> count([termeszt[k, n] | n in Noveny], petrezselyem)=0);

% 11. Nuts grower has also gourd and parsley.
%constraint forall(k in Kertek,n in Noveny)(termeszt[k,n]=3 -> termeszt[k,n]=7 /\ termeszt[k,n]=6);
constraint forall(k in Kertek)(count([termeszt[k, n] | n in Noveny], mogyoro)=1 -> count([termeszt[k, n] | n in Noveny], petrezselyem)=1 /\ count([termeszt[k, n] | n in Noveny], tok)=1);

% 12. In the first garden are apples and cherries.
constraint exactly(1, [termeszt[1,n] | n in Noveny], alma);
constraint exactly(1, [termeszt[1,n] | n in Noveny], cseresznye);

% 13. Only in two gardens are cherries.
constraint exactly(2, [termeszt[k,n] | k in Kertek, n in Noveny], cseresznye);

% 14. Sam has onions and cherries.
%constraint forall(t in TULAJ, n in Noveny)(tulaj[t]=2 -> termeszt[t,n]=8);
%constraint forall(t in TULAJ, n in Noveny)(tulaj[t]=2 -> termeszt[t,n]=4);
constraint forall(k in Kertek)(tulaj[k]=Sam -> count([termeszt[k, n] | n in Noveny], hagyma)=1);
constraint forall(k in Kertek)(tulaj[k]=Sam -> count([termeszt[k, n] | n in Noveny], cseresznye)=1);

% 15. Luke grows exactly two kinds of fruit.
%constraint forall(gy in Gyumolcsok, n in Noveny)(exactly(2,[tulaj[t]=2 -> termeszt[k,n]=gy | k in Kertek, t in TULAJ], gy));
constraint forall(k in Kertek)(tulaj[k]=Luke -> exactly(2, [count([termeszt[k, n] | n in Noveny], TERMENY[gy]) | gy in Gyumolcsok], 1));

% 16. Tulip is only in two gardens.
constraint exactly(2, [termeszt[k,n] | k in Kertek, n in Noveny], tulipan);

% 17. Apple is in a single garden.
constraint exactly(1, [termeszt[k,n] | k in Kertek, n in Noveny], alma);

% 18. Only in one garden next to Zick's is parsley.
%constraint forall(k in 2..kertek-1,)(tulaj[k]=5 -> (termeszt[k-1]=6)+(termeszt[k+1]=6)=6);
%constraint forall(n in Noveny)(tulaj[1]=5 -> termeszt[2,n]=6);
%constraint forall(n in Noveny)(tulaj[kertek]=5 -> termeszt[kertek-1,n]=6);
%constraint forall(n in Noveny)(exactly(1,[termeszt[k,n] | k in Kertek], 6));
constraint exactly(1, [termeszt[k,n] | k in Kertek, n in Noveny], petrezselyem);
constraint tulaj[1]=Zick -> count([termeszt[2, n] | n in Noveny], petrezselyem)=1;
constraint tulaj[kertek]=Zick -> count([termeszt[kertek-1, n] | n in Noveny], petrezselyem)=1;
constraint forall(k in 2..kertek-1)(tulaj[k]=Zick -> count([termeszt[k-1, n] | n in Noveny], petrezselyem)+count([termeszt[k+1, n] | n in Noveny], petrezselyem)=1);

% 19. Sam's garden is not on the border.
constraint tulaj[1] != Sam;
constraint tulaj[kertek] != Sam;

% 20. Hank grows neither vegetables nor asters.
%constraint forall(t in TULAJ, z in Zoldsegek, n in Noveny)(tulaj[t]=3 -> (termeszt[t,n]!=z));
%constraint forall(t in TULAJ, n in Noveny)(tulaj[t]=3 -> (termeszt[t,n]!=9));
constraint forall(k in Kertek)(tulaj[k]=Hank -> exactly(0, [count([termeszt[k, n] | n in Noveny], TERMENY[z]) | z in Zoldsegek], 1));
constraint forall(k in Kertek)(tulaj[k]=Hank -> count([termeszt[k, n] | n in Noveny], oszirozsa)=0);

% 21. Paul has exactly three kinds of vegetable.
%constraint forall(z in Zoldsegek, n in Noveny)(exactly(3, [tulaj[t]=4->termeszt[t,n]=z | t in TULAJ ], z));
constraint forall(k in Kertek)(tulaj[k]=Paul -> exactly(3, [count([termeszt[k, n] | n in Noveny], TERMENY[z]) | z in Zoldsegek], 1));

solve satisfy;

int: width = -15;
output [show(fix(tulaj[1])) ++ ":\t"]++[format(width, show(fix(termeszt[1, n]))) | n in Noveny]++["\n"];
output [show(fix(tulaj[2])) ++ ":\t"]++[format(width, show(fix(termeszt[2, n]))) | n in Noveny]++["\n"];
output [show(fix(tulaj[3])) ++ ":\t"]++[format(width, show(fix(termeszt[3, n]))) | n in Noveny]++["\n"];
output [show(fix(tulaj[4])) ++ ":\t"]++[format(width, show(fix(termeszt[4, n]))) | n in Noveny]++["\n"];
output [show(fix(tulaj[5])) ++ ":\t"]++[format(width, show(fix(termeszt[5, n]))) | n in Noveny]++["\n"];