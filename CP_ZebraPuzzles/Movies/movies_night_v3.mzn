include "globals.mzn";

%Bemenő paraméter és segédhalmaz az indexeléshez: hány ember/korlátozás van
int: db = 4;
set of int: PEOPLE = 1..db;
int: korlatozasok;
array[1..korlatozasok] of int: kivesszuk;

%Tulajdonságok
enum NAMES = {Daniel, Joshua, Nicholas, Ryan};
enum MOVIES = {action, comedy, horror, thriller};
enum SNACKS = {chips, cookies, crackers, popcorn};
enum COLORS = {black, blue, green, red};
enum AGES = {eleven, twelve, thirteen, fourteen};

%Tulajdonságonként egy tömb
array[PEOPLE] of var NAMES: name;
array[PEOPLE] of var MOVIES: movie;
array[PEOPLE] of var COLORS: shirt;
array[PEOPLE] of var SNACKS: snack;
array[PEOPLE] of var AGES: age;

%Mindegyik tömb különböző adatokat tartalmaz
constraint alldifferent(name);
constraint alldifferent(movie);
constraint alldifferent(shirt);
constraint alldifferent(snack);
constraint alldifferent(age);

%The 14 years old boy is at third position.
constraint if kivesszuk[1]=1 then true else
  age[3]=fourteen
endif;

%At first position is the boy wearning the Green shirt.
constraint if kivesszuk[2]=1 then true else
  shirt[1]=green
endif;

%Joshua is in one of the ends.
constraint if kivesszuk[3]=1 then true else
  name[1]=Joshua xor name[db]=Joshua
endif;

%The boy who is going to eat Cookies is in one of the ends.
constraint if kivesszuk[4]=1 then true else
  snack[1]=cookies xor snack[db]=cookies
endif;

%In one of the ends is the boy who likes Thriller movies.
constraint if kivesszuk[5]=1 then true else
  movie[1]=thriller xor movie[db]=thriller
endif;

%Joshua likes Horror movies.
constraint if kivesszuk[6]=1 then true else
  forall(szek in PEOPLE)(name[szek]=Joshua -> movie[szek]=horror)
endif;

%Daniel likes Thriller movies
constraint if kivesszuk[7]=1 then true else
  forall(szek in PEOPLE)(name[szek]=Daniel -> movie[szek]=thriller)
endif;

%The boy wearning the Black shirt is exactly to the left of the one who likes Thriller movies.
constraint if kivesszuk[8]=1 then true else
  forall(szek in 2..db)(movie[szek]=thriller -> shirt[szek-1]=black)
endif;

%The boy who is going to eat Crackers is exactly to the right of the boy who likes Comedy movies.
constraint if kivesszuk[9]=1 then true else
  forall(szek in 1..db-1)(movie[szek]=comedy -> snack[szek+1]=crackers)
endif;

%The boy wearning the Black shirt is somewhere to the left of the youngest boy.
constraint if kivesszuk[10]=1 then true else
  forall(x in PEOPLE)(age[x]=eleven -> count([shirt[szek] | szek in 1..x-1], black)=1)
endif;

%The boy wearning the Red shirt is somewhere between the 13 years old boy and the one who likes Action movies, in that order.
constraint if kivesszuk[11]=1 then true else
  forall(x in PEOPLE)(movie[x]=action -> count([shirt[szek] | szek in 1..x-1], red)=1) /\
  forall(x in PEOPLE)(age[x]=thirteen -> count([shirt[szek] | szek in x+1..db], red)=1)
endif;

%The boy wearning the Red shirt is somewhere between the boy who is going to eat Popcorn and Nicholas, in that order.
constraint if kivesszuk[12]=1 then true else
  forall(x in PEOPLE)(name[x]=Nicholas -> count([shirt[szek] | szek in 1..x-1], red)=1) /\
  forall(x in PEOPLE)(snack[x]=popcorn -> count([shirt[szek] | szek in x+1..db], red)=1)
endif;

%Nicholas is somewhere between Joshua and Daniel, in that order.
constraint if kivesszuk[13]=1 then true else
   forall(x in PEOPLE)(name[x]=Daniel -> count([name[szek] | szek in 1..x-1], Nicholas)=1) /\
   forall(x in PEOPLE)(name[x]=Joshua -> count([name[szek] | szek in x+1..db], Nicholas)=1)
endif;

solve satisfy;

int: width = -15;
output [format(width, show(name[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width, show(movie[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width, show(snack[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width, show(shirt[p])) ++ "\t" | p in PEOPLE]++["\n"];
output [format(width, show(age[p])) ++ "\t" | p in PEOPLE]++["\n"];