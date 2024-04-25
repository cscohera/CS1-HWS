/*Carson Scohera
 COP3502C
 3/8/2024
 */


#include <stdlib.h>
#include <stdio.h>

//structs for stack implementation
struct Node {
   long long int indivCompWealth;
   struct Node * next;
};

struct Stack {
    struct Node * head;
};

//functions needed
struct Stack *createStack();
void push(struct Stack *compStk, long long int indivCompWealth);
long long int pop(struct Stack * compStk);
void merge_sort(long long int *numCompetiotsArray, long long int len);
long long int peek(struct Stack * compstk);



int main(){
    //declaring varibles
    int stackTwoSize = 0;
    int movestoHighest = 0;
    long long int largestPossibleBuy = 0;
    long long int count = 0;
    int numCompetiors;
    long long int btsStartWealth;
    long long int compWealth;

    //creating two stacks 
    struct Stack *compStk = createStack();
    struct Stack *compStk2 = createStack();

    //scaning in bts starting wealth and num competeing shops
    scanf("%d %lld", &numCompetiors, &btsStartWealth);

    long long int numCompetiorsArray[numCompetiors];

    //placing each shops wealth into an array
    for (int i = 0; i < numCompetiors; i++){
        scanf("%lld", &compWealth);
        numCompetiorsArray[i] = compWealth;
        count++;
    }

        //sorts competitors 
        merge_sort(numCompetiorsArray, count);
        
    //pushing sorted array onto stack in order greatest to least
    for(int i = 0; i < numCompetiors; i++){
        push(compStk,numCompetiorsArray[i]);
    }

    
    //takes compstk and looks at top and if btsstartWealth is greater pops onto second stack
    //if its not then it buys whats on top of second stack
    while (compStk->head != NULL){
        if (btsStartWealth > peek(compStk)){
            push(compStk2, pop(compStk));
            } 
        //if btsStartwealth cant buy a value in compStk then check compStk2 and if its empty we return -1 for not possible
        else if (compStk2->head == NULL){
            movestoHighest = -1;
            break;
            } 
        //if not empty we pop the element and increment move to highest 
            else {
            btsStartWealth += pop(compStk2);
            movestoHighest++;
        }
    }

    //final output
    printf("%d\n", movestoHighest);
}

//creates a stack
struct Stack *createStack(){
    struct Stack *compStk;
    compStk = (struct Stack*)malloc(sizeof(struct Stack));
    compStk->head = NULL;
    return compStk;
}

//pushs top number off the stack
void push(struct Stack *compStk, long long int indivCompWealth){
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    if(!temp){
        return;
    }
    temp->indivCompWealth = indivCompWealth;
    temp->next = compStk->head;
    compStk->head = temp;
}

//pops off top number off the stack
long long int pop(struct Stack * compStk){
    long long int indivCompWealth;
    struct Node *temp;
    if (compStk->head == NULL)
        return 0;
    temp = compStk->head;
    compStk->head = compStk->head->next;
    indivCompWealth = temp->indivCompWealth;
    free(temp);
    return indivCompWealth;
}

//looks at to value
long long int peek(struct Stack * compstk){
    if (compstk->head == NULL)
        return 0;
        
    
    return compstk->head->indivCompWealth;
    
}

// Merge sort function sorting from greatest to least
void merge_sort(long long int *numCompetiorsArray, long long int len) {
// Base Case
if (len <= 1) {
return;
}
// Sort the 2 halves
merge_sort(numCompetiorsArray, len / 2);
merge_sort(numCompetiorsArray + (len / 2), len - (len / 2));
// Merge the 2 halves into a temp array
long long int *tmp = (long long int *)malloc(sizeof(long long int) * len);
long long int fptr = 0;
long long int bptr = len / 2;
for (int i = 0; i < len; i++) {
if (fptr == len / 2 || (bptr != len && numCompetiorsArray[bptr] > numCompetiorsArray[fptr])) {
tmp[i] = numCompetiorsArray[bptr];
bptr++;
} else {
tmp[i] = numCompetiorsArray[fptr];
fptr++;
}
}
// Move the contents into the original array
for (int i = 0; i < len; i++) {
numCompetiorsArray[i] = tmp[i];
}
// Clean up the temp array
free(tmp);
}



