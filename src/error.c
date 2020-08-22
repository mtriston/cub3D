#include "../cub3D.h"

void    ft_exit(char *message, t_vars *vars)
{
    if (errno != 0)
        perror(message);
    else
        ft_putendl_fd(message, 1);
 //   mlx_destroy_image(vars->screen.mlx, vars->img.img);
 //   mlx_destroy_image(vars->screen.mlx, vars->texture.north.img);
 //   mlx_destroy_image(vars->screen.mlx, vars->texture.south.img);
 //   mlx_destroy_image(vars->screen.mlx, vars->texture.west.img);
 //   mlx_destroy_image(vars->screen.mlx, vars->texture.east.img);
 //   mlx_destroy_image(vars->screen.mlx, vars->texture.sprite.img);
 //   mlx_destroy_window(vars->screen.mlx, vars->screen.win);
    free(vars->screen.mlx);
    free_gc(NULL);
    exit(errno);
}