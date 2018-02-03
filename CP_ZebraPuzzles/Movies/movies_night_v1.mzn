%Bemenő paraméter és segédhalmaz az indexeléshez: hány ember van
int: db = 4;
set of int: PEOPLE = 1..db;

%Tulajdonságok
enum NAMES = {Daniel, Joshua, Nicholas, Ryan};
enum MOVIES = {action, comedy, horror, thriller};
enum SNACKS = {chips, cookies, crackers, popcorn};
enum COLORS = {black, blue, green, red};
enum AGES = {eleven, twelve, thirteen, fourteen};

%Tulajdonságonként egy bináris mtx
array[COLORS, PEOPLE] of var {0, 1}: shirt;
array[NAMES, PEOPLE] of var {0, 1}: name;
array[MOVIES, PEOPLE] of var {0, 1}: movie;
array[SNACKS, PEOPLE] of var {0, 1}: snack;
array[AGES, PEOPLE] of var {0, 1}: age;

%Mindegyik mtx minden sor- és oszlopösszege 1
constraint forall(p in PEOPLE)(sum(n in NAMES)(name[n, p])=1);
constraint forall(n in NAMES)(sum(p in PEOPLE)(name[n, p])=1);

constraint forall(p in PEOPLE)(sum(m in MOVIES)(movie[m, p])=1);
constraint forall(m in MOVIES)(sum(p in PEOPLE)(movie[m, p])=1);

constraint forall(p in PEOPLE)(sum(c in COLORS)(shirt[c, p])=1);
constraint forall(c in COLORS)(sum(p in PEOPLE)(shirt[c, p])=1);

constraint forall(p in PEOPLE)(sum(s in SNACKS)(snack[s, p])=1);
constraint forall(s in SNACKS)(sum(p in PEOPLE)(snack[s, p])=1);

constraint forall(p in PEOPLE)(sum(a in AGES)(age[a, p])=1);
constraint forall(a in AGES)(sum(p in PEOPLE)(age[a, p])=1);

%The 14 years old boy is at third position.
constraint age[fourteen,3]=1;

%At first position is the boy wearning the Green shirt.
constraint shirt[green,1]=1;

%Joshua is in one of the ends.
constraint name[Joshua,1]+name[Joshua,db]=1;

%The boy who is going to eat Cookies is in one of the ends.
constraint snack[cookies,1]+snack[cookies,db]=1;

%In one of the ends is the boy who likes Thriller movies.
constraint movie[thriller,1]+movie[thriller,db]=1;

%Joshua likes Horror movies.
constraint forall(szek in PEOPLE)(name[Joshua,szek] = movie[horror, szek]);

%Daniel likes Thriller movies
constraint forall(szek in PEOPLE)(name[Daniel,szek] = movie[thriller, szek]);

%The boy wearning the Black shirt is exactly to the left of the one who likes Thriller movies.
constraint forall(szek in 2..db)(movie[thriller,szek]=1 -> shirt[black, szek-1]=1);

%The boy who is going to eat Crackers is exactly to the right of the boy who likes Comedy movies.
constraint forall(szek in 1..db-1)(movie[comedy,szek]=1 -> snack[crackers, szek+1]=1);

%The boy wearning the Black shirt is somewhere to the left of the youngest boy.
constraint forall(x in PEOPLE)(age[eleven,x]=1 -> sum(szek in 1..x-1)(shirt[black, szek])=1);

%The boy wearning the Red shirt is somewhere between the 13 years old boy and the one who likes Action movies, in that order.
constraint forall(x in PEOPLE, y in PEOPLE)(age[thirteen,x]=1 /\ movie[action,y]=1 -> sum(szek in x+1..y-1)(shirt[red,szek])=1);

%The boy wearning the Red shirt is somewhere between the boy who is going to eat Popcorn and Nicholas, in that order.
constraint forall(x in PEOPLE, y in PEOPLE)(snack[popcorn,x]=1 /\ name[Nicholas,y]=1 -> sum(szek in x+1..y-1)(shirt[red,szek])=1);

%Nicholas is somewhere between Joshua and Daniel, in that order.
constraint forall(x in PEOPLE, y in PEOPLE)(name[Joshua,x]=1 /\ name[Daniel,y]=1 -> sum(szek in x+1..y-1)(name[Nicholas,szek])=1);

solve satisfy;

int: width = -15;
output [format(width, show(n)) ++ "\t" | t in PEOPLE, n in NAMES where fix(name[n,t])=1]++["\n"];
output [format(width, show(c)) ++ "\t" | t in PEOPLE, c in COLORS where fix(shirt[c,t])=1]++["\n"];
output [format(width, show(m)) ++ "\t"  | t in PEOPLE, m in MOVIES where fix(movie[m,t])=1]++["\n"];
output [format(width, show(s)) ++ "\t"  | t in PEOPLE, s in SNACKS where fix(snack[s,t])=1]++["\n"];
output [format(width, show(a)) ++ "\t" | t in PEOPLE, a in AGES where fix(age[a,t])=1]++["\n"];