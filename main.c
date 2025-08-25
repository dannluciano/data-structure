// int main()
// {
// }
/******************************************************************************/
// int main()
// {
//     return 1;
// }
/******************************************************************************/
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Hello World");
    for (int i = 0; i < argc; i++)
    {
        puts(argv[i]);
    }
    return 0;
}