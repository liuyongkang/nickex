#################################################
#
#
#
#   Makefile 整个内核的makefile
#
#
#
#################################################

CC = gcc
LD = ld
ASM = nasm

CFLAGS = -c -ggdb -Wall -m32 -gstabs+ -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Iinclude
LDFLAGS = -Tscripts/link.ld -m elf_i386
ASMFLAGS = -felf -g


C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))


all: $(S_OBJECTS) $(C_OBJECTS) link update_image


.c.o:
	@echo Compiling $<...
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	@echo Compiling $<...
	$(ASM) $(ASMFLAGS) $<

link:
	@echo Linking $<...
	$(LD) $(LDFLAGS) $(S_OBJECTS) $(C_OBJECTS) -o kernel


.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt/kernel
	sudo cp kernel /mnt/kernel/kernel
	sleep 1
	sudo umount /mnt/kernel

.PHONY:run-gdb
run-gdb:
	bochs-gdb -f bochsrc-gdb.txt

.PHONY:run-debug
run-debug:
	bochs-debug -f bochsrc-debug.txt

.PHONY:qemu
qemu:
	qemu -fda floppy.img -boot a

.PHONY:debug
debug:
	qemu -S -s -fda floppy.img -boot a &
	sleep 1
	cgdb -x gdbinit

