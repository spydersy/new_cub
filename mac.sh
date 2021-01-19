clear && gcc -Wall -Werror -Wextra -I /usr/local/include *.c *.a -o cub3D -L /usr/local/lib -lmlx -framework OpenGl -framework AppKit && ./cub3D map.cub
