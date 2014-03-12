/*
** main.c for  in /home/otoshigami/tmp
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Tue Mar 11 18:32:58 2014
** Last update Wed Mar 12 23:09:23 2014 
*/

#include "objdump.h"

int	main(int ac, char** av)
{
  t_filemap	filemap;
  char*		filename;

  if (ac < 2)
    filename = "./a.out";
  else
    filename = av[1];
  if (fmap(filename, &filemap) == -1)
    return (-1);
  if (objdump32(&filemap) == -1)
    return (-1);
  return (0);
}
