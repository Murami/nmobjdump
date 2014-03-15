/*
** dump_section.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:23:21 2014
** Last update Sat Mar 15 18:02:58 2014 
*/

#include "nm.h"

char*		get_sym_name32(t_filemap* filemap, Elf32_Ehdr* elf,
			       unsigned int idx)
{
  Elf32_Shdr*	strtab;
  char*		stringtable;
  char*		string;

  strtab = load_section_by_name32(filemap, elf, ".strtab");
  if (strtab == NULL)
    return (NULL);
  if (idx >= gethost32(strtab->sh_size, elf))
    return (NULL);
  stringtable = fmapaccess(filemap,
			   gethost32(strtab->sh_offset, elf),
			   gethost32(strtab->sh_size, elf));
  if (stringtable == NULL)
    return (NULL);
   string = stringtable + idx;
  if (strnlen(string, gethost32(strtab->sh_size, elf) - idx) ==
      gethost32(strtab->sh_size, elf) - idx)
    return (NULL);
  return (string);
}

void		print_symbol32(Elf32_Sym* sym, char* symname, Elf32_Ehdr* elf)
{
  (void) sym;
  if (!strlen(symname))
    return;
  if (gethost32(sym->st_value, elf))
    printf("%08x  ", gethost32(sym->st_value, elf));
  else
    printf("          ");
  printf("  %s\n", symname);
}

int		dump_symbols32(t_filemap* filemap, Elf32_Shdr* section,
			       Elf32_Ehdr* elf)
{
  Elf32_Sym*	sym;
  int		nsym;
  char*		symname;

  if (!(sym = fmapaccess(filemap, gethost32(section->sh_offset, elf),
			 gethost32(section->sh_size, elf))))
    {
      fprintf(stderr,
	      "error: invalid section of size %d\n",
	      gethost32(section->sh_size, elf));
      return (-1);
    }
  nsym = 0;
  while (nsym * sizeof(Elf32_Sym) < gethost32(section->sh_size, elf))
    {
      symname = get_sym_name32(filemap, elf, sym->st_name);
      if (symname == NULL)
	return (-1);
      print_symbol32(sym, symname, elf);
      sym++;
      nsym++;
    }
  return (0);
}
