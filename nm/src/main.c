/*
** main.c for  in /home/otoshigami/tmp
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Tue Mar 11 18:32:58 2014
** Last update Sat Mar 15 18:01:41 2014 
*/

#include "nm.h"

unsigned char*	load_ident(t_filemap* filemap)
{
  return (fmapaccess(filemap, 0, EI_NIDENT));
}

int	main(int ac, char** av)
{
  t_filemap		filemap;
  char*			filename;
  unsigned char*	ident;

  if (ac < 2)
    filename = "./a.out";
  else
    filename = av[1];
  if (fmap(filename, &filemap) == -1)
    return (-1);
  ident = load_ident(&filemap);
  if (ident == NULL)
    return (-1);
  if (ident[EI_CLASS] == ELFCLASS32 &&
      nm32(&filemap, filename) == -1)
    return (-1);
  else if (ident[EI_CLASS] == ELFCLASS64 &&
	   nm64(&filemap, filename) == -1)
    return (-1);
  return (0);
}
