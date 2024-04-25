/*Carson Scohera
 COP3502C
 2/11/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rowStart 502
#define colStart 502


//structs used for stacks of each elephants movements/location
struct Node {
    int r, c;
   struct Node * next;
};


struct Elephant {
    struct Node *head;
};

//stack functions
struct Elephant *createStack(int row, int col);
struct Node *push(struct Elephant * stk, int row, int col);
struct Node * pop(struct Elephant * stk);


int main(){

    //creating variables and grid with buffer to allow for easier movement checks for elephants
    int num_ele, row, col, total;
    char input[20];
    int grid[502][502];
    scanf("%d", &num_ele);

    //creating array of elephants
    struct Elephant * array[num_ele];

    //creating stack for each elephant inputted
    for (int i = 0; i < num_ele; i++){
        scanf("%d %d", &row, &col);
        array[i] = createStack(row, col);
    }
    //runs until quit entered
    while (!(strcmp(input, "QUIT") == 0)){

    int melonAmt;
     scanf("%s", input);

    //if choice is BAIT then sets grid location to that melon amt
    if (strcmp(input, "BAIT") == 0){
        scanf("%d %d %d", &row, &col, &melonAmt);
        grid[row][col] += melonAmt;
    }

    //if choice is hour loops through all elephants checking the grid for melons in adacent squares as well as squares with most amt of melons
    //then updates elephants postions and eats if there is food in second loop once all elephants have looked and may or may not have moved
    if (strcmp(input, "HOUR") == 0){

        total = 0;

        for(int i = 0; i < num_ele; i++){
            int r = array[i]->head->r;
            int c = array[i]->head->c;
            int highest = grid[r][c];

            if (grid[array[i]->head->r + 1][array[i]->head->c] > highest) {
                highest = grid[array[i]->head->r + 1][array[i]->head->c];
                r = array[i]->head->r + 1;
                c = array[i]->head->c;
            } else if (grid[array[i]->head->r - 1][array[i]->head->c] > highest) {
                highest = grid[array[i]->head->r - 1][array[i]->head->c];
                r = array[i]->head->r - 1;
                c = array[i]->head->c;

            } else if (grid[array[i]->head->r][array[i]->head->c + 1] > highest) {
                highest = grid[array[i]->head->r][array[i]->head->c + 1];
                r = array[i]->head->r;
                c = array[i]->head->c + 1;

            } else if (grid[array[i]->head->r][array[i]->head->c - 1] > highest) {
                highest = grid[array[i]->head->r][array[i]->head->c - 1];
                r = array[i]->head->r;
                c = array[i]->head->c - 1;
            }

            //No food elephant moves back
            if (highest == 0){
                if (array[i]->head->next != NULL)
                    array[i]->head = pop(array[i]);
                
            //food on elephant
            } else if (grid[array[i]->head->r][array[i]->head->c] > 0){
                continue;

            //Food in range elephant moves to food
            } else {
                array[i]->head = push(array[i], r, c);
            }
        }
        //elephant eats food and hour food total is then printed
        for(int i = 0; i < num_ele; i++){
                total += grid[array[i]->head->r][array[i]->head->c];
                grid[array[i]->head->r][array[i]->head->c] = 0;
        }
        printf("%d \n", total);
    }

    }
    //prints elephant locations and then we free memory
    for(int i = 0; i < num_ele; i++){
        printf("%d %d\n", array[i]->head->r, array[i]->head->c);
        
        while(array[i]->head != NULL)
            array[i]->head = pop(array[i]);

        free(array[i]);
    }
    return 0;
}

//creating the stack for each elephant
struct Elephant *createStack(int row, int col){
   struct Elephant *res = (struct Elephant *)malloc(sizeof(struct Elephant));

   res->head = push(res, row, col);
   return res;
}
//adds elephant movements to the stack
struct Node *push(struct Elephant * stk, int row, int col){
    struct Node *res =(struct Node *)malloc(sizeof(struct Node));
    
    res->r = row;
    res->c = col;

    res->next = stk->head;
    return res;

}
//takes elephant movements off the stack
struct Node * pop(struct Elephant * stk){
    if (stk->head == NULL){
        return NULL;
    }

    struct Node *newHead = stk->head->next;
    free(stk->head);
    return newHead;
}
