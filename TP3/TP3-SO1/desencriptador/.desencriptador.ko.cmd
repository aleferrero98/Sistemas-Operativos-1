cmd_/home/alejandro/Escritorio/TP3-SO1/desencriptador/desencriptador.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds  --build-id  -o /home/alejandro/Escritorio/TP3-SO1/desencriptador/desencriptador.ko /home/alejandro/Escritorio/TP3-SO1/desencriptador/desencriptador.o /home/alejandro/Escritorio/TP3-SO1/desencriptador/desencriptador.mod.o ;  true