#include <stdio.h>
#include <stdlib.h>

int main()
{
    puts("Poczatek projektu");
    // char string [] = "Hello world!";
    // puts(string);

    int tab[] = {1, 2, 3, 4};

    for(int i=0; i<3; i++)
        printf("%d ", tab[i]);

    puts("");

    return EXIT_SUCCESS;
}