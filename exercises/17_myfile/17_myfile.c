#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
    const char *type_str;
    switch (e_type) {
        case ET_NONE:
            type_str = "No file type";
            break;
        case ET_REL:
            type_str = "Relocatable file";
            break;
        case ET_EXEC:
            type_str = "Excutable file";
            break;
        case ET_DYN:
            type_str = "Shared object file";
            break;
        case ET_CORE:
            type_str = "Reserved/Processor-specific";
            break;
    }
    printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
    char filepath[2][256] = {
        "./17_myfile.o",
        "./17_myfile",
    };

    int fd;
    Elf64_Ehdr ehdr;

    for (size_t i = 0; i < 2; i++) {
        char *current_file = filepath[i];

        printf("Checking filies: %s\n", current_file);

        fd = open(current_file, 'r');
        if (fd < 0) {
            perror("Open failed");
            continue;
        }

        if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
            perror("Error reading ELF header");
            continue;
        }

        if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) == 0) {
            printf("File: %s\n", filepath[i]);
            print_elf_type(ehdr.e_type);
        } else {
            printf("%s is not a valid ELF file.\n", filepath[i]);
        }
    }

    return 0;
}
