/*
** endian.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:29:08 2014
** Last update Wed Mar 12 23:03:13 2014 
*/

#include "objdump.h"

uint16_t	gethost16(uint16_t value, void* elf)
{
  if (((uint8_t*)elf)[EI_DATA] == ELFDATA2LSB)
    return (le16toh(value));
  else if (((uint8_t*)elf)[EI_DATA] == ELFDATA2MSB)
    return (be16toh(value));
  return (value);
}

uint32_t	gethost32(uint32_t value, void* elf)
{
  if (((uint8_t*)elf)[EI_DATA] == ELFDATA2LSB)
    return (le32toh(value));
  else if (((uint8_t*)elf)[EI_DATA] == ELFDATA2MSB)
    return (be32toh(value));
  return (value);
}

uint64_t	gethost64(uint64_t value, void* elf)
{
  if (((uint8_t*)elf)[EI_DATA] == ELFDATA2LSB)
    return (le64toh(value));
  else if (((uint8_t*)elf)[EI_DATA] == ELFDATA2MSB)
    return (be64toh(value));
  return (value);
}
