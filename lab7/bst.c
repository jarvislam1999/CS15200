#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

// ****************************** build_bst ******************************
// Creates a heap-allocated new singleton node with root value n
ibst_t *new_bst_node(int n) {
  ibst_t *res = malloc(sizeof(ibst_t));
  if (!res) {
    fprintf(stderr, "malloc error in new_bst_node\n");
    exit(-1);
  }
  res->root = n;
  res->lsub = NULL;
  res->rsub = NULL;
  return res;
}

// Will insert the number n into the tree
// The output is a pointer to the same tree as the input
//      The only exception is when the input is NULL
ibst_t *bst_insert(ibst_t *tree, int n) {
  // If the tree is empty, then output a single node
  if (!tree) {
    tree = new_bst_node(n);
  }
  // Otherwise, perform an insert in the correct branch
  else if (n < tree->root) {
    tree->lsub = bst_insert(tree->lsub, n);
  }
  else if (n > tree->root) {
    tree->rsub = bst_insert(tree->rsub, n);
  }
  else {
    fprintf(stderr, "Tree cannot contain duplicates\n");
    exit(-1);
  }
  return tree;
}

// build a bst containing the numbers in array
// - the bst must not contain any duplicates
// - optional challenge: build a balanced bst (not lopsided)
ibst_t *build_bst(int arr[], int len) {
  int i;
  ibst_t *res = NULL;
  for(i = 0; i <= len; i++) {
    res = bst_insert(res, arr[i]);
  }
  return res;
}


// ****************************** well_formed ******************************
// Returns max int in tree
// Error to call with empty tree
int bst_max(ibst_t *tree) {
  if (!tree) {
    fprintf(stderr, "bst_max requires non-empty input tree\n");
    exit(-1);
  }
  if (!tree->rsub)
    return tree->root;
  else
    return bst_max(tree->rsub);
}

// Returns min int in tree
// Error to call with empty tree
int bst_min(ibst_t *tree) {
  if (!tree) {
    fprintf(stderr, "bst_min requires non-empty input tree\n");
    exit(-1);
  }
  if (!tree->lsub)
    return tree->root;
  else
    return bst_max(tree->lsub);
}

// Returns 0 when the tree is not well-formed
int well_formed(ibst_t *t) {
  if (!t)
    return 1;
  if (t->lsub && bst_max(t->lsub) > t->root)
    return 0;
  if (t->rsub && bst_min(t->rsub) < t->root)
    return 0;
  return well_formed(t->lsub) && well_formed(t->rsub);
}


// ****************************** sum ******************************
// A list of bst
// Can be used for either a stack or queue
struct tlist {
  ibst_t *first;
  struct tlist *rest;
};

typedef struct tlist tlist_t;

// Adds an item to the top of the stack
// Returns pointer to new stack
tlist_t *tlist_push(tlist_t *stack, ibst_t *tree) {
  tlist_t *new_node = malloc(sizeof(tlist_t));
  new_node->first = tree;
  new_node->rest = stack;
  return new_node;
}

// Simply returns the top tree on the stack
// Does not modify the stack
ibst_t *tlist_top(tlist_t *stack) {
  return stack->first;
}

// Removes an item from the top of the stack
// Returns pointer to new stack
tlist_t *tlist_pop(tlist_t *stack) {
  tlist_t *rest = stack->rest;
  return rest;
}

// compute the sum of the bst *without recursion*
int sum(ibst_t *t) {
  tlist_t *stack = NULL;
  int sum = 0;
  if(t)
    stack = tlist_push(stack, t);
  while (stack) {
    t = tlist_top(stack);
    sum += t->root;
    stack = tlist_pop(stack);
    if (t->lsub)
      stack = tlist_push(stack, t->lsub);
    if (t->rsub)
      stack = tlist_push(stack, t->rsub);
  }
  return sum;
}

// ****************************** path-to ******************************
// Inserts a new number in the beginning of a list
ilist_t *ilist_insert(ilist_t *list, int n) {
  ilist_t *new_node = malloc(sizeof(ilist_t));
  new_node->first = n;
  new_node->rest = list;
  return new_node;
}

// return the path to the sought number, root first
// if the sought number is absent, return NULL
ilist_t *path_to(int sought, ibst_t *t) {
  ilist_t *rest_of_path = NULL;
  if (!t) {
    return NULL;
  }
  if (sought < t->root) {
    rest_of_path = path_to(sought, t->lsub);
  }
  else if (sought > t->root) {
    rest_of_path = path_to(sought, t->rsub);
  }
  else {
    return ilist_insert(NULL, sought);
  }
  if (!rest_of_path)
    return NULL;
  return ilist_insert(rest_of_path, t->root);
}

// ****************************** preorder ******************************
// Takes as input the pointer to the LAST item in the list!
// Returns a pointer to the LAST item in the list!
ilist_t *ilist_append(ilist_t *tail, int n) {
  tail->rest = malloc(sizeof(ilist_t));
  tail->rest->first = n;
  tail->rest->rest = NULL;
  return tail->rest;
}

// Takes a pointer to the LAST item in a list and adds to that list in preorder
ilist_t *preorder_helper(ilist_t *tail, ibst_t *t) {
  if (!t)
    return tail;
  tail = ilist_append(tail, t->root);
  tail = preorder_helper(tail, t->lsub);
  tail = preorder_helper(tail, t->rsub);
  return tail;
}

// return the preorder traversal of the tree
ilist_t *preorder(ibst_t *t) {
  ilist_t dummy;
  dummy.rest = NULL;
  preorder_helper(&dummy, t);
  return dummy.rest;
}

// ****************************** inorder ******************************
// Takes a pointer to the LAST item in a list and adds in inorder
ilist_t *inorder_helper(ilist_t *tail, ibst_t *t) {
  if (!t)
    return tail;
  tail = inorder_helper(tail, t->lsub);
  tail = ilist_append(tail, t->root);
  tail = inorder_helper(tail, t->rsub);
  return tail;
}

// return the inorder traversal of the tree
ilist_t *inorder(ibst_t *t) {
  ilist_t dummy;
  dummy.rest = NULL;
  inorder_helper(&dummy, t);
  return dummy.rest;
}

// ****************************** postorder ******************************
// Takes a pointer to the LAST item in a list and adds in postorder
ilist_t *postorder_helper(ilist_t *tail, ibst_t *t) {
  if (!t)
    return tail;
  tail = postorder_helper(tail, t->lsub);
  tail = postorder_helper(tail, t->rsub);
  tail = ilist_append(tail, t->root);
  return tail;
}

// return the postorder traversal of the tree
ilist_t *postorder(ibst_t *t) {
  ilist_t dummy;
  dummy.rest = NULL;
  postorder_helper(&dummy, t);
  return dummy.rest;
}

// ****************************** levelorder ******************************
// Add an item to a queue (to the back of a list)
// Input should be a pointer to the LAST item in a list
// This is similar to ilist_append
tlist_t *tlist_enqueue(tlist_t *tail, ibst_t *tree) {
  tail->rest = malloc(sizeof(tlist_t));
  tail->rest->first = tree;
  tail->rest->rest = NULL;
  return tail->rest;
}

// return the level-order traversal of the tree
ilist_t *levelorder(ibst_t *t) {
  tlist_t *queue = NULL;
  tlist_t *queue_tail;
  ilist_t dummy, *list_tail;

  queue = tlist_push(queue, t);
  queue_tail = queue;
  dummy.rest = NULL;
  list_tail = &dummy;
  while (queue) {
    t = tlist_top(queue);
    if (t) {
      list_tail = ilist_append(list_tail, t->root);
      queue_tail = tlist_enqueue(queue_tail, t->lsub);
      queue_tail = tlist_enqueue(queue_tail, t->rsub);
    }
    queue = tlist_pop(queue);
  }
  return dummy.rest;
}

// ****************************** bst_tos ******************************
// build a string representation of the tree
char *bst_tos(ibst_t *t) {
  char *lstr, *rstr, *out;
  int size;

  if (!t)
    return "empty";
  lstr = bst_tos(t->lsub);
  rstr = bst_tos(t->rsub);

  // Decimal representation of an int is at most sizeof(int) * 3 + 1 digits
  size = strlen(lstr) + strlen(rstr) + 1;
  out = malloc(sizeof(char) * size);
  sprintf(out, "(%d %s %s)", t->root, lstr, rstr);
  return out;
}
  
// build a string representation of a list
char *ilist_tos(ilist_t *l) {
  char *rest_str, *out;
  int size;
  if (!l)
    return "empty";
  rest_str = ilist_tos(l->rest);
  size = strlen(rest_str) + 1;
  out = malloc(size);
  sprintf(out, "%d -> %s", l->first, rest_str);
  return out;
}

int main() {
  ibst_t *tree;
  ilist_t *list;
  char *str;

  // Start by fixing just test 0 and 1.  Then, once that is working, you can
  // work on fixing the other tests.  The same errors appear many times in
  // the tests, so you can copy/paste a lot of your solution for one test
  // the other ones.


  //The simplest tree is the empty tree
  printf("*************** TEST 0 ***************\n");
  tree = NULL;
  printf("tree0 is well-formed: %d\n", well_formed(tree));
  printf("tree0 sum is 0: %d\n", sum(tree));
  list = path_to(5, tree);
  str = ilist_tos(list);
  printf("path-to 5 is empty: %s\n", str);
  list = path_to(0, tree);
  str = ilist_tos(list);
  printf("path-to 0 is empty: %s\n", str);
  list = preorder(tree);
  str = ilist_tos(list);
  printf("preorder tree0 is empty: %s\n", str);
  list = inorder(tree);
  str = ilist_tos(list);
  printf("inorder tree0 is empty: %s\n", str);
  list = postorder(tree);
  str = ilist_tos(list);
  printf("postorder tree0 is empty: %s\n", str);
  list = levelorder(tree);
  str = ilist_tos(list);
  printf("levelorder tree0 is empty: %s\n", str);
  str = bst_tos(tree);
  printf("tree0 is empty tree: %s\n", str);
  
  // Testing a linear tree (all left subtrees empty) 
  printf("*************** TEST 1 ***************\n");
  int array1[] = {1,2,3,4,5};

  tree = build_bst(array1, 5);
  printf("tree1 is well-formed: %d\n", well_formed(tree));
  printf("tree1 sum is 15: %d\n", sum(tree));
  list = path_to(5, tree);
  str = ilist_tos(list);
  printf("path-to 5 is 1, 2, 3, 4, 5: %s\n", str);
  list = path_to(2, tree);
  str = ilist_tos(list);
  printf("path-to 2 is 1, 2: %s\n", str);
  list = path_to(0, tree);
  str = ilist_tos(list);
  printf("path-to 0 is empty: %s\n", str);
  list = preorder(tree);
  str = ilist_tos(list);
  printf("preorder is 1, 2, 3, 4, 5: %s\n", str);
  list = inorder(tree);
  str = ilist_tos(list);
  printf("inorder is 1, 2, 3, 4, 5: %s\n", str);
  list = postorder(tree);
  str = ilist_tos(list);
  printf("postorder is 5, 4, 3, 2, 1: %s\n", str);
  list = levelorder(tree);
  str = ilist_tos(list);
  printf("levelorder is 1, 2, 3, 4, 5: %s\n", str);
  str = bst_tos(tree);
  printf("tree: %s\n", str);
  
  // Testing a balanced tree
  printf("*************** TEST 2 ***************\n");
  int array2[] = {4, 2, 1, 3, 6, 5, 7};

  tree = build_bst(array2, 7);
  printf("tree2 is well-formed: %d\n", well_formed(tree));
  printf("tree2 sum is 28: %d\n", sum(tree));
  list = path_to(6, tree);
  str = ilist_tos(list);
  printf("path-to 6 is 4, 6: %s\n", str);
  list = path_to(3, tree);
  str = ilist_tos(list);
  printf("path-to 3 is 4, 2, 3: %s\n", str);
  list = path_to(0, tree);
  str = ilist_tos(list);
  printf("path-to 0 is empty: %s\n", str);
  list = preorder(tree);
  str = ilist_tos(list);
  printf("preorder is 4, 2, 1, 3, 6, 5, 7: %s\n", str);
  list = inorder(tree);
  str = ilist_tos(list);
  printf("inorder is 1, 2, 3, 4, 5, 6, 7: %s\n", str);
  list = postorder(tree);
  str = ilist_tos(list);
  printf("postorder is 1, 3, 2, 5, 7, 6, 4: %s\n", str);
  list = levelorder(tree);
  str = ilist_tos(list);
  printf("levelorder is 4, 2, 6, 1, 3, 5, 7: %s\n", str);
  str = bst_tos(tree);
  printf("tree: %s\n", str);
  
  // Testing an unbalanced tree with some negatives
  printf("*************** TEST 3 ***************\n");
  int array3[] = {2, -3, -1, -2, 0, 1};

  tree = build_bst(array3, 6);
  printf("tree3 is well-formed: %d\n", well_formed(tree));
  printf("tree3 sum is -3: %d\n", sum(tree));
  list = path_to(2, tree);
  str = ilist_tos(list);
  printf("path-to 2 is 2: %s\n", str);
  list = path_to(1, tree);
  str = ilist_tos(list);
  printf("path-to 1 is 2, -3, -1, 0, 1: %s\n", str);
  list = path_to(-2, tree);
  str = ilist_tos(list);
  printf("path-to -2 is 2, -3, -1, -2: %s\n", str);
  list = preorder(tree);
  str = ilist_tos(list);
  printf("preorder is 2, -3, -1, -2, 0, 1: %s\n", str);
  list = inorder(tree);
  str = ilist_tos(list);
  printf("inorder is -3, -2, -1, 0, 1, 2: %s\n", str);
  list = postorder(tree);
  str = ilist_tos(list);
  printf("postorder is -2, 1, 0, -1, -3, 2: %s\n", str);
  list = levelorder(tree);
  str = ilist_tos(list);
  printf("levelorder is 2, -3, -1, -2, 0, 1: %s\n", str);
  str = bst_tos(tree);
  printf("tree: %s\n", str);
  
  // Testing with simple ill-formed tree
  ibst_t node0, node1;
  node0.root = 0;
  node0.lsub = &node1;
  node0.rsub = NULL;
  node1.root = 3;
  node1.lsub = NULL;
  node1.rsub = NULL;

  tree = &node0;
  printf("*************** TEST 4 ***************\n");
  printf("tree4 is not well-formed: %d\n", well_formed(tree));
  printf("tree4 sum is 3: %d\n", sum(tree));
  list = path_to(0, tree);
  str = ilist_tos(list);
  printf("path-to 0 is 0: %s\n", str);
  list = path_to(3, tree);
  str = ilist_tos(list);
  printf("path-to 1 is 0, 3 (but 3 is in the wrong place,");
  printf("so it can't be found): %s\n", str);
  list = preorder(tree);
  str = ilist_tos(list);
  printf("preorder is 0, 3: %s\n", str);
  list = inorder(tree);
  str = ilist_tos(list);
  printf("inorder is 3, 0: %s\n", str);
  list = postorder(tree);
  str = ilist_tos(list);
  printf("postorder is 3, 0: %s\n", str);
  list = levelorder(tree);
  str = ilist_tos(list);
  printf("levelorder is 0, 3: %s\n", str);
  str = bst_tos(tree);
  printf("tree: %s\n", str);

  // Testing with more complicated ill-formed tree
  ibst_t node2, node3, node4;
  node2.root = 5;
  node2.lsub = &node3;
  node2.rsub = NULL;
  node3.root = 3;
  node3.lsub = NULL;
  node3.rsub = &node4;
  node4.root = 7;
  node4.lsub = NULL;
  node4.rsub = NULL;

  tree = &node2;
  printf("*************** TEST 5 ***************\n");
  printf("tree5 is not well-formed: %d\n", well_formed(tree));
  printf("tree5 sum is 15: %d\n", sum(tree));
  list = path_to(5, tree);
  str = ilist_tos(list);
  printf("path-to 5 is 5: %s\n", str);
  list = path_to(7, tree);
  str = ilist_tos(list);
  printf("path-to 7 is 5, 3, 7 (but 7 is in the wrong place,");
  printf("so it can't be found): %s\n", str);
  list = preorder(tree);
  str = ilist_tos(list);
  printf("preorder is 5, 3, 7: %s\n", str);
  list = inorder(tree);
  str = ilist_tos(list);
  printf("inorder is 3, 7, 5: %s\n", str);
  list = postorder(tree);
  str = ilist_tos(list);
  printf("postorder is 7, 3, 5: %s\n", str);
  list = levelorder(tree);
  str = ilist_tos(list);
  printf("levelorder is 5, 3, 7: %s\n", str);
  str = bst_tos(tree);
  printf("tree: %s\n", str);

  // Testing with large random tree
  // We won't know what the correct result should be for this test.
  // This is mostly for fun.
  // We'll just pring the first 50 characters of the really long strings.
  int size6 = 1000;
  int *array6 = malloc(sizeof(int) * size6);
  int i;
  for(i = 0; i < size6; i++) {
    array6[i] = rand();
  }
  tree = build_bst(array6, size6);
  printf("*************** TEST 6 ***************\n");
  printf("tree6 is well-formed: %d\n", well_formed(tree));
  printf("tree sum is unknown (and likely an overflow): %d\n", sum(tree));
  list = path_to(0, tree);
  str = ilist_tos(list);
  printf("path-to 5: %s\n", str);
  list = path_to(7, tree);
  str = ilist_tos(list);
  printf("path-to 7: %s\n", str);
  list = preorder(tree);
  str = ilist_tos(list);
  printf("preorder is: %.50s ...\n", str);
  list = inorder(tree);
  str = ilist_tos(list);
  printf("inorder is: %.50s ...\n", str);
  list = postorder(tree);
  str = ilist_tos(list);
  printf("postorder is: %.50s ...\n", str);
  list = levelorder(tree);
  str = ilist_tos(list);
  printf("levelorder is: %.50s ...\n", str);
  str = bst_tos(tree);
  printf("tree: %.50s ...\n", str);

  return 0;
}
