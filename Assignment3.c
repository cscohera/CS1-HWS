/*Carson Scohera
 COP3502C
 2/27/2024
 */

#include <stdlib.h>
#include <stdio.h>

#define CATSMAX 15

//Globas needed
int minCozy = 20000;
int maxCozy = -20000;
int bestComb[CATSMAX];
int worstComb[CATSMAX];
int indivCat[CATSMAX][3];
int catPreferences[CATSMAX][CATSMAX];
int cozinessSum[CATSMAX];

void combination(int numCats, int Index, int *Cats, int *house, int *houseCatCount);

int main() {
    int numCats;
    scanf("%d", &numCats);
    //scaning in each cats inital cozy levels
    for (int i = 0; i < numCats; i++) {
        scanf("%d %d %d", &indivCat[i][0], &indivCat[i][1], &indivCat[i][2]);
    }
    //scaning in each cats preferences to other cats
    for (int i = 0; i < numCats; i++) {
        for (int j = 0; j < numCats; j++) {
            scanf("%d", &catPreferences[i][j]);
        }
    }
    //arrays used to keep track of cats, which house, and cats in each house within each combination
    int Cats[numCats];
    int house[numCats]; 
    int houseCatCount[numCats];

    //starting each number in house cat count at zero so that if it gets to 1 we know there is at least one cat in the house
    for (int i = 0; i < numCats; i++){
        houseCatCount[i] = 0;

    }
    combination(numCats, 0, Cats, house, houseCatCount);
    //final answer printing
    printf("%d %d\n", maxCozy, minCozy);

    return 0;
}

void combination(int numCats, int Index, int *Cats, int *house, int *houseCatCount) {
    int cozyValue = 0;

    //makes sure it runs for all cats
    for (int i = 0; i < numCats; i++){
    //base case hit when the numcats is equal to the index as we have went through all cats for that combonation
    if (numCats == Index) {
        
        // stop processing this combination there isn't a cat in every house 
        for (int i = 0; i < numCats; i++) {
            if (houseCatCount[house[i]] == 0){
                return;  
            }  
        }
            int sum = 0;
            for (int i = 0; i < numCats; i++) {
                cozinessSum[i] = indivCat[i][house[i]];
                //checks to make sure the cat i is not comparing with its self then at same time checks to see if cat i and j are in the same house
                //if so then adds their preferences to the coziness sum
                for (int j = 0; j < numCats; j++) {
                    if (i != j && house[i] == house[j])
                        cozinessSum[i] += catPreferences[i][j];
                }
                sum += cozinessSum[i];
                //from all combinations using sum to check to see if its the best combination of cat preferences
                if (sum > maxCozy){
                    maxCozy = sum;
                    for(int i = 0; i < numCats; i++){
                        bestComb[i] = house[i];
                    }

                }
                //from all the combinations using sum to check to see if its the worst best combination of cat preferences
                if (sum < minCozy){
                    minCozy = sum;
                    for (int i = 0; i < numCats; i++){
                        worstComb[i] = house[i];
                    }
                }
            }
            return;
    }
    //main recursive loops that executes for each house
    // I set cats[index] and house[index] = i in order to set the cat to that house
    //for that combination then we increment houseCatCount cause we have a cat in the house 
    //then we recurse index and increase by 1 as we go through to the next cat
    //I then set houseCatCount to 0 so that other iterations houseCatCount start at zero
    for (int i = 0; i < 3; i++) {
        Cats[Index] = i; 
        house[Index] = i; 
        houseCatCount[house[i]]++;
        combination(numCats, Index + 1, Cats, house, houseCatCount);
        houseCatCount[house[i]] = 0;
        
    }

    return;
    }
}