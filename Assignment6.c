/*
Carson Scohera
COP3502 Assignment 6
4/18/24
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//max size
#define MAX 100001

typedef struct Node Node;
struct Node {
    int subTrieAmount;
    int myAmount;
    Node * children[32];
    int flag;
};

void insertNode(Node ** root, char * word, int foodAmt);
void SUM(Node *root, char * word);
void deleteTrie(Node * root);
void changeResponse(Node * root, char * response, char * newresponse);


int main(void){

    Node *root = NULL;
    char choice[20] = "";
    int foodAmt;
    char response[MAX], newresponse[MAX];

    //loops until quit
    while (!(strcmp(choice, "QUIT") == 0)){

        scanf("%s", choice);
    
        if (strcmp(choice, "ADD") == 0){
            scanf("%s %d", response, &foodAmt);
            insertNode(&root, response, foodAmt);
        }
    
        if (strcmp(choice, "CHANGE") == 0){
            scanf("%s %s", response, newresponse);
            changeResponse(root, response, newresponse);
        }
    
        if (strcmp(choice, "SUM") == 0){
            scanf("%s", response);
            SUM(root, response);
        }
    }

    //done so delete trie
    deleteTrie(root);

    //see you space cowboy
    return 0;
}

void insertNode(Node ** root, char * response, int foodAmt){
    int index;
    int tempFood;
    tempFood = foodAmt;

    if (*root == NULL){ //check if tree is empty 
        *root = (Node *) calloc(1, sizeof(Node)); //create new root
    }
    
    //adding food to total
    (*root)->subTrieAmount += tempFood;

    //looping until end of word    
    while (response[0] != '\0'){
        //need to map/determine if char is letter or number to map correctly
        if(response[0] >= '0' && response[0] <= '9'){
            index = response[0] - '0';
            response++;
            root = &((*root)->children[index]);
        }
        else if(response[0] >= 'a' && response[0] <= 'v'){
            index = response[0] - 'a';
            index += 10;
            response++;
            root = &((*root)->children[index]);
        }
        else
            return; //invalid character
    
        if (*root == NULL) //check if child did not exist
            *root = (Node *) calloc(1,sizeof(Node)); //create new root

        
        //want to make sure we add total trie amount to each node so we can make adding sum easier
        (*root)->subTrieAmount += tempFood;
        
    }
        //putting the food amt at last node
        (*root)->myAmount += foodAmt;
        (*root)->flag = 1;
        
}

//function that changes response to something else
void changeResponse(Node * root, char * response, char * newresponse){
    Node * cur = root;
    int length;
    int index;
    length = strlen(response);

    //incase change called with nothing to change
    if (root == NULL)
        return;

    //if for some reason they change response to the same thing just return
    if(strcmp(response,newresponse) == 0)
        return;
    
        //want to get old responses food amount
        for (int i = 0; i < length; i++){
            if(response[i] >= '0' && response[i] <= '9'){
            index = response[i] - '0';
            }
            else if(response[i] >= 'a' && response[i] <= 'v'){
                index = response[i] - 'a';
                index += 10;
            }
            else
                return;
            
            //go until end of word to get myamount
            cur = cur->children[index];
        }
        //getting amount and setting old response back to zero
        int amt = cur->myAmount;
        cur->subTrieAmount = cur->subTrieAmount - cur->myAmount;
        cur->myAmount = 0;

        //if prefix
        if (response[0] == newresponse[0]){
            
            //traversing the string
            length = strlen(newresponse);

            for (int i = 0; i < length; i++){
            if(newresponse[i] >= '0' && newresponse[i] <= '9'){
            index = newresponse[i] - '0';
            }
            else if(newresponse[i] >= 'a' && newresponse[i] <= 'v'){
                index = newresponse[i] - 'a';
                index += 10;
            }
            else
                return;       
            
            //go until end of word to get new myamount
            root = root->children[index];   
        }
            //changing where in prefix the food is if newresponse starts with same letter
            root->myAmount = amt;
        }
        //insert the node
        insertNode(&root, newresponse, amt);
        cur->myAmount = 0;
                
    }

//delete trie
void deleteTrie(Node * root){
    if (root == NULL)
        return;

    for (int i = 0; i < 32; i++){
        deleteTrie(root->children[i]);
    }
    free(root);
}

//gets min and max food amounts
void SUM(Node *root, char * response){
    Node *lookResponse = root;
    int index;
    int min = 0, max = 0;

    //incase sum called before any responses are added
    if (root == NULL){
        printf("%d %d", min, max);
        return;
    }

    //i want to confirm that the requested sum of responses actully exists
    for (int i = 0; response[i] != '\0'; i++){
        
        if(response[i] >= '0' && response[i] <= '9'){
            index = response[i] - '0';
        }
        else if(response[i] >= 'a' && response[i] <= 'v'){
            index = response[i] - 'a';
            index += 10;
        }
        else
            return;
        //breaks out if child doesn't exist
    if (lookResponse->children[index] == NULL) {
            break;
        }
        //go to next index
        lookResponse = lookResponse->children[index];
        
    }

    //sum is valid so now traverse 
    if (lookResponse != NULL) {
            
            //if sum of single character min and max will be same
            if (response[1] == '\0'){
                max += lookResponse->myAmount;
                min = max;
                printf("%d %d \n", min, max);
                return;
            }
            //resest lookresponse so we can travse word
            lookResponse = root;
            
            //travese word
        for (int i = 0; response[i] != '\0'; i++){

            if (lookResponse == NULL) break;

            if(response[i] >= '0' && response[i] <= '9'){
                index = response[i] - '0';
            }
            else {
                index = response[i] - 'a';
                index += 10;
            }
                    //add to my amount 
                    max += lookResponse->myAmount;
                
                //go on 
                lookResponse = lookResponse->children[index];

        }
            
        //only add if word exits beyond
        if (lookResponse != NULL){
            max += lookResponse->subTrieAmount;
            min += lookResponse->subTrieAmount;
        }
        printf("%d %d\n", min, max);
        
    }

}


