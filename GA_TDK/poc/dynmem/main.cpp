struct person {
        int property;
        int value;
};

struct onepersonrule {
    struct person first;
};

struct twopersonrule {
    struct person first;
    struct person second;
};

struct threepersonrule {
    struct person first;
    struct person second;
    struct person third;
};

struct positionrule {
    struct person first;
    int hely;
};

int testAtTheEnd(struct onepersonrule attheend[3]){
    int i, position, megsert=0;
    for (i=0;i<3;i++){
        position=hanyasSzek(attheend[i].first.property, attheend[i].first.value);
        if (position>0 && position<SZEK-1) megsert++;
    }
    return megsert;
}

int testExactlyToTheLeft(struct twopersonrule exactlyleft[1]){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(exactlyleft[i].first.property, exactlyleft[i].first.value);
        position2=hanyasSzek(exactlyleft[i].second.property, exactlyleft[i].second.value);
        if (position1!=position2-1) megsert++;
    }
    return megsert;
}

int testExactlyToTheRight(struct twopersonrule exactlyright[1]){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(exactlyright[i].first.property, exactlyright[i].first.value);
        position2=hanyasSzek(exactlyright[i].second.property, exactlyright[i].second.value);
        if (position2!=position1-1) megsert++;
    }
    return megsert;
}

int testSomewhereToTheLeft(struct twopersonrule somewhereleft[1]){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(somewhereleft[i].first.property, somewhereleft[i].first.value);
        position2=hanyasSzek(somewhereleft[i].second.property, somewhereleft[i].second.value);
        if (position1>=position2) megsert++;
    }
    return megsert;
}

int testSameperson (struct twopersonrule sameperson[2]){
    int i, position1, position2, megsert=0;
    for (i=0;i<2;i++){
        position1=hanyasSzek(sameperson[i].first.property, sameperson[i].first.value);
        position2=hanyasSzek(sameperson[i].second.property, sameperson[i].second.value);
        if (position1!=position2) megsert++;
    }
    return megsert;
}

int testPosition (struct positionrule position[2]){
    int i, megsert=0;
    for (i=0;i<2;i++){
        if (hely!=hanyasSzek(attheend[i].first.property, attheend[i].first.value)) megsert++;
    }
    return megsert;
}

int testSomewhereBetween (struct threepersonrule between[3]){
    int i, position1, position2, position3, megsert=0;
      for (i=0;i<3;i++){
        position1=hanyasSzek(between[i].first.property, between[i].first.value);
        position2=hanyasSzek(between[i].second.property, between[i].second.value);
        position3=hanyasSzek(between[i].third.property, between[i].third.value);
        if (!(position2<position1 && position1<position3)) megsert++;
      }
    return megsert;
}

int fitness(){
    megsert+=testSomewhereBetween(*kozott);
    megsert+=testExactlyToTheLeft(*balpont);
    megsert+=testExactlyToTheRight(*jobbpont);
    megsert+=testPosition(*pozicio);
    megsert+=testSameperson(*ugyanaz);
    megsert+=testSomewhereToTheLeft(*balvhol);
    megsert+=testAtTheEnd(*vegen);
    return megsert;
}

int main() {
    struct onepersonrule *vegen = new struct onepersonrule[3];
    struct onepersonrule attheend[3];
	attheend[0] = {NAME,JOSHUA};
	attheend[1] = {SNACK,COOKIES};
	attheend[2] = {MOVIE,THRILLER};
    attheend =
    {
        {NAME,JOSHUA},
        {SNACK,COOKIES},
        {MOVIE,THRILLER}
    };
    vegen = attheend;
    // meret meghatarozasa
    int meret = 1;
    struct twopersonrule *balpont = new struct twopersonrule[meret];
    for (int i=0; i<meret; ++i) {
        struct person szemely1, szemely2;
        // fajlbol beolvasni a parametereit
        int index = tulindex(beolvasott);
        szemely1.property = index;
        szemely1.value = JOSHUA;
//        balpont[i] = {szemely1, szemely2};
        balpont[i].first = szemely1;
        balpont[i].second = szemely2;
    }
    *balpont = struct twopersonrule exactlyleft[1] =
    {
        { int fajl[32];
        std::string line_;
        ifstream file_("fajl.txt");
        if(file_.is_open()){
            getline(file_,line_);
            file_.close();
        }
    else
    exit(EXIT_FAILURE);
    std::cin.get();
        };
    };
    struct twopersonrule *jobbpont = new struct twopersonrule[1];
	struct twopersonrule exactlyright[1];
	exactlyright[0] = {MOVIE,COMEDY,SNACK,CRACKERS};
	exactlyright = 
    {
        { MOVIE,COMEDY,SNACK,CRACKERS }
    };
	jobbpont = exactlyright;
    struct twopersonrule *balvhol = new struct twopersonrule[1];
	struct twopersonrule somewhereleft[1];
	somewhereleft[0] = { AGE,ELEVEN,SHIRT,BLACK };
	somewhereleft =
    {
        { AGE,ELEVEN,SHIRT,BLACK }
    };
	balpont = somewhereleft;
    struct positionrule *pozicio = new struct positionrule[1];
	struct positionrule position[2];
	position[0] = {AGE,FOURTEEN,3};
	position[1] = {SHIRT,GREEN,1};
    {
        { AGE,FOURTEEN,3 },
        { SHIRT,GREEN,1 }
    };
	pozicio = position;
    struct threepersonrule *kozott = new struct threepersonrule[3];
	struct threepersonrule between[3];
	between[0] = {AGE,THIRTEEN,SHIRT,RED,MOVIE,ACTION};
	between[1] = {SNACK,POPCORN,SHIRT,RED,NAME,NICHOLAS};
	between[2] = {NAME,JOSHUA,NAME,NICHOLAS,NAME,DANIEL};
	between =
    {
        { AGE,THIRTEEN,SHIRT,RED,MOVIE,ACTION },
        { SNACK,POPCORN,SHIRT,RED,NAME,NICHOLAS },
        { NAME,JOSHUA,NAME,NICHOLAS,NAME,DANIEL }
    };
	kozott = between;
    struct twopersonrule *ugyanaz = new struct twopersonrule[2];
	struct twopersonrule sameperson[2];
	sameperson[0] = {NAME,JOSHUA,MOVIE,HORROR};
	sameperson[1] = {NAME,DANIEL,MOVIE,THRILLER};
	sameperson =
	{
        { NAME,JOSHUA,MOVIE,HORROR },
        { NAME,DANIEL,MOVIE,THRILLER }
    };
	ugyan = sameperson;
    fitness();

}


