#include "../cub3D.h"

void    ft_error(char *message)
{
    if (errno != 0)
        perror(message);
    else
        ft_putendl_fd(message, 1);
    free_gc(NULL);
    exit(errno);
}