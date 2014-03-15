/*
** load.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:25:37 2014
** Last update Sat Mar 15 18:02:58 2014 
*/

#include "nm.h"

Elf32_Ehdr*	load_elf_header32(t_filemap* filemap)
{
  return (fmapaccess(filemap, 0, sizeof(Elf32_Ehdr)));
}

Elf32_Phdr*	load_segment_header32(t_filemap* filemap,
				      Elf32_Ehdr* elf,
				      unsigned int nsegment)
{
  return (fmapaccess(filemap,
		     gethost32(elf->e_phoff, elf)
		     + gethost16(elf->e_phentsize, elf) * nsegment,
		     elf->e_phentsize));
}

Elf32_Shdr*	load_section_header32(t_filemap* filemap,
				      Elf32_Ehdr* elf,
				      unsigned int nsection)
{
  return (fmapaccess(filemap,
		     gethost32(elf->e_shoff, elf)
		     + gethost16(elf->e_shentsize, elf) * nsection,
		     elf->e_shentsize));
}

char*		load_section_name32(t_filemap* filemap,
				    Elf32_Ehdr* elf,
				    unsigned int indexstr)
{
  Elf32_Shdr*	names_section;
  char*		stringtable;
  char*		string;

  names_section = load_section_header32(filemap,
					elf,
					gethost16(elf->e_shstrndx, elf));
  if (names_section == NULL)
    return (NULL);
  if (indexstr >= gethost32(names_section->sh_size, elf))
    return (NULL);
  stringtable = fmapaccess(filemap,
			   gethost32(names_section->sh_offset, elf),
			   gethost32(names_section->sh_size, elf));
  if (stringtable == NULL)
    return (NULL);
  string = stringtable + indexstr;
  if (strnlen(string, gethost32(names_section->sh_size, elf) - indexstr) ==
      gethost32(names_section->sh_size, elf) - indexstr)
    return (NULL);
  return (string);
}

Elf32_Shdr*	load_section_by_name32(t_filemap* filemap, Elf32_Ehdr* elf,
				       char* name)
{
  Elf32_Shdr*	section;
  char*		string;
  int		i;

  i = 0;
  while (i < gethost16(elf->e_shnum, elf))
    {
      section = load_section_header32(filemap, elf, i);
      if (section == NULL)
	return (NULL);
      string = load_section_name32(filemap, elf,
				   gethost32(section->sh_name, elf));
      if (string == NULL)
	return (NULL);
      if (strcmp(string, name) == 0)
	return (section);
      i++;
    }
  return (NULL);
}
