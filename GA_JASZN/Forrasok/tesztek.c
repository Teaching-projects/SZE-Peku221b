//The 14 years old boy is at third position.
int Teszt1(struct gen egyed) {
    if(egyed.allel[AGE][2]==FOURTEEN) return 0;
    else return 1;
}
//Joshua is exactly to the left of the youngest boy.
int Teszt2(struct gen egyed){ 
   int egyed1=HanyadikSzek(egyed,NAME,JOSHUA);
   int egyed2= HanyadikSzek(egyed,AGE,ELEVEN);
   return !(egyed1==egyed2-1);
}
//The boy wearing the Red shirt is somewhere between 
//the boy who is going to eat Popcorn and Nicholas, in that order.
int Teszt3 (struct gen egyed) {
    int egyed1=HanyadikSzek(egyed,SNACK,POPCORN);
    int egyed2= HanyadikSzek(egyed,SHIRT,RED);
    int egyed3=HanyadikSzek(egyed,NAME,NICHOLAS);
    return !(egyed2<egyed1 && egyed1<egyed3);
}
