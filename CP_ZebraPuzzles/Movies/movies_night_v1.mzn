include "globals.mzn";

%Bemenő paraméter és segédhalmaz az indexeléshez: hány ember van
int: db;
set of int: Db = 1..db;

int: Daniel = 1;
int: Joshua = 2;
int: Nicholas = 3;
int: Ryan = 4;

int: action = 1;
int: comedy = 2;
int: horror = 3;
int: thriller = 4;

int: chips = 1;
int: cookies = 2;
int: crackers = 3;
int: popcorn = 4;

int: black = 1;
int: blue = 2;
int: green = 3;
int: red = 4;

int: eleven = 1;
int: twelve = 2;
int: thirteen = 3;
int: fourteen = 4;

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
constraint forall(szek in Db)(name[Joshua,szek] = movie[horror, szek]);

%Daniel likes Thriller movies
constraint forall(szek in Db)(name[Daniel,szek] = movie[thriller, szek]);

%The boy wearning the Black shirt is exactly to the left of the one who likes Thriller movies.
constraint forall(szek in 2..db)(movie[thriller,szek]=1 -> shirt[black, szek-1]=1);

%The boy who is going to eat Crackers is exactly to the right of the boy who likes Comedy movies.
constraint forall(szek in 1..db-1)(movie[comedy,szek]=1 -> snack[crackers, szek+1]=1);

%The boy wearning the Black shirt is somewhere to the left of the youngest boy.
constraint forall(x in Db)(age[eleven,x]=1 -> sum(szek in 1..x-1)(shirt[black, szek])=1);

%The boy wearning the Red shirt is somewhere between the 13 years old boy and the one who likes Action movies, in that order.
constraint forall(x in Db, y in Db)(age[thirteen,x]=1 /\ movie[action,y]=1 -> sum(szek in x+1..y-1)(shirt[red,szek])=1);

%The boy wearning the Red shirt is somewhere between the boy who is going to eat Popcorn and Nicholas, in that order.
constraint forall(x in Db, y in Db)(snack[popcorn,x]=1 /\ name[Nicholas,y]=1 -> sum(szek in x+1..y-1)(shirt[red,szek])=1);

%Nicholas is somewhere between Joshua and Daniel, in that order.
constraint forall(x in Db, y in Db)(name[Joshua,x]=1 /\ name[Daniel,y]=1 -> sum(szek in x+1..y-1)(name[Nicholas,szek])=1);

solve satisfy;

output [show(nameData[n]) ++ "\t" ++ "\t" | t in Db, n in Db where fix(name[n,t])=1]++["\n"];
output [show(shirtData[n]) ++ "\t" ++ "\t" | t in Db, n in Db where fix(shirt[n,t])=1]++["\n"];
output [show(movieData[n]) ++ "\t" ++ "\t"  | t in Db, n in Db where fix(movie[n,t])=1]++["\n"];
output [show(snackData[n]) ++ "\t" ++ "\t"  | t in Db, n in Db where fix(snack[n,t])=1]++["\n"];
output [show(ageData[n]) ++ "\t" ++ "\t" ++ "\t"  | t in Db, n in Db where fix(age[n,t])=1]++["\n"];