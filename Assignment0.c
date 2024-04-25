
/*Carson Scohera
 COP3502C
 1/12/2024
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//giving enough room fof cats names plus concats of family names
#define MAX_STR_LEN 114


//creating a struct that holds cats names and if the cat is taken or not
typedef struct {

    char cats_name[MAX_STR_LEN];
    int has_cat;

} all_cats;



int main(void){

    //defining varibles
    int num_cozy_cages, num_weeks, test = 0;
    int Family1 = 0, Family2 = 1, Family3 = 2;
    int temp1 = 0, temp2 = 1, temp3 = 2;

    //creating array of struct cats to hold up to the max amount of cozy cages and cats created 
    all_cats cats[500];

    //scaning in user input
    scanf("%d", &num_cozy_cages);
    scanf("%d", &num_weeks);
    

    //for each cozy cage bringing each cats name to a struct for that cat and setting who has the cat to zero since no one has the cat
    for (int i=0; i<num_cozy_cages; i++){
        scanf("%s", cats[i].cats_name);
        cats[i].has_cat = 0;
    }

    //setting cats in starting postion based on day of the week they adopt
    strcat(cats[0].cats_name, "Lee");
    strcat(cats[1].cats_name, "Lyn");
    strcat(cats[2].cats_name, "Eve");


    //giving first three cats at familys position the has cat = to 1 to know that the family has those cats
    cats[0].has_cat = 1;
    cats[1].has_cat = 1;
    cats[2].has_cat = 1;

    
    //looping through user inputed amount of weeks
    for (int i = 1 ; i < num_weeks; i++){
        
        //logic that determines each new familys postion and when they go above the amount of cozy cages brings it back 
        Family1 = (2 + Family1) % num_cozy_cages;
        Family2 = (3 + Family2) % num_cozy_cages;
        Family3 = (5 + Family3) % num_cozy_cages;


        
        //if the cat has not been taken a family takes cat concats name and changes has cat to 1
        if (cats[Family1].has_cat == 0) {
            strcat(cats[Family1].cats_name, "Lee");
            cats[Family1].has_cat = 1;
        }

        //needed temp in order to store previous weeks has cat or does not has cat so that Familys don't concat when theyre is a cat in new week
        cats[temp1].has_cat = 0;


        if(cats[Family2].has_cat == 0){
            strcat(cats[Family2].cats_name, "Lyn");
            cats[Family2].has_cat = 1;
        }
        cats[temp2].has_cat = 0;


        if(cats[Family3].has_cat == 0){
            strcat(cats[Family3].cats_name, "Eve");
            cats[Family3].has_cat = 1;
        }
        cats[temp3].has_cat = 0;

        //setting temp equal to now previous week families
        temp1 = Family1;
        temp2 = Family2;
        temp3 = Family3;

        
        
    }


        

    //prints out no cat found if family hascat else prints cats name
    for (int i=0; i<num_cozy_cages; i++){
        if(cats[i].has_cat == 1 )
            printf("No cat found. \n");
        else
            printf("%s\n", cats[i].cats_name);
    }

    return 0;
}
