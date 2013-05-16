#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main (char argc, char **argv)
{
    Elf64_Ehdr e;
    /* code */
    Elf64_Phdr p;
    /* stack */
    Elf64_Phdr s;

    const long page_size = sysconf (_SC_PAGESIZE);

    memset (&e, 0, sizeof (e));
    memset (&p, 0, sizeof (p));
    memset (&s, 0, sizeof (s));

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
    e.e_phnum = 2;
    e.e_entry = 0x400000;
    e.e_phoff = sizeof (e);

    /* code */
    p.p_type = PT_LOAD;
    p.p_offset = page_size;
    p.p_vaddr = 0x400000;
    p.p_filesz = page_size;
    p.p_memsz = page_size;
    p.p_flags = ( PF_X | PF_R );

    /* stack */
    s.p_type = PT_GNU_STACK;
    s.p_flags = ( PF_W | PF_R );


    assert (page_size >= (sizeof (e) + sizeof (p) + sizeof (s)));

    char code[page_size];

    FILE *f = fopen ("elf.out", "w");
    fwrite (&e, sizeof (e), 1, f);
    fwrite (&p, sizeof (p), 1, f);
    fwrite (&s, sizeof (s), 1, f);

    fseek (f, page_size, SEEK_SET);
    memset (code, 0x90, page_size);
    memcpy (code, "\x48\xb8\x9a\x02\x00\x00\x00\x00\x00\x00\x50\xb8\x3c\x00\x00\x00\x48\x31\xff\x66\xff\xc7\x66\xff\xc7\x0f\x05", 27);
    fwrite (code, page_size, 1, f);
    fclose (f);
}
