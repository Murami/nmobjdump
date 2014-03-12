/*
** objdump32.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:21:23 2014
** Last update Wed Mar 12 23:11:13 2014 
*/

#include "objdump.h"

static int	objdump_f32(t_filemap* filemap, Elf32_Ehdr* elf)
{
  Elf32_Shdr*	section;
  char*		string;
  int		i;

  i = 0;
  while (i < gethost16(elf->e_shnum, elf))
    {
      section = load_section_header32(filemap, elf, i);
      if (section == NULL)
	return (-1);
      string = load_section_name32(filemap, elf, gethost32(section->sh_name, elf));
      if (string == NULL)
	return (-1);
      if (gethost32(section->sh_size, elf) != 0 &&
	  gethost32(section->sh_size, elf) != SHT_NOBITS &&
	  strcmp(string, ".bss") != 0)
	{
	  printf("Contenue de la section %s:\n", string);
	  if (dump_section_content32(filemap, section, string, elf) == -1)
	    return (-1);
	}
      i++;
    }
  return (0);
}

int	objdump32(t_filemap* filemap)
{
  Elf32_Ehdr*	elf;

  elf = load_elf_header32(filemap);
  if (elf == NULL)
    return (-1);
  if (objdump_f32(filemap, elf))
    return (-1);
  return (0);
}
