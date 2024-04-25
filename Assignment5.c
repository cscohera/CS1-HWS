/*Carson Scohera
 COP3502C
 3/28/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node struct used

typedef struct Node Node;
struct Node
{
    Node *left, *right, *parent;
    int hat;
    int x;
    long long int food;
};

//function prototypes
Node *createNode(int location, int hatSize);
Node *insertRaccoon(Node *root, int location, int hatSize);
Node *captureRaccoon(Node *root, int location);
Node *changeHat(Node *current, int location, int hatSize);
void stealFood(Node *root, int location, int amt);
Node *findClosest(Node *root, int location);
Node *rotateLeft(Node *current);
Node *rotateRight(Node *current);
void printTree(Node *root);


int main()
{
    //declarations
    Node *root = NULL;
    int location, hatSize, nearestRaccoon;
    long long int food;
    char choice[20] = "";

    //loops until QUIT
    while (!(strcmp(choice, "QUIT") == 0))
    {
        scanf("%s", choice);
    
        if (strcmp(choice, "ADD") == 0)
        {
            scanf("%d %d", &location, &hatSize);
            root = insertRaccoon(root, location, hatSize);
        }

        if (strcmp(choice, "CAPTURE") == 0)
        {
            scanf("%d", &location);
            root = captureRaccoon(root, location);
        }

        if (strcmp(choice, "HAT") == 0)
        {
            scanf("%d %d", &location, &hatSize);
            root = changeHat(root, location, hatSize);
        }

        if (strcmp(choice, "STEAL") == 0)
        {
            scanf("%d %lld", &location, &food);
            stealFood(root, location, food);
        }
        
    }
    //prints tree
    printTree(root);
    return 0;
}

//creating individual raccoon nodes
Node *createNode(int location, int hatSize)
{
    Node *res;
    res = (Node *)malloc(sizeof(Node));
    res->x = location;
    res->hat = hatSize;
    res->left = res->right = res->parent = NULL;
    res->food = 0;
    return res;
}

//inserting a raccoon node
Node *insertRaccoon(Node *root, int location, int hatSize)
{
    //no nodes create
    if (root == NULL)
        return createNode(location, hatSize);

    // Child the parent for the insertion
    Node *parent = NULL;
    Node *child = root;

    // 1 for right 0 for left
    int weRight = 1;

    while (child)
    {
        if (child->x < location)
        {
            // Go right
            parent = child;
            child = parent->right;
            weRight = 1;
        }
        else if (child->x > location)
        {
            // Go left
            parent = child;
            child = parent->left;
            weRight = 0;
        }
        else
        {
            // Duplicate node avoid
            return root;
        }
    }
    // Insert at the location with parent as parent
    if (parent->x < location)
    {
        parent->right = createNode(location, hatSize);
        parent->right->parent = parent;
    }
    else
    {
        parent->left = createNode(location, hatSize);
        parent->left->parent = parent;
    }
    // Rebalance loop
    while (parent)
    {

        //if node has two children 
        if (parent->right != NULL && parent->left != NULL)
        {   
            //biggesthat used to check who of children have bigger hat and if bigger than parent rotate
            //go right used to know which way we need to go
            int biggestHat = parent->right->hat;
            int goRight = 1;
            if (parent->left->hat > biggestHat)
            {
                biggestHat = parent->left->hat;
                goRight = 0;
            }
            //need a rotation if child has bigger hat than parent
            if (biggestHat > parent->hat)
            {
                if (goRight)
                {   
                    // if node exists
                    if (parent->right->left != NULL)
                    {
                        rotateRight(parent->right);
                    }
                    rotateLeft(parent);

                    parent = parent->left;
                }
                else
                {
                    //if node exists
                    if (parent->left->right != NULL)
                    {
                        rotateLeft(parent->left);
                    }
                    rotateRight(parent);

                    parent = parent->right;
                }
            }
        }
            //one child left
        else if (parent->left != NULL)
        {
                //rotation needed
            if (parent->left->hat > parent->hat)
            {
                    //if node exists
                if (parent->left->right != NULL)
                {
                    rotateLeft(parent->left);
                }
                rotateRight(parent);
            }
        }
            //one child right
        else if (parent->right != NULL)
        {   
                //rotation needed
            if (parent->right->hat > parent->hat)
            {
                    //if node exists
                if (parent->right->left != NULL)
                {
                    rotateRight(parent->right);
                }
                rotateLeft(parent);
            }
        }
        //if no children go up
        parent = parent->parent;
    }
    // Find the new root
    while (root->parent)
    {
        root = root->parent;
    }
    return root;
}

//raccoon removal 
Node *captureRaccoon(Node *root, int location)
{
    //looking for racoon to remove
    Node *cur = root;
    while (cur && cur->x != location)
    {
        if (cur->x < location)
        {
            // Go right
            cur = cur->right;
        }
        else if (cur->x > location)
        {
            // Go left
            cur = cur->left;
        }
    }
    // Value not in tree
    if (!cur)
        return root;

    // Node should be removed
    Node *par = cur->parent;

    if (cur->left == NULL || cur->right == NULL)
    {
        // 1 child case (also handles 0 child case)
        Node *child = cur->right;
        if (!child)
        {
            child = cur->left;
        }
        //prints and we run change hat to check and see if hat can be used for another raccoon still in tree
        printf("%lld\n", cur->food);
        changeHat(root, cur->x, cur->hat);
        free(cur);
        if (child)
            child->parent = par;
        if (!par)
        {
            // Tree's root is now child
            return child;
        }
        if (par->left == cur)
        {
            par->left = child;
        }
        else
        {
            par->right = child;
        }
        // Balance tree up to root to fix tree after removal 
        while (par)
        {
            
                //two child case
            if (par->right != NULL && par->left != NULL)
            {
                //does child have smaller or larger hat than parent if larger roatate
                //go right used to know which way we need to go
                int biggestHat = par->right->hat;
                int goRight = 1;
                if (par->left->hat > biggestHat)
                {
                    biggestHat = par->left->hat;
                    goRight = 0;
                }
                if (biggestHat > par->hat)
                {
                    if (goRight)
                    {
                        //does node exist
                        if (par->right->left != NULL)
                        {
                            rotateRight(par->right);
                        }
                        rotateLeft(par);

                        par = par->left;
                    }
                    else
                    {
                        //does node exist
                        if (par->left->right != NULL)
                        {
                            rotateLeft(par->left);
                        }
                        rotateRight(par);

                        par = par->right;
                    }
                }
            }
                //one child to roatae
            else if (par->left != NULL)
            {
                if (par->left->hat > par->hat)
                {
                        //does node exist
                    if (par->left->right != NULL)
                    {
                        rotateLeft(par->left);
                    }
                    rotateRight(par);
                }
            }

            else if (par->right != NULL)
            {
                if (par->right->hat > par->hat)
                {
                        //does node exist
                    if (par->right->left != NULL)
                    {
                        rotateRight(par->right);
                    }
                    rotateLeft(par);
                }
            }
            root = par;
            par = par->parent;
            
        }
        // Return root;
        
        return root;
    }
    // 2 child case we switch nodes until 1 child case then remove
    Node *pred = cur->left;
    while (pred->right)
    {
        pred = pred->right;
    }
    
    // Swap with pred to keep data of child node not being removed
    int tmpX = cur->x;
    long long int tmpF = cur->food;
    int tmpH = cur->hat;

    cur->x = pred->x;
    cur->food = pred->food;
    cur->hat = pred->hat;

    pred->x = tmpX;
    pred->food = tmpF;
    pred->hat = tmpH;
    // Remove the data from the subtree
    return captureRaccoon(cur->left, location);
}

//changes raccoon hats
Node *changeHat(Node *current, int location, int hatSize)
{
    //run findclosest
    Node *curRac = findClosest(current, location);

    //if there is a raccoon and its hatsize is smaller than the hat it changes hat or it destroys and keeps cur hat
    if (curRac != NULL && curRac->hat < hatSize)
    {
        curRac->hat = hatSize;
    }
    else
        return current;

    //with hat change checking if we now need to rotate tree to account for possible change in hat hierachy
    while (curRac)
    {

            //same as insertion and deltion code two child
        if (curRac->right != NULL && curRac->left != NULL)
        {
            //does child have smaller or larger hat than parent if larger roatate
            //go right used to know which way we need to go
            int biggestHat = curRac->right->hat;
            int goRight = 1;
            if (curRac->left->hat > biggestHat)
            {
                biggestHat = curRac->left->hat;
                goRight = 0;
            }
            //need a rotation if child has bigger hat than parent
            if (biggestHat > curRac->hat)
            {
                if (goRight)
                {
                        //does node exists
                    if (curRac->right->left != NULL)
                    {
                        rotateRight(curRac->right);
                    }
                    rotateLeft(curRac);

                    curRac = curRac->left;
                }
                else
                {
                        //does node exists
                    if (curRac->left->right != NULL)
                    {
                        rotateLeft(curRac->left);
                    }
                    rotateRight(curRac);

                    curRac = curRac->right;
                }
            }
        }
            //one child case left
        else if (curRac->left != NULL)
        {   
            //is hat bigger than parent
            if (curRac->left->hat > curRac->hat)
            {
                    //does node exist
                if (curRac->left->right != NULL)
                {
                    rotateLeft(curRac->left);
                }
                rotateRight(curRac);
            }
        }
            //one child case right
        else if (curRac->right != NULL)
        {
            //is hat bigger than parent
            if (curRac->right->hat > curRac->hat)
            {
                if (curRac->right->left != NULL)
                {
                    rotateRight(curRac->right);
                }
                rotateLeft(curRac);
            }
        }

        curRac = curRac->parent;
    }
    // Find the new root
    while (current->parent)
    {
        current = current->parent;
    }

    return current;
}

//deals with stealing food
void stealFood(Node *root, int location, int amt)
{
    //find closest raccoon
    Node *curRac = findClosest(root, location);

    //if raccoon exists bring food up the ladder of command giving each raccoon its fair share
    if (curRac != NULL)
    {
        curRac->food += amt;

        while (curRac->parent)
        {
            curRac->parent->food += amt - amt / 2;
            curRac->food -= amt - amt / 2;
            amt = amt - amt / 2;
            curRac = curRac->parent;
        }
    }
}

//finds closest raccoon 
Node *findClosest(Node *root, int location)
{
    Node *nearestRaccoon;
    nearestRaccoon = root;

    // goes through raccoon tree 
    while (root != NULL)
    {
        // if the distance is smaller than we can update the closet raccoon until null in which we will have smallest distance
        //using absloute value to account for possible negatives that are larger distance than a positve subtracion 
        if ((abs(root->x - location)) < (abs(nearestRaccoon->x - location)))
            nearestRaccoon = root;

        // if equal distance raccoons then check which racoon has smaller hat
        if ((abs(root->x - location)) == (abs(nearestRaccoon->x - location)))
        {
            if (root->hat < nearestRaccoon->hat)
                nearestRaccoon = root;
        }

        // traversal checking each node depending on location
        if (location < root->x)
            root = root->left;
        else if (location > root->x)
            root = root->right;
        else
            return root;
    }

    return nearestRaccoon;
}

//rotate left
Node *rotateLeft(Node *current)
{
    
    // Get pointers to the parent, child, and grandchild
    Node *par = current->parent;
    Node *ch = current->right;
    Node *gc = ch->left;
    // Top edge
    ch->parent = par;
    // Check parent's existance
    if (par)
    {
        // Check the side of the rotated node for its parent
        if (par->right == current)
        {
            par->right = ch;
        }
        else
        {
            par->left = ch;
        }
    }
    // Middle edge
    ch->left = current;
    current->parent = ch;
    // Bottom edge
    current->right = gc;
    if (gc)
    { // Check grandchild's existance
        gc->parent = current;
    }

    return ch;
}

//rotate right
Node *rotateRight(Node *current)
{

    // Get pointers to the parent, child, and grandchild
    Node *par = current->parent;
    Node *ch = current->left;
    Node *gc = ch->right;
    // Top edge
    ch->parent = par;
    // Check parent's existance
    if (par)
    {
        // Check the side of the rotated node for its parent
        if (par->right == current)
        {
            par->right = ch;
        }
        else
        {
            par->left = ch;
        }
    }
    // Middle edge
    ch->right = current;
    current->parent = ch;
    // Bottom edge
    current->left = gc;
    if (gc)
    { // Check grandchild's existance
        gc->parent = current;
    }

    return ch;
}

//prints pre order traversel of nodes
void printTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d %lld\n", root->x, root->food);
    printTree(root->left);
    printTree(root->right);

}
