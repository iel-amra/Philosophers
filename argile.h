#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"
# include <limits.h>

# define A_TO_B 1
# define B_TO_A 2
# define FIRST_P 4
# define SECOND_P 8
# define LAST 16

typedef struct s_stacks
{
	t_list	*a;
	t_list	*b;
	int	nb;
}	t_stacks;

enum {PA, RA, RB, RR, PB, RRA, RRB, RRR, SA, SB, SS, SORTED};

static const char str_move[11][4] = {"pa", "ra", "rb", "rr", "pb", "rra", "rrb", "rrr", "sa", "sb", "ss"};
