/*Carson Scohera
 COP3502C
 1/27/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 20

//created array of struct locations and array of struct placements inside each location

typedef struct {

    long long int identifer_num;
    long long int previous_food_level;
    long long int takenFood;

} Placement;

typedef struct {
    
    char * locationName;
    int size, cap;
    Placement * placementArray;
    
} Location;

typedef struct {
    int size, cap;
    Location * locationArray;
} LocalArrayList;

LocalArrayList createlocationlist();
LocalArrayList add_location_to_list(LocalArrayList Full_location_list, char * location);
void printlocations(LocalArrayList Full_location_list);
Location addPlacement(Location Full_location_list, int ID);
Location createLocation(char * name);

int main(void){

    //creating array list
    LocalArrayList Full_location_list = createlocationlist();

    long long int ID = 0;
    long long int Food_level = 0;
    
    char locationName[MAXLEN] = "";

    scanf(" %s %lld %lld", locationName, &ID, &Food_level);

    //loops user input until END -1 -1
    while (!(strcmp(locationName, "END") == 0 && ID == -1 && Food_level == -1)){

            //if location is first location in array
        if (Full_location_list.size == 0) {
            printf("New placement.\n");
            Full_location_list = add_location_to_list(Full_location_list, locationName);
            Full_location_list.locationArray[0] = addPlacement(Full_location_list.locationArray[0], ID);
            Full_location_list.locationArray[0].placementArray[0].previous_food_level = Food_level;
        }
        //checking if not the first location then if the location has been added already
        else{
        int found = 0;
        for (int i = 0; i < Full_location_list.size; i++)
        {
            
                //if location has been added already
            if (strcmp(Full_location_list.locationArray[i].locationName, locationName) == 0) {

                //founds used as flags
                //checking to see if the id value has been added inside the now known added location
                int found2 = 0;

                for (int j = 0; j < Full_location_list.locationArray[i].size; j++){
                    if (Full_location_list.locationArray[i].placementArray[j].identifer_num == ID){

                        long long int math = Full_location_list.locationArray[i].placementArray[j].previous_food_level - Food_level;
                        
                        //used to determine food levels based on postive or negative bait level
                        if(math <= 0) {
                            printf("%d\n", 0);
                            Full_location_list.locationArray[i].placementArray[j].previous_food_level = Food_level;
                        } 
                        else {
                            printf("%lld\n", math);
                            Full_location_list.locationArray[i].placementArray[j].takenFood += math;
                            Full_location_list.locationArray[i].placementArray[j].previous_food_level = Food_level;
                        }
                        found2 = 1;
                        break;
                    }
                }
                //if the location is found but placement is new 
                if (!found2){
                    printf("New placement.\n");
                    Full_location_list.locationArray[i] = addPlacement(Full_location_list.locationArray[i], ID);
                    Full_location_list.locationArray[i].placementArray[Full_location_list.locationArray[i].size - 1].previous_food_level = Food_level;
                }

                found = 1;
                break;
            }
        }
        //if the location is new adds it to location array and adds its placement
        if (!found) {
            printf("New placement.\n");
            Full_location_list = add_location_to_list(Full_location_list, locationName);
            Full_location_list.locationArray[Full_location_list.size - 1] = addPlacement(Full_location_list.locationArray[Full_location_list.size - 1], ID);
            Full_location_list.locationArray[Full_location_list.size - 1].placementArray[0].previous_food_level = Food_level;
        }
        }
        

        //repeat until END
        scanf(" %s %lld %lld", locationName, &ID, &Food_level);

    }

    //prints all locations and frees memory
    printlocations(Full_location_list);
    
    free(Full_location_list.locationArray);

    return 0;
}

//creates array of locations 
LocalArrayList createlocationlist(){
    LocalArrayList list_start;
    list_start.size=0;
    list_start.cap=10;

    list_start.locationArray = (Location *) calloc(1 * list_start.cap,sizeof(Location)*10);

    return list_start;
}
//adds locations to location list and resizes accordinly
LocalArrayList add_location_to_list(LocalArrayList Full_location_list, char * location){

    if (Full_location_list.size == Full_location_list.cap){
            //Expand
            Full_location_list.cap *=2;
            Full_location_list.locationArray = (Location *) realloc( Full_location_list.locationArray ,sizeof(Location) * Full_location_list.cap);

    }

    Full_location_list.locationArray[Full_location_list.size] = createLocation(location);
    Full_location_list.size++;

    return Full_location_list;
}

//creating individual locations
Location createLocation(char * name){
    
    Location location;
    
    location.locationName = (char *) calloc(MAXLEN, 1);
    strcpy(location.locationName, name);

    location.cap = 10;
    location.size = 0;

    location.placementArray = (Placement *) calloc(location.cap, sizeof(Placement)); 

    return location;
}


//adding placements to locations
Location addPlacement(Location Full_location_list, int ID){

    if (Full_location_list.size == Full_location_list.cap){
            //Expand
            Full_location_list.cap *=2;
            Full_location_list.placementArray = (Placement *) realloc( Full_location_list.placementArray ,sizeof(Placement) * Full_location_list.cap);

    }

    Full_location_list.placementArray[Full_location_list.size].identifer_num = ID;
    Full_location_list.placementArray[Full_location_list.size].previous_food_level = 0;
    Full_location_list.placementArray[Full_location_list.size].takenFood= 0;

    Full_location_list.size += 1;

    return Full_location_list;

}

//prints and frees memory after
void printlocations(LocalArrayList  Full_location_list){
    
    for (int i = 0; i < Full_location_list.size; i++) {
        long long int sum = 0;
        for (int j = 0; j < Full_location_list.locationArray[i].size; j++)
        {
            sum += Full_location_list.locationArray[i].placementArray[j].takenFood;
        }
        printf("%s %lld \n", Full_location_list.locationArray[i].locationName, sum);

        free(Full_location_list.locationArray[i].placementArray);
        free(Full_location_list.locationArray[i].locationName);
    }
        

}
