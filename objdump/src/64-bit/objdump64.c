/*
** objdump32.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:21:23 2014
** Last update Thu Mar 13 18:59:27 2014 
*/

#include "objdump.h"

static int	objdump_s64(t_filemap* filemap, Elf64_Ehdr* elf)
{
  Elf64_Shdr*	section;
  char*		string;
  int		i;

  i = 0;
  while (i < gethost16(elf->e_shnum, elf))
    {
      section = load_section_header64(filemap, elf, i);
      if (section == NULL)
	return (-1);
      string = load_section_name64(filemap, elf, gethost32(section->sh_name, elf));
      if (string == NULL)
	return (-1);
      if (gethost32(section->sh_size, elf) != 0 &&
	  gethost32(section->sh_size, elf) != SHT_NOBITS &&
	  strcmp(string, ".bss") != 0)
	{
	  printf("Contenue de la section %s:\n", string);
	  if (dump_section_content64(filemap, section, string, elf) == -1)
	    return (-1);
	}
      i++;
    }
  return (0);
}

int	objdump64(t_filemap* filemap, char* filename)
{
  Elf64_Ehdr*	elf;

  (void) filename;
  elf = load_elf_header64(filemap);
  if (elf == NULL)
    return (-1);
  if (objdump_s64(filemap, elf))
    return (-1);
  return (0);
}
