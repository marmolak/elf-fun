#include <elf.h>
#include <stdio.h>
#include <string.h>

int main (char argc, char **argv)
{
    Elf64_Ehdr e;
    Elf64_Phdr p;

    memset (&e, 0, sizeof (e));
    memset (&p, 0, sizeof (p));

    e.e_ident [EI_MAG0] = ELFMAG0;
    e.e_ident [EI_MAG1] = ELFMAG1;
    e.e_ident [EI_MAG2] = ELFMAG2;
    e.e_ident [EI_MAG3] = ELFMAG3;
    e.e_ident [EI_CLASS] = ELFCLASS64;
    e.e_ident [EI_DATA] = ELFDATA2LSB;
    e.e_ident [EI_VERSION] = EV_CURRENT;
    e.e_ident [EI_OSABI] = ELFOSABI_LINUX;
    e.e_ident [EI_NIDENT] = EI_NIDENT;

    e.e_type = ET_EXEC;
    e.e_machine = EM_X86_64;
    e.e_version = EV_CURRENT;
    e.e_ehsize = sizeof (e);
    e.e_phentsize = sizeof (p);
    e.e_phnum = 1;
    e.e_entry = 0x400000;
    e.e_phoff = sizeof (e);

    p.p_type = PT_LOAD;
    p.p_offset = 4096;
    p.p_vaddr = 0x400000;
    p.p_filesz = 4096;
    p.p_memsz = 4096;
    p.p_flags = ( PF_X | PF_R );


    char code[4096];

    FILE *f = fopen ("elf.out", "w");
    fwrite (&e, sizeof (e), 1, f);
    fwrite (&p, sizeof (p), 1, f);
    fseek (f, 4096, SEEK_SET);
    memset (code, 0x90, 4096);
    memcpy (code, "\xb8\x3c\x00\x00\x00\x48\x31\xff\x66\xff\xc7\x66\xff\xc7\x0f\x05", 16);
    fwrite (code, 4096, 1, f);
    fclose (f);
}
