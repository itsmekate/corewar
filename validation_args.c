#include "asm.h"

int     validation_args(t_cmnd *c, t_asm *a)
{
    int i = 0;
    int j;

    if (!c->arg.arg_arr[i].type)
        return (0);
    while (c->arg.arg_arr[i].type && i < 3)
    {
        j = 0;
        while (a->op_tab[c->command_name - 1].params[i][j] && j <= 3)
        {
            if (c->arg.arg_arr[i].type == a->op_tab[c->command_name - 1].params[i][j])
               break;
            else
            {
                j++;
                 if (!a->op_tab[c->command_name - 1].params[i][j])
                    return (0);
            }
        }
        if (!a->op_tab[c->command_name - 1].params[i][j])
            return (0);
        i++;
    }
    return (1);
}
