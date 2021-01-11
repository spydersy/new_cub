clear && gcc -Wall -Werror -Wextra -g *.c ./GNL/*.c ./LBFT/*.c -L.. -lmlx -L%%%%/../lib -lXext -lX11 -lm -lbsd && ./a.out map.cub
