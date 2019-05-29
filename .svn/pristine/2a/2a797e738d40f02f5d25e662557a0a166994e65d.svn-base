#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_vcard_todo_format = "TODO [vcard]: %s\nhalting\n";

/* vcard_new : allocate a new vcard, copy all strings, return new object
 * note: this is a "deep copy" as opposed to a "shallow copy"; the string 
 *   arguments are not to be shared by the newly allocated vcard
 */
vcard *vcard_new(char *cnet, char *email, char *fname, char *lname, char *tel)
{  
  vcard *vcard_out = malloc(sizeof(vcard));  // Allocate output variable
  if (vcard_out == NULL){
    fprintf(stderr, "Error: Malloc for vcard unsuccessful\n");
  };
  
  // Allocate cnet
  if (cnet == NULL){
    fprintf(stderr, "CNET not found, will terminate\n");
    return NULL;
  };
  vcard_out->cnet = strdup(cnet);

  // Allocate email
  if (email == NULL){
    fprintf(stderr, "Email not found, will proceed but behavior undefined\n");
  };
  vcard_out->email = strdup(email);

  // Allocate first name
  if (fname == NULL){
    fprintf(stderr, 
	    "First name not found, will proceed but fname will be NULL\n");
  };
  vcard_out->fname = strdup(fname);
  if (lname == NULL){
    fprintf(stderr, 
	    "Last name not found, will proceed but lname will be NULL\n");
  };
  vcard_out->lname = strdup(lname);
  if (tel == NULL){
    fprintf(stderr, 
	    "Telephone not found, will proceed but tel will be NULL\n");
  };
  vcard_out->tel = strdup(tel);

  return vcard_out;
}


/* vcard_free : free vcard and the strings it points to
 */
void vcard_free(vcard *c)
{  
  if (c == NULL){
    fprintf(stderr, "NULL vcard was passed, nothing to free\n");
    return;
  };
  if (c->cnet != NULL){
    free(c->cnet);
  };
  if (c->email != NULL){
    free(c->email);
  };
  if (c->fname != NULL){
    free(c->fname);
  };
  if (c->lname != NULL){
    free(c->lname);
  };
  if (c->tel != NULL){
    free(c->tel);
  };
  free(c);
  
  return;
}


// Print out vcard
void vcard_show(FILE *f, vcard *c)
{
  if (c == NULL){
    fprintf(stderr, "Need to pass a non-null vcard\n");
    return;
  };
  if (f == NULL){
    fprintf(stderr, "Need to pass a non-null output file\n");
    return;
  };
  fprintf(f, "cnet: %s\n", c->cnet);
  fprintf(f, "email: %s\n", c->email);
  fprintf(f, "fname: %s\n", c->fname);
  fprintf(f, "lname: %s\n", c->lname);
  fprintf(f, "tel: %s\n", c->tel);
  return;

}
