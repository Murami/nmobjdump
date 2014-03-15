/*
** objdump32.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:21:23 2014
** Last update Sat Mar 15 18:02:58 2014 
*/

#include "nm.h"

static int	nmloop32(t_filemap* filemap, Elf32_Ehdr* elf)
{
  Elf32_Shdr*	section;
  int		i;

  i = 0;
  while (i < gethost16(elf->e_shnum, elf))
    {
      section = load_section_header32(filemap, elf, i);
      if (section == NULL)
	return (-1);
      if (gethost32(section->sh_size, elf) != 0 &&
	  gethost32(section->sh_size, elf) != SHT_NOBITS &&
	  (gethost32(section->sh_type, elf) == SHT_SYMTAB ||
	   gethost32(section->sh_type, elf) == SHT_SYMTAB))
	{
	  if (dump_symbols32(filemap, section, elf) == -1)
	    return (-1);
	}
      i++;
    }
  return (0);
}

int	nm32(t_filemap* filemap, char* filename)
{
  Elf32_Ehdr*	elf;

  (void) filename;
  elf = load_elf_header32(filemap);
  if (elf == NULL)
    return (-1);
  if (nmloop32(filemap, elf))
    return (-1);
  return (0);
}
