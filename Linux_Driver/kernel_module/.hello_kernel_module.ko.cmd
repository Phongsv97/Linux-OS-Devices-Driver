cmd_/home/slayder/Desktop/Linux_Embedded_Trainnign/kernel_module/hello_kernel_module.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds  --build-id  -o /home/slayder/Desktop/Linux_Embedded_Trainnign/kernel_module/hello_kernel_module.ko /home/slayder/Desktop/Linux_Embedded_Trainnign/kernel_module/hello_kernel_module.o /home/slayder/Desktop/Linux_Embedded_Trainnign/kernel_module/hello_kernel_module.mod.o ;  true