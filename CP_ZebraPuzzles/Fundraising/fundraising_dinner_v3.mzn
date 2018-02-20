include "globals.mzn";

%Bemenő paraméter és segédhalmaz az indexeléshez: hány ember/korlátozás van
int: db = 5;
set of int: PEOPLE = 1..db;
int: korlatozasok;
array[1..korlatozasok] of int: kivesszuk;

%Tulajdonságok
enum COLORS = {black, blue, purple, red, white};
enum NAMES = {Carmen, Diana, Jane, Lidia, Melissa};
enum MONEY = {tenthousand, twentythousand, thirtythousand, fourtythousand, fiftythousand};
enum DRINKS = {cosmopolitan, daiquiri, manhattan, margarita, martini};
enum GEMS = {emerald, moonstone, pearl, sapphire, turquoise};
enum AGES = {fourty, fourtyfive, fifty, fiftyfive, sixty};

%Tulajdonságonként egy tömb
array[PEOPLE] of var COLORS: dress;
array[PEOPLE] of var NAMES: name;
array[PEOPLE] of var MONEY: donation;
array[PEOPLE] of var DRINKS: cocktail;
array[PEOPLE] of var GEMS: necklace;
array[PEOPLE] of var AGES: age;

%Mindegyik tömb elemei különbözőek
constraint alldifferent(dress);
constraint alldifferent(name);
constraint alldifferent(donation);
constraint alldifferent(cocktail);
constraint alldifferent(necklace);
constraint alldifferent(age);

%Jane donated $20,000.
constraint if kivesszuk[1]=1 then true else
  forall(p in PEOPLE)(name[p]=Jane <-> donation[p]=twentythousand)
endif;

%The lady wearing the Pearl necklace donated the smallest amount.
constraint if kivesszuk[2]=1 then true else
  forall(p in PEOPLE)(necklace[p]=pearl <-> donation[p]=tenthousand)
endif;

%The woman wearing the Turquoise necklace donated $30,000.
constraint if kivesszuk[3]=1 then true else
  forall(p in PEOPLE)(necklace[p]=turquoise <-> donation[p]=thirtythousand)
endif;

%The 55 years old woman is wearing the Sapphire necklace.
constraint if kivesszuk[4]=1 then true else
  forall(p in PEOPLE)(necklace[p]=sapphire <-> age[p]=fiftyfive)
endif;

%The woman who donated $ 30,000 is immediately before the youngest woman.
constraint if kivesszuk[5]=1 then true else
  forall(p in 2..db)(age[p]=fourty <-> donation[p-1]=thirtythousand)
endif;

%Diana is exactly to the left of the 50 years old woman.
constraint if kivesszuk[6]=1 then true else
  forall(p in 2..db)(age[p]=fifty <-> name[p-1]=Diana)
endif;

%The donator wearing the Emerald necklace is exactly to the left of the donator wearing the Purple dress.
constraint if kivesszuk[7]=1 then true else
  forall(p in 2..db)(dress[p]=purple <-> necklace[p-1]=emerald)
endif;

%The guest that donated $ 20,000 is immediately before the guest drinking Daiquiri.
constraint if kivesszuk[8]=1 then true else
  forall(p in 2..db)(cocktail[p]=daiquiri <-> donation[p-1]=twentythousand)
endif;

%The oldest woman is exactly to the right of the lady drinking Cosmopolitan.
constraint if kivesszuk[9]=1 then true else
  forall(p in 1..db-1)(cocktail[p]=cosmopolitan <-> age[p+1]=sixty)
endif;

%Melissa is exactly to the right of the guest drinking Cosmopolitan.
constraint if kivesszuk[10]=1 then true else
  forall(p in 1..db-1)(cocktail[p]=cosmopolitan <-> name[p+1]=Melissa)
endif;

%The 50 years old woman is exactly to the right of the woman wearing the Pearl necklace.
constraint if kivesszuk[11]=1 then true else
  forall(p in 1..db-1)(necklace[p]=pearl <-> age[p+1]=fifty)
endif;

%The lady drinking Manhattan is exactly to the right of the lady wearing the Red dress.
constraint if kivesszuk[12]=1 then true else
  forall(p in 1..db-1)(dress[p]=red <-> cocktail[p+1]=manhattan)
endif;

%The guest drinking Martini is next to the guest who donated $ 10,000.
constraint if kivesszuk[13]=1 then true else
   forall(p in 2..db-1)(donation[p]=tenthousand -> cocktail[p-1]=martini xor cocktail[p+1]=martini) /\
   forall(p in 2..db-1)(cocktail[p]=martini -> donation[p-1]=tenthousand xor donation[p+1]=tenthousand) /\
   donation[1]=tenthousand -> cocktail[2]=martini /\
   donation[db]=tenthousand -> cocktail[db-1]=martini /\
   cocktail[1]=martini -> donation[2]=tenthousand /\
   cocktail[db]=martini -> donation[db-1]=tenthousand
endif;

%The donator wearing the White dress is next to the woman who gave the biggest donation.
constraint if kivesszuk[14]=1 then true else
   forall(p in 2..db-1)(donation[p]=fiftythousand -> dress[p-1]=white xor dress[p+1]=white) /\
   forall(p in 2..db-1)(dress[p]=white -> donation[p-1]=fiftythousand xor donation[p+1]=fiftythousand) /\
   donation[1]=fiftythousand -> dress[2]=white /\
   donation[db]=fiftythousand -> dress[db-1]=white /\
   dress[db]=white -> donation[db-1]=fiftythousand /\
   dress[1]=white -> donation[2]=fiftythousand
endif;

%Lidia is next to the guest wearing the Black dress.
constraint if kivesszuk[15]=1 then true else
   forall(p in 2..db-1)(name[p]=Lidia -> dress[p-1]=black xor dress[p+1]=black) /\
   forall(p in 2..db-1)(dress[p]=black -> name[p-1]=Lidia xor name[p+1]=Lidia) /\
   name[1]=Lidia -> dress[2]=black /\
   name[db]=Lidia -> dress[db-1]=black /\
   dress[1]=black -> name[2]=Lidia /\
   dress[db]=black -> name[db-1]=Lidia
endif;

%Lidia is next to the woman drinking Cosmopolitan.
constraint if kivesszuk[13]=1 then true else
   forall(p in 2..db-1)(name[p]=Lidia -> cocktail[p-1]=cosmopolitan xor cocktail[p+1]=cosmopolitan) /\
   forall(p in 2..db-1)(cocktail[p]=cosmopolitan -> name[p-1]=Lidia xor name[p+1]=Lidia) /\
   name[1]=Lidia -> cocktail[2]=cosmopolitan /\
   name[db]=Lidia -> cocktail[db-1]=cosmopolitan /\
   cocktail[1]=cosmopolitan -> name[2]=Lidia /\
   cocktail[db]=cosmopolitan -> name[db-1]=Lidia
endif;

%The lady wearing the Blue dress is somewhere to the left of the lady drinking Margarita.
constraint if kivesszuk[17]=1 then true else
  forall(x in PEOPLE)(cocktail[x]=margarita -> count([dress[p] | p in 1..x-1], blue)=1)
endif;

%The lady wearing the Black dress is somewhere to the left of the lady who donated $ 40,000.
constraint if kivesszuk[18]=1 then true else
  forall(x in PEOPLE)(donation[x]=fourtythousand -> count([dress[p] | p in 1..x-1], black)=1)
endif;

%The guest wearing the White dress is somewhere to the left of the guest wearing the Black dress.
constraint if kivesszuk[19]=1 then true else
  forall(x in PEOPLE)(dress[x]=black -> count([dress[p] | p in 1..x-1], white)=1)
endif;

%The 60 years old woman is somewhere to the right of the woman wearing the Black dress.
constraint if kivesszuk[20]=1 then true else
  forall(x in PEOPLE)(dress[x]=black -> count([age[p] | p in x+1..db], sixty)=1)
endif;

%The woman wearing the Red dress is somewhere between the woman that donated $ 20,000 and the woman that gave $ 40,000, in that order.
constraint if kivesszuk[21]=1 then true else
  forall(x in PEOPLE)(donation[x]=fourtythousand -> count([dress[p] | p in 1..x-1], red)=1) /\
  forall(x in PEOPLE)(donation[x]=twentythousand -> count([dress[p] | p in x+1..db], red)=1)
endif;

solve satisfy;

int: width = -25;
output [format(width,show(dress[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width,show(name[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width,show(donation[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width,show(cocktail[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width,show(necklace[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width,show(age[p])) ++ "\t" | p in PEOPLE]++["\n"];