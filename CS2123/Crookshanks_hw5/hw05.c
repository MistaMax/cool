#include<stdio.h>
#include<stdlib.h>


typedef struct nodeT{
  int key;
  struct nodeT *left, *right;
}nodeT;

//nodeT *node;
//nodeT *t;


nodeT *FindMin(nodeT *t)
{
  if(t == NULL)
    return NULL; //no elements in the tree
  if(t->left)
    return FindMin(t->left); //keep going down the left side of the tree
  else
    return t; //found smallest value at end of left tree
}

nodeT *FindMax(nodeT *t)
{
  if(t == NULL)
    return NULL; //no elements in the tree
  if(t->right)
    return FindMax(t->right); //go down the right side of the tree
  else
    return t;
}

nodeT *Insert(nodeT *t, int key)
{
  if(t == NULL) //tree is empty
    {
      nodeT *temp;
      temp = (nodeT *)malloc(sizeof(nodeT));
      temp->key = key;
      temp->left = temp->right = NULL;
      return temp;
    }
  
  if(key > (t->key))
    { //new value > key, move to the right of key in the tree
      t->right = Insert(t->right, key);
    }
  else if(key < (t->key))
    { //new value < key, move to the left of the key in the tree
      t->left = Insert(t->left, key);
    }
  
  return t;
}


nodeT *Delete(nodeT *t, int key)
{
  nodeT *temp;
  if(t == NULL)
    printf("Element not found");
  //if the value you're looking to delete is less than the key value at this position in the tree
  else if(key < t->key)
    t->left = Delete(t->left, key); //keep moving down the left side
  else if(key > t->key)
    t->right = Delete(t->right, key); //keep moving down the right side
  else
    {
      //found the node, now need to delete it and replace it with either the min element
      //in the right subtree of the max element in the left subtree
      if(t->right && t->left)
    {
      temp = FindMin(t->right);
      t->key = temp->key;
      t->right = Delete(t->right, temp->key);
    }
      else
    {
      //if there is only one or zero children
      temp = t;
      if(t->left == NULL)
        t = t->right;
      else if(t->right == NULL)
        t = t->left;
      free(temp); //this key has been removed and the memory is no longer needed
    }
    }
  return t;
}

//finding nodes in a binary search tree
nodeT *FindNode(nodeT *t, int key)
{
  while(t != NULL){
    if(key == t->key) return t;
    if(key < t->key){
      t = t->left; //search in left subtree
    }else{
      t = t->right; //search in right subtree
    }
  }
  return NULL;
}

//tree traversal in order
//call with DisplayTree(t)
void DisplayTree(nodeT *t)
{
  if(t == NULL)
    return;

  DisplayTree(t->left);
  printf("%d ", t->key);
  DisplayTree(t->right);
}

//preorder
void PreOrderWalk(nodeT *t)
{
  if(t != NULL){
    printf("%d ", t->key);
    DisplayTree(t->left);
    DisplayTree(t->right);
  }
}

//postorder
void PostOrderWalk(nodeT *t)
{
  if(t != NULL){
    DisplayTree(t->left);
    DisplayTree(t->right);
    printf("%d ", t->key);
  }
}

//find the height
int height(nodeT *t)
{
  if(t == NULL)
    return 0;
  else
    {
      int lheight = height(t->left);
      int rheight = height(t->right);

      if(lheight > rheight)
    return(lheight+1);
      else
    return(rheight+1);
    }
}

void printLevelOrder(nodeT* t)
{
  int h = height(t);
  int i;
  for(i = 1; i <= h; i++)
    printLevel(t, i);
}

//print nodes at a given level
void printLevel(struct nodeT* t, int level)
{
  if(t == NULL)
    return;
  if(level == 1)
    printf("%d ", t->key);
  else if(level > 1)
    {
      printLevel(t->left, level-1);
      printLevel(t->right, level-1);
    }
}

//find the sum
int sum(nodeT *t)
{
  int total = 0;
  if(t == NULL)
    return 0;
  else
    {
      return(t->key + sum(t->left) + sum(t->right));
    }
}

void quit(nodeT *t)
{
  if(t != NULL)
    {
      quit(t->left);
      quit(t->right);
      free(t);
    }
}

int main()
{
  nodeT *root = NULL;
  nodeT *temp;
  char input;
  int userInput;
  int count = 0;
  

  printf("Enter a command: \n I for Insert, \n F for Find \n D for Delete \n T for List inorder \n P for List preorder");
  printf("\n O for List postorder \n L for List levelorder \n M for Max \n N for Min \n H for Height \n C for Count \n S for Sum \n Q to quit\n");

  scanf("%s", &input);
  while(input != '\0')
    {
      if(input == 'I') //insert
    {
      printf("Enter a positive int: \n");
      scanf("%d", &userInput);
      root = Insert(root, userInput);
      count++;
      DisplayTree(root); //for testing
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'F') //find
    {
      printf("Enter a positive int: \n");
      scanf("%d", &userInput);
      root = FindNode(root, userInput);
      DisplayTree(root); //for testing
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'D') //delete
    {
      printf("Enter a positive int: \n");
      scanf("%d", &userInput);
      root = Delete(root, userInput);
      count--;
      DisplayTree(root); //for testing
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'T') //in order
    {
      DisplayTree(root);
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'P') //pre order
    {
      PreOrderWalk(root);
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'O') //post order
    {
      PostOrderWalk(root);
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'T') //level order
    {
      printLevelOrder(root); //doesn't exist yet
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
      }
      else if(input == 'M') //Max
    {
      temp = FindMax(root);
      printf("Max element is %d\n", temp->key);
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'N') //Min
    {
      temp = FindMin(root);
      printf("Min element is %d\n", temp->key);
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'L') //level order
    {
      printLevelOrder(root);
      printf("\n");
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'H') //height
    {
      int treeHeight = height(root);
      printf("Height is %d\n", treeHeight);
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'C') //count
    {
      printf("The count of the number of elements is %d\n", count);
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'S') //sum
    {
      int total = sum(root);
      printf("Sum of all elements is %d\n", total);
      printf("Enter a command again.\n");
      scanf("%s", &input);
    }
      else if(input == 'Q') //quit
    {
      quit(root);
      //exit(-1);
      break;
    }
      else
    {
      printf("Invalid input, please enter a valid command.\n");
      scanf("%s", &input);
    }
    }
}