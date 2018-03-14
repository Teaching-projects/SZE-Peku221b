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

int testAtTheEnd(struct onepersonrule attheend[5]){
    int i, position, megsert=0;
    for (i=0;i<5;i++){
        position=hanyasSzek(attheend[i].first.property, attheend[i].first.value);
        if (position>0 && position<SZEK-1) megsert++;
    return megesert;
        

}

int main() {
    struct onepersonrule attheend[5];
    struct twopersonrule exactlytotheleft[7];
    struct twopersonrule sameperson[4] =
    {
        {1, 2, 3, 6},
        {
    };


}

    
