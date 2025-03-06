/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:48:03 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/06 15:32:56 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

//execve(path, argv, envp) esegue un nuovo programma sostituendo 
//l'attuale processo con il comando specificato.
///bin/sh" → Usa la shell per eseguire cmd.
//"-c" → Indica alla shell di eseguire il comando cmd.
//envp per trovare il percorso dei comandi all'interno di PATH, ad esempio
void    execute_cmd(char *cmd, char **envp)
{
    char *argv[] = {"/bin/sh", "-c", cmd, NULL};
    if (execve("/bin/sh", argv, envp) == -1)
        error_exit("execve fallita");  
}