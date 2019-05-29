#include <stdio.h>
#include <stdlib.h>
#include "hw4.h"
#include <string.h>


// Helper function to sort an array
void sort_array(int arr[], int len)
{
  // Will use a simple algorithm with nested for loops so it's easy to follow
  int tmp;
  for (int i = 0; i < len; i++){
    for (int j = i+1; j < len; j++){
      if (arr[i] > arr[j]){
	tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
      };
    };
  };
  return;
};


// Helper function to insert array element from a sorted array into tree
ibst_t *insert_bst(int arr[], int len, int low, int high){
  // This takes the median of an array and make it the parent node,
  // then run recursively on the children
  if (low == high){
    return NULL;
  }
  ibst_t *t_out = malloc(sizeof(ibst_t));
  int median = (high + low)/2;
  t_out->root = arr[median];
  t_out->lsub = insert_bst(arr, len, low, median);
  t_out->rsub = insert_bst(arr, len, median + 1, high);
  return t_out;

};


// build a bst containing the numbers in array
// - the bst must not contain any duplicates
// - optional challenge: build a balanced bst (not lopsided)
ibst_t *build_bst(int arr[], int len){
  // We can either sort the array first and assign the tree or just take a 
  // random node and insert into the tree based on last lab's principle. 
  // However, to get a balanced search tree, the first node should be the
  // array's median. This means sorting the array first would be simpler.

  sort_array(arr, len);   //Sort the input array
  
  // Creating a copy array but without any duplicates
  int len_ = 1;
  int arr_[len];
  arr_[0] = arr[0];
  for (int i = 1; i < len; i++){
    if (arr[i] != arr[i-1]){
      arr_[len_] = arr[i];
      len_ += 1;
    };
  };
  
  // Call recursive function to insert into tree
  ibst_t *t_out = insert_bst(arr_, len_, 0, len_);
  return t_out;
  
};


// Helper function to free tree
void bst_free(ibst_t *t){
  if (t == NULL){
    return;
  };
  bst_free(t->lsub);
  bst_free(t->rsub);
  free(t);
  return;
};


// Define min function for true/false purpose
#define min(a,b) (a<b?a:b)


// Helper function to check if a tree is well formed
int well_formed_max_min(ibst_t *t, int min, int max){
  // 0 represents false and 1 represents true
  if (t == NULL){
    return 1;
  };

  if (t->root >= max || t->root <= min){
    return 0;
  };
  
  if (t->lsub == NULL && t->rsub == NULL){
      return 1;
  };

  // Recursively call on the children node with updated min, max
  return min(well_formed_max_min(t->lsub, min, t->root),
	     well_formed_max_min(t->rsub, t->root, max));
};

//verify that the bst is well formed, that is, contains no numbers out of place
int well_formed(ibst_t *t){
  // 0 represents false and positive 1 represents true
  if (t == NULL){
    return 1;
  };
  
  if (t->lsub == NULL && t->rsub == NULL){
    return 1;
  };
  
  ibst_t *curr = t;
  int min_ = t->root;
  int max_ = t->root;

  // Determine the whole tree left-most and right-most node (min and max)
  while (curr->lsub != NULL){
    curr = curr->lsub;
  };
  min_ = curr->root - 1;
  curr = t;
  while (curr->rsub != NULL){
    curr = curr->rsub;
  };
  max_ = curr->root + 1;

  // Call helper function
  return well_formed_max_min(t, min_, max_);
};


// Define a struct which will be made into a stack containing trees as values
struct ilist_bst {
  ibst_t *tree;
  struct ilist_bst *next;
};
typedef struct ilist_bst ilist_bst_t;


// We implement some stack functions where each node is a tree

// Initiate empty stack
ilist_bst_t *stack_init(){
  return NULL;
};

// Push tree to stack
ilist_bst_t *stack_push(ilist_bst_t *s, ibst_t *t){
  if (t == NULL){
    return s;
  };
  ilist_bst_t *s_push = malloc(sizeof(ilist_bst_t));
  s_push->tree = t;
  s_push->next = s;
  return s_push;
};

// Parallel push function for linked list
ilist_t *list_push(ilist_t *s, int t){
  ilist_t *s_push = malloc(sizeof(ilist_t));
  s_push->first = t;
  s_push->rest = s;
  return s_push;
};

// Pop top element from stack and return the element
ibst_t *stack_pop(ilist_bst_t **s){
  if (*s == NULL){
    return NULL;
  };
  ibst_t *s_pop = malloc(sizeof(ibst_t));
  ilist_bst_t *s_free;
  s_free = *s;
  s_pop = (*s)->tree;
  (*s) = (*s)->next;
  s_free->next = NULL;
  free(s_free);
  return s_pop;
};

// Parallel pop function for linked list
int *list_pop(ilist_t **s){
  if (*s == NULL){
    return NULL;
  };
  int *s_pop = malloc(sizeof(int));
  ilist_t *s_free;
  s_free = *s;
  *s_pop = (*s)->first;
  (*s) = (*s)->rest;
  s_free->rest = NULL;
  free(s_free);
  return s_pop;
};

// Free the entire stack
void stack_free(ilist_bst_t *s){
  if (s == NULL){
    return;
  };
  stack_free(s->next); // This don't free the trees
  free(s);
  return;
};

// Free the entire list
void list_free(ilist_t *s){
  if (s == NULL){
    return;
  };
  list_free(s->rest); 
  free(s);
  return;
};

// Print the entire stack (only used for debugginh)
void stack_print(ilist_bst_t *s){
  if (s == NULL){
    return;
  };
  fprintf(stdout, "%d \n", s->tree->root);
  stack_print(s->next);
  return;
};

// Print the entire linked list
void list_print(ilist_t *l){
  if (l == NULL){
    return;
  };
  fprintf(stdout, "%d \n", l->first);
  list_print(l->rest);
  return;
};


// Helper function to calculate the sum of the stack
int stack_sum(ilist_bst_t *s){
  if (s == NULL){
    return 0;
  };
  int sum = 0;
  ilist_bst_t *curr = s;
  while (curr != NULL){
    sum += curr->tree->root;
    curr = curr->next;
  };
  return sum;
};

// Helper function to traverse through tree in inorder path
// Store the tree into a stack in inorder fashion
ilist_bst_t *inorder_stack(ibst_t *t){

  ilist_bst_t *s = stack_init();      // Stack to traverse
  ilist_bst_t *s_out = stack_init();  // Stack to output
  ibst_t *curr = t;                   // Traverse pointer
   
  while (curr != NULL || s != NULL){
    if (curr != NULL){
      s = stack_push(s, curr);
      curr = curr->lsub;              // Go to left node
    } else {
      curr = stack_pop(&s);
      if (curr != NULL){
	s_out = stack_push(s_out, curr);   // Push popped element into output
	curr = curr->rsub;            // Go to right node
      };
    };
  };
  return s_out;
};

// compute the sum of the bst *without recursion*
int sum(ibst_t *t){
  if (t == NULL){
    fprintf(stderr, "null tree \n");
    return 0;
  };
  ilist_bst_t *inorder_ = inorder_stack(t);   // Store tree in a stack
  int sum = stack_sum(inorder_);              // Calculate its sum
  stack_free(inorder_);
  return sum;
};


// return the path to the sought number, root first
// if the sought number is absent, return NULL
ilist_t *path_to(int sought, ibst_t *t){
  if (t == NULL){
    return NULL;
  };
  ilist_t *link = malloc(sizeof(ilist_t));
  link->first = t->root;
  
  // If number is found just return current tree address
  if (t->root == sought){
    link->rest = NULL;
    return link;
  }
  // Recursively call function on children node and link to current list
  if (sought < t->root){
    link->rest = path_to(sought, t->lsub);
  } else if (sought > t->root){
    link->rest = path_to(sought, t->rsub);
  };
  // If nothing is found, set all the list to NULL
  if (link->rest == NULL){
    free(link);
    return NULL;
  };
  return link;
};


// Recursive function to help both preorder and postorder traversal
void preorder_helper(ibst_t *t, ilist_t **l_out, int pre_post){
  // pre_post = 0 means preorder, pre_post = 1 means postorder
  if (t == NULL){
    return;
  };

  if (pre_post == 0){     // Preorder path only
    *l_out = list_push(*l_out, t->root);
  };
  preorder_helper(t->lsub, l_out, pre_post);
  preorder_helper(t->rsub, l_out, pre_post);
  if (pre_post == 1){     // Postorder path only
    *l_out = list_push(*l_out, t->root);
  };
  return;
};

// return the preorder traversal of the tree
ilist_t *preorder(ibst_t *t){
  if (t == NULL){
    return NULL;
  };
  ilist_t *l_out = NULL;
  preorder_helper(t, &l_out, 0);  // Call recursvie function

  // Reverse the list for right result
  ilist_t *l_final = NULL;
  int *pop = 0;
  while (l_out != NULL){
    pop = list_pop(&l_out);
    l_final = list_push(l_final, *pop);
    free(pop);
  };
  return l_final;
};


// return the inorder traversal of the tree
ilist_t *inorder(ibst_t *t){
  if (t == NULL){
    return NULL;
  };

  // We use the inorder stack function earlier to help us
  ilist_bst_t *l_out = inorder_stack(t);

  // Reverse the list for right result
  ilist_t *l_final = NULL;
  int pop = 0;
  while (l_out != NULL){
    pop = stack_pop(&l_out)->root;
    l_final = list_push(l_final, pop);
  };
  return l_final;
};


// return the postorder traversal of the tree
ilist_t *postorder(ibst_t *t){
  if (t == NULL){
    return NULL;
  };
  ilist_t *l_out = NULL;
  preorder_helper(t, &l_out, 1);   // Call recursive helper function

  // Reverse the list for right result
  ilist_t *l_final = NULL;
  int *pop = 0;
  while (l_out != NULL){
    pop = list_pop(&l_out);
    l_final = list_push(l_final, *pop);
    free(pop);
  };
  return l_final;
};


// Recursive function to help with level order
int levelorder_helper(ibst_t *t, ilist_t **l_out, int level){
  // Return 0 if at least 1 node is found, otherwise return 1
  if (t == NULL){
    return 1;
  };
  
  if (level == 1){   // Push current node to linked list
    *l_out = list_push(*l_out, t->root);
    return 0;
  };

  // Recursively call on children until level =1
  int left = levelorder_helper(t->lsub, l_out, level - 1);
  int right = levelorder_helper(t->rsub, l_out, level - 1);
  return min(left,right);
};

// return the levelorder traversal of the tree
ilist_t *levelorder(ibst_t *t){
  if (t == NULL){
    return NULL;
  };
  
  ilist_t *l_out = NULL;
  int level = 1;
  while (levelorder_helper(t, &l_out, level) == 0){  // Call helper function
    level +=1;
  };

  // Reverse the list for right result
  ilist_t *l_final = NULL;
  int *pop = 0;
  while (l_out != NULL){
    pop = list_pop(&l_out);
    l_final = list_push(l_final, *pop);
    free(pop);
  };
  return l_final;
};


// Helper recursive function to print out string in preorder fashion
void bst_to_string(ibst_t *t, char *str){
  // I tried printing out the fancy way but that took one hour and
  // no progress so I will resort to using brackets
  if (t == NULL){
    return;
  };

  // Get the number of digits of current tree node
  int num = t->root;
  int count = 0;
  while (num / 10 != 0){
    count +=1;
    num = num /10;
  };

  // Store int value into string
  char *value = malloc(sizeof(char) * count);
  sprintf(value, "%d", t->root);
  strcat(str, value);
  
  if (t->lsub == NULL && t->rsub == NULL){
    return;
  };

  // Add brackets and value for children node
  strcat(str, " {");
  bst_to_string(t->lsub, str);
  strcat(str, "} ");

  strcat(str, " {");
  if (t->rsub != NULL){
    bst_to_string(t->rsub, str);
  };
  strcat(str, "} ");
  return;
};

// Helper function to count the number of nodes in a tree
int bst_count(ibst_t *t){
  if (t == NULL){
    return 0;
  };
  return 1 + bst_count(t->lsub) + bst_count(t->rsub);
  
};

// build a string representation of the tree
char *bst_tos(ibst_t *t){
  char *str_out = malloc(sizeof(char) * 10 * bst_count(t));
  bst_to_string(t, str_out);
  return str_out;
};





int main(){
  // Testing tree 1
  fprintf(stdout, "Begin testing \n");
  int arr1[7] = {3,5,4,0,2,6,1};
  fprintf(stdout, "Testing tree 1 with [%d,%d,%d,%d,%d,%d,%d] \n",
	  3,5,4,0,2,6,1);
  ibst_t *t1 = build_bst(arr1, 7);
  fprintf(stdout,
	  "Finished building.\n");

  fprintf(stdout, "Check if the tree is well-formed: \n");
  char *check = (well_formed(t1))? "True" : "False";
  fprintf(stdout, "%s \n", check);

  char *tree1 = bst_tos(t1);
  fprintf(stdout, "String representation of such tree is:\n %s \n", tree1);
  free(tree1);

  fprintf(stdout, "Sum of such tree: %d \n", sum(t1));

  int sought = 0;
  fprintf(stdout, "Path to integer %d such tree is:\n", sought);
  ilist_t *l1 = path_to(sought, t1);
  list_print(l1);
  list_free(l1);
  
  fprintf(stdout, "Preorder path to such tree is:\n");
  ilist_t *l_pre1 = preorder(t1);
  list_print(l_pre1);
  list_free(l_pre1);
  fprintf(stdout, "Inorder path to such tree is:\n");
  ilist_t *l_in1 = inorder(t1);
  list_print(l_in1);
  list_free(l_in1);
  fprintf(stdout, "Postorder path to such tree is:\n");
  ilist_t *l_post1 = postorder(t1);
  list_print(l_post1);
  list_free(l_post1);
  fprintf(stdout, "Levelorder path to such tree is:\n");
  ilist_t *l_level1 = levelorder(t1);
  list_print(l_level1);
  list_free(l_level1);
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");
  bst_free(t1);  
  fprintf(stdout, "\n \n");

  
  // Testing tree 2
  int arr2[7] = {3,12,4,0,6,6,28};
  fprintf(stdout, "Testing tree 2 with [%d,%d,%d,%d,%d,%d,%d] \n",
	  3,12,4,0,6,6,28);
  ibst_t *t2 = build_bst(arr2, 7);
  fprintf(stdout,"Finished building.\n");

  char *tree2 = bst_tos(t2);
  fprintf(stdout, "String representation of such tree is:\n %s \n", tree2);
  free(tree2);
  
  fprintf(stdout, "Check if the tree is well-formed: \n");
  check = (well_formed(t2) == 1)? "True" : "False";
  fprintf(stdout, "%s \n", check);

  fprintf(stdout, "Sum of such tree: %d \n", sum(t2));

  sought = 0;
  fprintf(stdout, "Path to integer %d such tree is:\n", sought);
  ilist_t *l2 = path_to(sought, t2);
  list_print(l2);

  sought = 22;
  fprintf(stdout, "Path to integer %d such tree is:\n", sought);
  l2 = path_to(sought, t2);
  list_print(l2);
  list_free(l2);
  
  fprintf(stdout, "Preorder path to such tree is:\n");
  ilist_t *l_pre = preorder(t2);
  list_print(l_pre);
  list_free(l_pre);
  fprintf(stdout, "Inorder path to such tree is:\n");
  ilist_t *l_in = inorder(t2);
  list_print(l_in);
  list_free(l_in);
  fprintf(stdout, "Postorder path to such tree is:\n");
  ilist_t *l_post = postorder(t2);
  list_print(l_post);
  list_free(l_post);
  fprintf(stdout, "Levelorder path to such tree is:\n");
  ilist_t *l_level = levelorder(t2);
  list_print(l_level);
  list_free(l_level);
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");
  bst_free(t2);  




  
  // Testing tree 3
  int arr3[9] = {3,12,4,0,6,6,28,5,1};
  fprintf(stdout, "Testing tree 3 with [%d,%d,%d,%d,%d,%d,%d,%d,%d] \n",
	  3,12,4,0,6,6,28,5,1);
  ibst_t *t3 = build_bst(arr3, 9);
  fprintf(stdout,
	  "Finished building.\n");


  char *tree3 = bst_tos(t3);
  fprintf(stdout, "String representation of such tree is:\n %s \n", tree3);
  free(tree3);

  fprintf(stdout, "Check if the tree is well-formed: \n");
  check = (well_formed(t3) == 1)? "True" : "False";
  fprintf(stdout, "%s \n", check);

  fprintf(stdout, "Sum of such tree: %d \n", sum(t3));

  sought = 6;
  fprintf(stdout, "Path to integer %d such tree is:\n", sought);
  ilist_t *l3 = path_to(sought, t3);
  list_print(l3);
  list_free(l3);

  sought = 50;
  fprintf(stdout, "Path to integer %d such tree is:\n", sought);
  l3 = path_to(sought, t3);
  list_print(l3);
  free(l3);
  
  fprintf(stdout, "Preorder path to such tree is:\n");
  ilist_t *l_pre3 = preorder(t3);
  list_print(l_pre3);
  list_free(l_pre3);
  fprintf(stdout, "Inorder path to such tree is:\n");
  ilist_t *l_in3 = inorder(t3);
  list_print(l_in3);
  list_free(l_in3);
  fprintf(stdout, "Postorder path to such tree is:\n");
  ilist_t *l_post3 = postorder(t3);
  list_print(l_post3);
  list_free(l_post3);
  fprintf(stdout, "Levelorder path to such tree is:\n");
  ilist_t *l_level3 = levelorder(t3);
  list_print(l_level3);
  list_free(l_level3);
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");
  bst_free(t3);  


  // Make a not well-formed tree and test it
  ibst_t t_4 = {3, NULL, NULL};
  ibst_t t_5 = {2, NULL, NULL};
  ibst_t t_3 = {3, &t_4, &t_5};
  ibst_t t_2 = {5, &t_3, NULL};

  fprintf(stdout, "Checking well_formed() with not well_formed tree \n");
  fprintf(stdout,
	  "Finished building not well-formed tree.\n");

  fprintf(stdout, "Preorder path to such tree is:\n");
  ilist_t *l_pre_2 = preorder(&t_2);
  list_print(l_pre_2);
  list_free(l_pre_2);  

  check = (well_formed(&t_2))? "True" : "False";
  fprintf(stdout, "%s \n", check);
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");



  
  // Testing tree 4
  int arr4[15] = {3,5,4,0,2,6,1,26,17,8,4,15, 100, 76,2};
  fprintf(stdout,
	  "Testing tree 4 [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n",
	  3,5,4,0,2,6,1,26,17,8,4,15,100,76,2);
  ibst_t *t4 = build_bst(arr4, 15);
  fprintf(stdout,
	  "Finished building.\n");
  char *tree4 = bst_tos(t4);
  fprintf(stdout, "String representation of such tree is:\n %s \n", tree4);
  free(tree4);

  fprintf(stdout, "Check if the tree is well-formed: \n");
  check = (well_formed(t4) == 1)? "True" : "False";
  fprintf(stdout, "%s \n", check);

  fprintf(stdout, "Sum of such tree: %d \n", sum(t4));

  sought = 6;
  fprintf(stdout, "Path to integer %d such tree is:\n", sought);
  ilist_t *l4 = path_to(sought, t4);
  list_print(l4);
  
  sought = 50;
  fprintf(stdout, "Path to integer %d such tree is:\n", sought);
  l4 = path_to(sought, t4);
  list_print(l4);
  list_free(l4);
  
  fprintf(stdout, "Preorder path to such tree is:\n");
  ilist_t *l_pre4 = preorder(t4);
  list_print(l_pre4);
  list_free(l_pre4);

  fprintf(stdout, "Inorder path to such tree is:\n");
  ilist_t *l_in4 = inorder(t4);
  list_print(l_in4);
  list_free(l_in4);
  fprintf(stdout, "Postorder path to such tree is:\n");
  ilist_t *l_post4 = postorder(t4);
  list_print(l_post4);
  list_free(l_post4);
  fprintf(stdout, "Levelorder path to such tree is:\n");
  ilist_t *l_level4 = levelorder(t4);
  list_print(l_level4);
  list_free(l_level4);
  fprintf(stdout, "\n \n");
  fprintf(stdout, "\n \n");
  bst_free(t4);  
  fprintf(stdout, "\n \n");
  

  return 0;
};

