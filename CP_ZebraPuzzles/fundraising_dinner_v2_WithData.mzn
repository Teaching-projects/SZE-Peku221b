include "globals.mzn";

%Bemenő paraméter és segédhalmaz az indexeléshez: hány ember van
int: db = 5;
set of int: Db = 1..db;

int: Carmen = 1;
int: Diana = 2;
int: Jane = 3;
int: Lidia = 4;
int: Melissa = 5;

int: black = 1;
int: blue = 2;
int: purple = 3;
int: red = 4;
int: white = 5;

int: tenthousand = 1;
int: twentythousand = 2;
int: thirtythousand = 3;
int: fourtythousand = 4;
int: fiftythousand = 5;

int: cosmopolitan = 1;
int: daiquiri = 2;
int: manhattan = 3;
int: margarita = 4;
int: martini = 5;

int: emerald = 1;
int: moonstone = 2;
int: pearl = 3;
int: sapphire = 4;
int: turquoise = 5;

int: fourty = 1;
int: fourtyfive = 2;
int: fifty = 3;
int: fiftyfive = 4;
int: sixty = 5;

%A tulajdonságok nevei a kiíratáshoz
array[Db] of string: dressData = ["black", "blue", "purple", "red", "white"];
array[Db] of string: nameData = ["Carmen", "Diana", "Jane", "Lidia", "Melissa"];
array[Db] of string: donationData = ["$10,000", "$20,000", "$30,000", "$40,000", "$50,000"];
array[Db] of string: cocktailData = ["cosmopolitan", "daiquiri", "manhattan", "margarita", "martini"];
array[Db] of string: necklaceData = ["emerald", "moonstone", "pearl", "sapphire", "turquoise"];
array[Db] of string: ageData = ["40", "45", "50", "55", "60"];

%Tulajdonságonként egy bináris mtx
array[Db, Db] of var {0, 1}: dress;
array[Db, Db] of var {0, 1}: name;
array[Db, Db] of var {0, 1}: donation;
array[Db, Db] of var {0, 1}: cocktail;
array[Db, Db] of var {0, 1}: necklace;
array[Db, Db] of var {0, 1}: age;

%Mindegyik mtx minden sor- és oszlopösszege 1
constraint forall(d1 in Db)(sum(d2 in Db)(dress[d1, d2])=1 /\ sum(d2 in Db)(dress[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(name[d1, d2])=1 /\ sum(d2 in Db)(name[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(donation[d1, d2])=1 /\ sum(d2 in Db)(donation[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(cocktail[d1, d2])=1 /\ sum(d2 in Db)(cocktail[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(necklace[d1, d2])=1 /\ sum(d2 in Db)(necklace[d2, d1])=1);
constraint forall(d1 in Db)(sum(d2 in Db)(age[d1, d2])=1 /\ sum(d2 in Db)(age[d2, d1])=1);

%Jane donated $20,000.
constraint forall(p in Db)(name[Jane, p] = donation[twentythousand, p]);

%The lady wearing the Pearl necklace donated the smallest amount.
constraint forall(p in Db)(necklace[pearl, p] = donation[tenthousand, p]);

%The woman wearing the Turquoise necklace donated $30,000.
constraint forall(p in Db)(necklace[turquoise, p] = donation[thirtythousand, p]);

%The 55 years old woman is wearing the Sapphire necklace.
constraint forall(p in Db)(necklace[sapphire, p] = age[fiftyfive, p]);

%The woman who donated $ 30,000 is immediately before the youngest woman.
constraint forall(p in 2..db)(age[fourty, p]=1 -> donation[thirtythousand, p-1]=1);

%Diana is exactly to the left of the 50 years old woman.
constraint forall(p in 2..db)(age[fifty, p]=1 -> name[Diana, p-1]=1);

%The donator wearing the Emerald necklace is exactly to the left of the donator wearing the Purple dress.
constraint forall(p in 2..db)(dress[purple, p]=1 -> necklace[emerald, p-1]=1);

%The guest that donated $ 20,000 is immediately before the guest drinking Daiquiri.
constraint forall(p in 2..db)(cocktail[daiquiri, p]=1 -> donation[twentythousand, p-1]=1);

%The oldest woman is exactly to the right of the lady drinking Cosmopolitan.
constraint forall(p in 1..db-1)(cocktail[cosmopolitan, p]=1 -> age[sixty, p+1]=1);

%Melissa is exactly to the right of the guest drinking Cosmopolitan.
constraint forall(p in 1..db-1)(cocktail[cosmopolitan, p]=1 -> name[Melissa, p+1]=1);

%The 50 years old woman is exactly to the right of the woman wearing the Pearl necklace.
constraint forall(p in 1..db-1)(necklace[pearl, p]=1 -> age[fifty, p+1]=1);

%The lady drinking Manhattan is exactly to the right of the lady wearing the Red dress.
constraint forall(p in 1..db-1)(dress[red, p]=1 -> cocktail[manhattan, p+1]=1);

%The guest drinking Martini is next to the guest who donated $ 10,000.
constraint forall(p in 2..db-1)(donation[tenthousand, p]=1 -> cocktail[martini, p-1]+cocktail[martini, p+1]=1);
constraint donation[tenthousand, 1]=1 -> cocktail[martini, 2]=1;
constraint donation[tenthousand, db]=1 -> cocktail[martini, db-1]=1;

%The donator wearing the White dress is next to the woman who gave the biggest donation.
constraint forall(p in 2..db-1)(donation[fiftythousand, p]=1 -> dress[white, p-1]+dress[white, p+1]=1);
constraint donation[fiftythousand, 1]=1 -> dress[white, 2]=1;
constraint donation[fiftythousand, db]=1 -> dress[white, db-1]=1;

%Lidia is next to the guest wearing the Black dress.
constraint forall(p in 2..db-1)(dress[black, p]=1 -> name[Lidia, p-1]+name[Lidia, p+1]=1);
constraint dress[black, 1]=1 -> name[Lidia, 2]=1;
constraint dress[black, db]=1 -> name[Lidia, db-1]=1;

%Lidia is next to the woman drinking Cosmopolitan.
constraint forall(p in 2..db-1)(cocktail[cosmopolitan, p]=1 -> name[Lidia, p-1]+name[Lidia, p+1]=1);
constraint cocktail[cosmopolitan, 1]=1 -> name[Lidia, 2]=1;
constraint cocktail[cosmopolitan, db]=1 -> name[Lidia, db-1]=1;

%The lady wearing the Blue dress is somewhere to the left of the lady drinking Margarita.
constraint forall(x in Db)(cocktail[margarita, x]=1 -> sum(p in 1..x-1)(dress[blue, p])=1);

%The lady wearing the Black dress is somewhere to the left of the lady who donated $ 40,000.
constraint forall(x in Db)(donation[fourtythousand, x]=1 -> sum(p in 1..x-1)(dress[black, p])=1);

%The guest wearing the White dress is somewhere to the left of the guest wearing the Black dress.
constraint forall(x in Db)(dress[black, x]=1 -> sum(p in 1..x-1)(dress[white, p])=1);

%The 60 years old woman is somewhere to the right of the woman wearing the Black dress.
constraint forall(x in Db)(dress[black, x]=1 -> sum(p in x+1..db)(age[sixty, p])=1);

%The woman wearing the Red dress is somewhere between the woman that donated $ 20,000 and the woman that gave $ 40,000, in that order.
constraint forall(x in Db, y in Db)(donation[twentythousand,x]=1 /\ donation[fourtythousand,y]=1 -> sum(p in x+1..y-1)(dress[red, p])=1);

solve satisfy;

output [show(dressData[n]) ++ "\t" ++ "\t" | t in Db, n in Db where fix(dress[n,t])=1]++["\n"];
output [show(nameData[n]) ++ "\t" ++ "\t" | t in Db, n in Db where fix(name[n,t])=1]++["\n"];
output [show(donationData[n]) ++ "\t"   | t in Db, n in Db where fix(donation[n,t])=1]++["\n"];
output [show(cocktailData[n]) ++ "\t"   | t in Db, n in Db where fix(cocktail[n,t])=1]++["\n"];
output [show(necklaceData[n]) ++ "\t"  | t in Db, n in Db where fix(necklace[n,t])=1]++["\n"];
output [show(ageData[n]) ++ "\t" ++ "\t" | t in Db, n in Db where fix(age[n,t])=1]++["\n"];