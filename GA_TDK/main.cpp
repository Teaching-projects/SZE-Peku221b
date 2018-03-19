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
        if !(position1==position2-1) megsert++;
    }
    return megsert;
}

int testExactlyToTheRight(struct twopersonrule exactlyright[1]){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(exactlyright[i].first.property, exactlyright[i].first.value);
        position2=hanyasSzek(exactlyright[i].second.property, exactlyright[i].second.value);
        if !(position2==position1-1) megsert++;
    }
    return megsert;
}

int testSomewhereToTheLeft(struct twopersonrule somewhereleft[1]){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(somewhereleft[i].first.property, somewhereleft[i].first.value);
        position2=hanyasSzek(somewhereleft[i].second.property, somewhereleft[i].second.value);
        if !(position1<position2) megsert++;
    }
    return megsert;
}

int testSameperson (struct twopersonrule sameperson[2]){
    int i, position1, position2, megsert=0;
    for (i=0;i<2;i++){
        position1=hanyasSzek(sameperson[i].first.property, sameperson[i].first.value);
        position2=hanyasSzek(sameperson[i].second.property, sameperson[i].second.value);
        if !(position1=position2) megsert++;
    }
    return megsert;
}

int testPosition (struct positionrule position[2]){
    int i, megsert=0;
    for (i=0;i<2;i++){
        if !(hely=hanyasSzek(attheend[i].first.property, attheend[i].first.value)) megsert++;
    }
    return megsert;
}

int testSomewhereBetween (struct threepersonrule between[3]){
    int i, position1, position2, position3, megsert=0;
      for (i=0;i<3;i++){
        position1=hanyasSzek(between[i].first.property, between[i].first.value);
        position2=hanyasSzek(between[i].second.property, between[i].second.value);
        position3=hanyasSzek(between[i].third.property, between[i].third.value);
        if !(position2<position1 && position1<position3) megsert++;
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
    *vegen = struct onepersonrule attheend[3] =
    {
        {NAME,JOSHUA},
        {SNACK,COOKIES},
        {MOVIE,THRILLER}

    };
	struct twopersonrule *balpont = new struct twopersonrule[1];
	*balpont = struct twopersonrule exactlyleft[1] =
	{
		{ MOVIE,THRILLER,SHIRT,BLACK };
	};
	struct twopersonrule *jobbpont = new struct twopersonrule[1];
	*jobbpont = struct twopersonrule exactlyright[1] =
	{
		{ MOVIE,COMEDY,SNACK,CRACKERS };
	};
	struct twopersonrule *balvhol = new struct twopersonrule[1];
	*balvhol = struct twopersonrule somewhereleft[1] =
	{
		{ AGE,ELEVEN,SHIRT,BLACK };
	};
	struct positionrule *pozicio = new struct positionrule[1];
	*poz = struct positionrule position[2] =
	{
		{ AGE,FOURTEEN,3 },
		{ SHIRT,GREEN,1 }
	};
	struct threepersonrule *kozott = new struct threepersonrule[3];
	*kozott = struct threepersonrule between[3] =
	{
		{ AGE,THIRTEEN,SHIRT,RED,MOVIE,ACTION },
		{ SNACK,POPCORN,SHIRT,RED,NAME,NICHOLAS },
		{ NAME,JOSHUA,NAME,NICHOLAS,NAME,DANIEL }
	};
	struct twopersonrule *ugyanaz = new struct twopersonrule[2];
	*ugyan = struct twopersonrule sameperson[2] =
	{
		{ NAME,JOSHUA,MOVIE,HORROR },
		{ NAME,DANIEL,MOVIE,THRILLER }
	};
    fitness();

}


