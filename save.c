#include "cub3d.h"

// void    put_hex(long nbr, int fd)
// {

// }

void    put_header1(int fd)
{
    ft_putstr_fd("42 4D\n", fd);
    ft_putstr_fd("00 00 00 00\n", fd);
    ft_putstr_fd("00 00\n", fd);
    ft_putstr_fd("00 00\n", fd);
    ft_putstr_fd("36 00 00 00\n", fd);
    ft_putstr_fd("\n", fd);

}

void    put_header2(int fd)
{
    ft_putstr_fd("28 00 00 00\n", fd);
    ft_putstr_fd("05 00 00 00\n", fd);
    ft_putstr_fd("05 00 00 00\n", fd);
    ft_putstr_fd("01 00\n", fd);
    ft_putstr_fd("10 00\n", fd);
    ft_putstr_fd("00 00 00 00\n", fd);
    ft_putstr_fd("00 00 00 00\n", fd);
    ft_putstr_fd("00 00 00 00\n", fd);
    ft_putstr_fd("00 00 00 00\n", fd);
    ft_putstr_fd("00 00 00 00\n", fd);
    ft_putstr_fd("00 00 00 00\n", fd);
}

void    put_image(int fd)
{
    ft_putstr_fd("FF 7F   00 00   00 00   00 00   E0 7F       00 00\n", fd);
    ft_putstr_fd("00 00   00 00   00 00   00 00   00 00       00 00\n", fd);
    ft_putstr_fd("00 00   00 00   E0 03   00 00   00 00       00 00\n", fd);
    ft_putstr_fd("00 00   00 00   00 00   00 00   00 00       00 00\n", fd);
    ft_putstr_fd("00 7C   00 00   00 00   00 00   1F 00       00 00\n", fd);
}

void    save_frame(void)
{
    int     fd;

    fd = open("image.bmp", O_CREAT | O_WRONLY);
    printf("fd00 : %d\n", fd);
    close(fd);
    // fd = open("image.bmp", O_RDWR);
    // printf("fd01 : %d\n", fd);
    put_header1(fd);
    put_header2(fd);
    put_image(fd);
}