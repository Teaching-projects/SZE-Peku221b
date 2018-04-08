 %Bemenő paraméter és segédhalmaz az indexeléshez: hány ember van
int: db = 5;
set of int: PEOPLE = 1..db;

%Tulajdonságok
enum COLORS = {black, blue, purple, red, white};
enum NAMES = {Carmen, Diana, Jane, Lidia, Melissa};
enum MONEY = {tenthousand, twentythousand, thirtythousand, fourtythousand, fiftythousand};
enum DRINKS = {cosmopolitan, daiquiri, manhattan, margarita, martini};
enum GEMS = {emerald, moonstone, pearl, sapphire, turquoise};
enum AGES = {fourty, fourtyfive, fifty, fiftyfive, sixty};

%Tulajdonságonként egy bináris mtx
array[COLORS, PEOPLE] of var {0, 1}: dress;
array[NAMES, PEOPLE] of var {0, 1}: name;
array[MONEY, PEOPLE] of var {0, 1}: donation;
array[DRINKS, PEOPLE] of var {0, 1}: cocktail;
array[GEMS, PEOPLE] of var {0, 1}: necklace;
array[AGES, PEOPLE] of var {0, 1}: age;

%Mindegyik mtx minden sor- és oszlopösszege 1
constraint forall(c in COLORS)(sum(p in PEOPLE)(dress[c, p])=1);
constraint forall(p in PEOPLE)(sum(c in COLORS)(dress[c, p])=1);

constraint forall(n in NAMES)(sum(p in PEOPLE)(name[n, p])=1);
constraint forall(p in PEOPLE)(sum(n in NAMES)(name[n, p])=1);

constraint forall(m in MONEY)(sum(p in PEOPLE)(donation[m, p])=1);
constraint forall(p in PEOPLE)(sum(m in MONEY)(donation[m, p])=1);

constraint forall(d in DRINKS)(sum(p in PEOPLE)(cocktail[d, p])=1);
constraint forall(p in PEOPLE)(sum(d in DRINKS)(cocktail[d, p])=1);

constraint forall(g in GEMS)(sum(p in PEOPLE)(necklace[g, p])=1);
constraint forall(p in PEOPLE)(sum(g in GEMS)(necklace[g, p])=1);

constraint forall(a in AGES)(sum(p in PEOPLE)(age[a, p])=1);
constraint forall(p in PEOPLE)(sum(a in AGES)(age[a, p])=1);

%Jane donated $20,000.
constraint forall(p in PEOPLE where name[Jane, p]=1)(donation[twentythousand, p]=1);

%The lady wearing the Pearl necklace donated the smallest amount.
constraint forall(p in PEOPLE where necklace[pearl, p]=1)(donation[tenthousand, p]=1);

%The woman wearing the Turquoise necklace donated $30,000.
constraint forall(p in PEOPLE where necklace[turquoise, p]=1)(donation[thirtythousand, p]=1);

%The 55 years old woman is wearing the Sapphire necklace.
constraint forall(p in PEOPLE where necklace[sapphire, p]=1)(age[fiftyfive, p]=1);

%The woman who donated $ 30,000 is immediately before the youngest woman.
constraint forall(p in 2..db where age[fourty, p]=1)(donation[thirtythousand, p-1]=1);

%Diana is exactly to the left of the 50 years old woman.
constraint forall(p in 2..db where age[fifty, p]=1)(name[Diana, p-1]=1);

%The donator wearing the Emerald necklace is exactly to the left of the donator wearing the Purple dress.
constraint forall(p in 2..db where dress[purple, p]=1)(necklace[emerald, p-1]=1);

%The guest that donated $ 20,000 is immediately before the guest drinking Daiquiri.
constraint forall(p in 2..db where cocktail[daiquiri, p]=1)(donation[twentythousand, p-1]=1);

%The oldest woman is exactly to the right of the lady drinking Cosmopolitan.
constraint forall(p in 1..db-1 where cocktail[cosmopolitan, p]=1)(age[sixty, p+1]=1);

%Melissa is exactly to the right of the guest drinking Cosmopolitan.
constraint forall(p in 1..db-1 where cocktail[cosmopolitan, p]=1)(name[Melissa, p+1]=1);

%The 50 years old woman is exactly to the right of the woman wearing the Pearl necklace.
constraint forall(p in 1..db-1 where necklace[pearl, p]=1)(age[fifty, p+1]=1);

%The lady drinking Manhattan is exactly to the right of the lady wearing the Red dress.
constraint forall(p in 1..db-1 where dress[red, p]=1)(cocktail[manhattan, p+1]=1);

%The guest drinking Martini is next to the guest who donated $ 10,000.
constraint forall(p in 2..db-1 where donation[tenthousand, p]=1)(cocktail[martini, p-1]+cocktail[martini, p+1]=1);
constraint donation[tenthousand, 1]=1 -> cocktail[martini, 2]=1;
constraint donation[tenthousand, db]=1 -> cocktail[martini, db-1]=1;

%The donator wearing the White dress is next to the woman who gave the biggest donation.
constraint forall(p in 2..db-1 where donation[fiftythousand, p]=1)(dress[white, p-1]+dress[white, p+1]=1);
constraint donation[fiftythousand, 1]=1 -> dress[white, 2]=1;
constraint donation[fiftythousand, db]=1 -> dress[white, db-1]=1;

%Lidia is next to the guest wearing the Black dress.
constraint forall(p in 2..db-1 where dress[black, p]=1)(name[Lidia, p-1]+name[Lidia, p+1]=1);
constraint dress[black, 1]=1 -> name[Lidia, 2]=1;
constraint dress[black, db]=1 -> name[Lidia, db-1]=1;

%Lidia is next to the woman drinking Cosmopolitan.
constraint forall(p in 2..db-1 where cocktail[cosmopolitan, p]=1)(name[Lidia, p-1]+name[Lidia, p+1]=1);
constraint cocktail[cosmopolitan, 1]=1 -> name[Lidia, 2]=1;
constraint cocktail[cosmopolitan, db]=1 -> name[Lidia, db-1]=1;

%The lady wearing the Blue dress is somewhere to the left of the lady drinking Margarita.
constraint forall(x in PEOPLE where cocktail[margarita, x]=1)(sum(p in 1..x-1)(dress[blue, p])=1);

%The lady wearing the Black dress is somewhere to the left of the lady who donated $ 40,000.
constraint forall(x in PEOPLE where donation[fourtythousand, x]=1)(sum(p in 1..x-1)(dress[black, p])=1);

%The guest wearing the White dress is somewhere to the left of the guest wearing the Black dress.
constraint forall(x in PEOPLE where dress[black, x]=1)(sum(p in 1..x-1)(dress[white, p])=1);

%The 60 years old woman is somewhere to the right of the woman wearing the Black dress.
constraint forall(x in PEOPLE where dress[black, x]=1)(sum(p in x+1..db)(age[sixty, p])=1);

%The woman wearing the Red dress is somewhere between the woman that donated $ 20,000 and the woman that gave $ 40,000, in that order.
constraint forall(x in PEOPLE, y in PEOPLE where (donation[twentythousand,x]=1 /\ donation[fourtythousand,y]=1))(sum(p in x+1..y-1)(dress[red, p])=1);

solve satisfy;

int: width = -15;
output [format(width,show(n)) ++ "\t" | t in PEOPLE, n in COLORS where fix(dress[n,t])=1]++["\n"];
output [format(width,show(n)) ++ "\t" | t in PEOPLE, n in NAMES where fix(name[n,t])=1]++["\n"];
output [format(width,show(n)) ++ "\t" | t in PEOPLE, n in MONEY where fix(donation[n,t])=1]++["\n"];
output [format(width,show(n)) ++ "\t" | t in PEOPLE, n in DRINKS where fix(cocktail[n,t])=1]++["\n"];
output [format(width,show(n)) ++ "\t" | t in PEOPLE, n in GEMS where fix(necklace[n,t])=1]++["\n"];
output [format(width,show(n)) ++ "\t" | t in PEOPLE, n in AGES where fix(age[n,t])=1]++["\n"];