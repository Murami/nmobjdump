/*
** main.c for  in /home/otoshigami/tmp
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Tue Mar 11 18:32:58 2014
** Last update Wed Mar 12 22:18:50 2014 
*/

#include <endian.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>

typedef struct	s_filemap
{
  int		size;
  void*		map;
}		t_filemap;

typedef struct	s_dump_infos
{
  unsigned char		buffer[16];
  unsigned int		offset;
  unsigned int		ndword;
  unsigned int		granularity;
}		t_dump_infos;

/*
** Gestion de l'endian
*/

uint16_t	gethost16(uint16_t value, Elf32_Ehdr* elf)
{
  if (elf->e_ident[EI_DATA] == ELFDATA2LSB)
    return (le16toh(value));
  else if (elf->e_ident[EI_DATA] == ELFDATA2MSB)
    return (be16toh(value));
}

uint32_t	gethost32(uint32_t value, Elf32_Ehdr* elf)
{
  if (elf->e_ident[EI_DATA] == ELFDATA2LSB)
    return (le32toh(value));
  else if (elf->e_ident[EI_DATA] == ELFDATA2MSB)
    return (be32toh(value));
}

/*
** Mappage
*/

size_t		filesize(int fd)
{
  off_t		offset;
  size_t	size;

  offset = lseek(fd, 0, SEEK_CUR);
  if (offset == -1)
    return (-1);
  size = lseek(fd, 0, SEEK_END);
  if (size == -1)
    return (-1);
  if (lseek(fd, offset, SEEK_SET) == -1)
    return (-1);
  return (size);
}

int		fdmap(int fd, t_filemap* filemap)
{
  filemap->size = filesize(fd);
  filemap->map = mmap(NULL, filemap->size, PROT_READ, MAP_SHARED, fd, 0);
  if (filemap->map == MAP_FAILED)
    return (-1);
  return (0);
}

int		fmap(char* filename, t_filemap* filemap)
{
  int		fd;

  fd = open(filename, O_RDONLY);
  if (fd == -1)
    return (-1);
  if (fdmap(fd, filemap) == -1)
    return (-1);
  if (close(fd) == -1)
    return (-1);
  return (0);
}

/*
** Load sécurisée des données
*/

void*		fmapaccess(t_filemap* filemap, unsigned long off, unsigned long size)
{
  if (off + size <= filemap->size && size != 0)
    return (filemap->map + off);
  else
    return (NULL);
}

Elf32_Ehdr*	load_elf_header32(t_filemap* filemap)
{
  return (fmapaccess(filemap, 0, sizeof(Elf32_Ehdr)));
}

Elf32_Phdr*	load_segment_header32(t_filemap* filemap,
				      Elf32_Ehdr* elf,
				      unsigned int nsegment)
{
  return (fmapaccess(filemap,
		     gethost32(elf->e_phoff, elf) +
		     gethost32(elf->e_phentsize, elf) * nsegment,
		     elf->e_phentsize));
}

Elf32_Shdr*	load_section_header32(t_filemap* filemap,
				      Elf32_Ehdr* elf,
				      unsigned int nsection)
{
  return (fmapaccess(filemap,
		     gethost32(elf->e_shoff, elf) +
		     gethost32(elf->e_shentsize, elf) * nsection,
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

/*
** Obj dump affichage
*/

void		print_raw_bytes32(t_dump_infos* dump_infos)
{
  int		i;
  int		cpy_ndword;

  cpy_ndword = dump_infos->ndword;
  i = 0;
  while (dump_infos->ndword < 4)
    {
      printf("         ");
      dump_infos->ndword++;
    }
  if (dump_infos->granularity != 0)
    cpy_ndword--;
  while (i < (4 * cpy_ndword + dump_infos->granularity))
    {
      if (dump_infos->buffer[i] >= ' ' && dump_infos->buffer[i] <= '~')
	printf("%c", dump_infos->buffer[i]);
      else
	printf(".");
      i++;
    }
}

void			dump_section_content_byte32(void* offset, unsigned int section_size,
						    t_dump_infos* dump_infos)
{
  unsigned char*	pvalue;
  unsigned char		granularity;

  dump_infos->granularity = 0;
  while (dump_infos->granularity != 4 && dump_infos->offset < section_size)
    {
      pvalue = offset + dump_infos->offset;
      printf("%02x", *pvalue);
      dump_infos->buffer[dump_infos->ndword * 4 + dump_infos->granularity] =
	*pvalue;
      dump_infos->offset++;
      dump_infos->granularity++;
    }
  granularity = dump_infos->granularity;
  while  (granularity != 4)
    {
      printf("  ");
      granularity++;
    }
}

void		dump_section_content_dword32(t_filemap* filemap, Elf32_Shdr* section,
					     t_dump_infos* dump_infos, Elf32_Ehdr* elf)
{
  printf(" %04x ", gethost32(section->sh_addr, elf) + dump_infos->offset);
  while (dump_infos->ndword < 4 && dump_infos->offset <
	 gethost32(section->sh_size, elf))
    {
      dump_section_content_byte32(filemap->map +
				  gethost32(section->sh_offset, elf),
				  gethost32(section->sh_size, elf), dump_infos);
      printf(" ");
      dump_infos->ndword++;
    }
  print_raw_bytes32(dump_infos);
  memset(dump_infos->buffer, 0, 16);
}

int		dump_section_content32(t_filemap* filemap, Elf32_Shdr* section,
				       char* section_name, Elf32_Ehdr* elf)
{
  t_dump_infos		dump_infos;

  memset(&dump_infos, 0, sizeof(t_dump_infos));
  if (gethost32(section->sh_size, elf) == 0 ||
      gethost32(section->sh_size, elf) == SHT_NOBITS ||
      strcmp(section_name, ".bss") == 0)
    return (0);
  if (!fmapaccess(filemap, gethost32(section->sh_offset, elf),
		  gethost32(section->sh_size, elf)))
    {
      fprintf(stderr,
	      "error: invalid section %s of size %d\n",
	      section_name,
	      gethost32(section->sh_size, elf));
      return (-1);
    }
  while (dump_infos.offset < gethost32(section->sh_size, elf))
    {
      dump_infos.ndword = 0;
      dump_section_content_dword32(filemap, section, &dump_infos, elf);
      printf("\n");
    }
  return (0);
}

int	objdump_f32(t_filemap* filemap, Elf32_Ehdr* elf)
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

int	main(int ac, char** av)
{
  t_filemap	filemap;

  if (fmap(av[1], &filemap) == -1)
    return (-1);
  if (objdump32(&filemap) == -1)
    return (-1);
}
