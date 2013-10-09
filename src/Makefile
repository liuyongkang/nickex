#################################################
#
#
#
#   Makefile �����ں˵�makefile
#
#
#
#################################################

CC = gcc
LD = ld
ASM = nasm

CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS = -Tscripts/link.ld -m elf_i386
ASMFLAGS = -felf 


C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))


all: $(S_OBJECTS) $(C_OBJECTS) link


.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	nasm $(ASMFLAGS) $<

link:
	ld $(LDFLAGS) $(C_OBJECTS) $(S_OBJECTS) -o kernel


.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt/kernel
	sudo cp kernel /mnt/kernel/kernel
	sleep 1
	sudo umount /mnt/kernel

.PHONY:run
run:
	bochs -f bochsrc.txt