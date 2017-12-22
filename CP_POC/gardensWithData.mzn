%Bemenő paraméterek: kertek száma, termények száma
int: kertek = 5;
int: termenyek = 12;

%Indexelésre használt halmazok
set of int: Kertek = 1..kertek;
set of int: Termenyek = 1.. termenyek;

%Nagy bináris mátrix, megadja hogy melyik kertben mit termesztenek
array[Termenyek, Kertek] of var: termeszt;

%Tömb az adott sorszámú kert tulajdonosának azonosítására
array[Kertek] of int: tulaj;

%Termények nevei, majd a kiíratáshoz fog kelleni
array[Termenyek] of string: termenyNev = ["alma", "körte", "mogyoró", "cseresznye", "sárgarépa", "petrezselyem", "tök", "hagyma", "őszirózsa", "rózsa", "tulipán", "liliom"];

%Tulajdonosok nevei, szintén kiíratáshoz kell majd
array[Kertek] of string: tulajNev = ["Luke", "Sam", "Hank", "Paul", "Zick"];

% 7. Pear is only in the two border gardens.
constraint termeszt[2,1]=1;
constraint termeszt[2,5]=1;

% 8. Paul's garden is in the middle with no lily.
constraint termeszt[12,3]=0;
constraint tulaj[3]=4;

%Ide kell majd a többi feltétel...

solve satisfy;