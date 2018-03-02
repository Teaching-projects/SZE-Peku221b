// Crossover 1.0
temp[k]=Keresztez(populacio[POPMERET-1],populacio[0]);
k++;
for (j=0;j<POPMERET-1;j++){
	temp[k]=Keresztez(populacio[j],populacio[j+1]);
	k++;
}
// Crossover 2.0
for (j=0;j<POPMERET;j++){
     int x=rand()%POPMERET;
     int y=rand()%POPMERET;
     temp[k]=Keresztez(populacio[x],populacio[y]);
     k++;
}
