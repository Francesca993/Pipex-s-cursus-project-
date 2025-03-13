/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:48:03 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/12 16:10:07 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
/**
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
*/

void    free_memory(char **paths)
{
    int    i;
    
    i = 0;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
}
/*
Scorro la matrice con dentro tutti i vari path per cercare il comando 
e testa in ognuno con (access(path, F_OK | X_OK) == 0)
*/

char    *construct_path(char *cmd, char **paths)
{
    int     i;
    char    *part_path;
    char    *path;

    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK | X_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    return (NULL);
}
/*
Vado a scorrere l'envp conm ft_strnstr che cerca PATH
creo una matrice con tutti vari path con split separando per i :
vado a cercare il path funzionante con construct path
libero la memoria e ritorno il path corretto
*/
char    *find_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    int     i;
    
    i = 0;
    while ((envp[i]) && (ft_strnstr(envp[i], "PATH=", 5) == NULL))
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    if(!paths)
        return (NULL);
    path = construct_path(cmd, paths);
    free_memory(paths);
    return (path);
}
/*
La funzione execute Divide il comando e i suoi argomenti con split
perché execve richiede un array di stringhe (char **argv) per 
eseguire correttamente il programma.
 usa find_path per trovare 
il comando e poi lo esegue con execve
*/
void    execute(char *argv, char **envp)
{
    char    **cmd;
    char    *path;

    cmd = ft_split(argv, ' ');
    if ((!cmd) || (!cmd[0]))
        error_exit("Comando non valido.\n");
    path = find_path(cmd[0], envp);
    if (!path)
    {
        free_memory(cmd);
        error_exit("Comando non trovato.\n");
    }
    if (execve(path, cmd, envp) == -1)
    {
        free(path);
        free_memory(cmd);
        error_exit("Execve fallita.\n");
    }
}
