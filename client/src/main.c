#include <stdio.h>
#include "../lib/dotenv.c"

int main(void)
{
    env_load(".", false);

    char *connection = getenv("SERVER_IP");
    printf(connection,"%s");
    printf("\n");

    return 0;
}
