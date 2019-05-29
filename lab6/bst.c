#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";

// Create single leaf node
bst *bst_singleton(vcard *c)
{
  if (c == NULL){
    fprintf(stderr, "Vcard NULL, will proceed but behavior undefined\n");
  };
  
  bst *bst_singleton_out = malloc(sizeof(bst));
  if (bst_singleton_out != NULL){
    bst_singleton_out->vc = c;
    bst_singleton_out->lsub = NULL;
    bst_singleton_out->rsub = NULL;
  };
  return bst_singleton_out;
  
}


// Insert new tree node into tree
int bst_insert(bst *t, vcard *c)
{  
  if (c == NULL){
    fprintf(stderr, "Vcard NULL, will terminate\n");
    return 0;
  };
  if (c->cnet == NULL){
    fprintf(stderr, "Vcard have NULL CNET, will terminate\n");
    return 0;
  };
  // Guard against NULL tree, will create new leaf node
  if (t == NULL){
    fprintf(stderr, "Tree NULL, will insert first entry and terminate\n");
    t = bst_singleton(c);
    return 1;
  };

  // Assign pointer to traverse tree
  bst *curr = t;
  
  while (curr != NULL){
    //CNet and a non-empty tree vcard will never be NULL, skip checking
    if (strcmp(curr->vc->cnet, c->cnet) == 0){
      fprintf(stderr, "CNET already present in tree, will terminate\n");
      return 0;
    }
    else if (strcmp(curr->vc->cnet, c->cnet) > 0){
      if (curr->lsub != NULL){
	curr = curr->lsub;    // Continue traversing
      } else {
	curr->lsub = bst_singleton(c);
	return 1;
      }
    }
    else if (strcmp(curr->vc->cnet, c->cnet) < 0){
      if (curr->rsub != NULL){
	curr = curr->rsub;   // Continue traversing
      } else {
	curr->rsub = bst_singleton(c);
	return 1;
      }
    
    };
  };
  return 1; // Useless code but just to make sure
}


//Count number of entries
unsigned int bst_num_entries(bst *t)
{
  return t ? 1 + bst_num_entries(t->lsub) + bst_num_entries(t->rsub) : 0;
}


// Define max function
#define max(a,b) (a>b?a:b)


// Measure height of tree
unsigned int bst_height(bst *t)
{
  return t ? 1 + max(bst_height(t->lsub), bst_height(t->rsub)) : 0;
}


// Search for vcard in tree
vcard *bst_search(bst *t, char *cnet, int *n_comparisons)
{
  if (t == NULL){
    fprintf(stderr, "NULL tree was passed, will return NULL pointer\n");
    return NULL;
  };
  if (cnet == NULL){
    fprintf(stderr, "NULL cnet was passed, will return NULL pointer\n");
    return NULL;
  };
  if (n_comparisons == NULL){
    fprintf(stderr, 
	    "NULL n_comparisons was passed, will return NULL pointer\n");
    return NULL;
  };

  // Assign pointer to traverse tree
  bst *curr = t;
  while (curr != NULL){
    if (strcmp(curr->vc->cnet, cnet) == 0){
      (*n_comparisons) += 1;
      return curr->vc;
    }
    else if (strcmp(curr->vc->cnet, cnet) > 0){
      (*n_comparisons) += 1;
      curr =  curr->lsub;
    }
    else if (strcmp(curr->vc->cnet, cnet) < 0){
      (*n_comparisons) += 1;
      curr =  curr->rsub;
    };
  };
  return NULL;
}


// Find CNET starting with c
unsigned int bst_c(FILE *f, bst *t, char c)
{
  if (t == NULL){
    return 0;
  };
  if (f == NULL){
    fprintf(stderr, "NULL file was passed, will return one\n");
    return -1;
  };

  // Set up pointers to measure the 2 CNETS
  char *initc = strdup(t->vc->cnet);
  char *new_c = malloc(sizeof(char) * 2);
  initc[1] = 0;     // Get first value of CNET
  new_c[0] = c;     // Assign comparison chat
  new_c[1] = 0;

  int sum = 0;
  if (strcmp(initc, new_c) == 0){
    sum += bst_c(f, t->lsub, c);
    fprintf(f, "%s\n", t->vc->cnet);
    sum += bst_c(f, t->rsub, c);
    // Free the allocated char pointers
    initc[1] = 1;
    free(initc);
    free(new_c);
    return 1 + sum;
  }
  else if (strcmp(initc, new_c) > 0){
    // Free the allocated char pointers
    initc[1] = 1;
    free(initc);
    free(new_c);
    return bst_c(f, t->lsub, c);
  }
  else if (strcmp(initc, new_c) < 0){
    // Free the allocated char pointers
    initc[1] = 1;
    free(initc);
    free(new_c);
    return bst_c(f, t->rsub, c);
  };
  return sum;
}


// Find CNET starting with substring
unsigned int bst_substring(FILE *f, bst *t, char *sub)
{
  if (t == NULL){
    return 0;
  };
  if (f == NULL){
    fprintf(stderr, "NULL file was passed, will return one\n");
    return 1;
  };
  if (sub == NULL){
    fprintf(stderr, "string file was passed, will return one\n");
    return 1;
  };

  // Set up char pointer
  char *subc = strdup(t->vc->cnet);
  subc[strlen(sub)] = 0;   // Get first n values of CNET
  int sum = 0;
  
  if (strcmp(subc, sub) == 0){
    sum += bst_substring(f, t->lsub, sub);
    fprintf(f, "%s\n", t->vc->cnet);
    sum += bst_substring(f, t->rsub, sub);
    subc[strlen(sub)] = 1;
  
    free(subc);    // Free char pointer
    return 1 + sum;
  }
  else if (strcmp(subc, sub) > 0){
    subc[strlen(sub)] = 1;
    free(subc);    // Free char pointer
    return bst_substring(f, t->lsub, sub);
  }
  else if (strcmp(subc, sub) < 0){
    subc[strlen(sub)] = 1;
    free(subc);    // Free char pointer
    return bst_substring(f, t->rsub, sub);
  };
  return sum;
}


// Free tree
void bst_free(bst *t)
{ 
  if (t == NULL){
    return;
  };
  if (t->vc != NULL){
    vcard_free(t->vc);
  };
  bst_free(t->lsub);
  bst_free(t->rsub);
  free(t);
  return;
}
