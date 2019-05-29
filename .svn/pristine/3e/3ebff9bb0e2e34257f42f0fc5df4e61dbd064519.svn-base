#include <stdlib.h>
#include <stdio.h>

void blowpast()
{
  char *mem = malloc(sizeof(char) * 667);

    for (int i = 0; i <= 666; i++) {
        mem[i] = '#';
    }
        
    free(mem);
}



int main()
{
    blowpast();
    printf("Feelin' fine.\n");
    
    return 0;
}
