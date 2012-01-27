#
# Makefile for BMAT-8641
#

all: bare-metal-app

TARGET_CCPREFIX=powerpc-eabi-

AS=$(TARGET_CCPREFIX)gcc
CC=$(TARGET_CCPREFIX)gcc
LD=$(TARGET_CCPREFIX)ld
OBJCOPY=$(TARGET_CCPREFIX)objcopy
OBJDUMP=$(TARGET_CCPREFIX)objdump

LIBGCC := $(shell OS=`uname -o`; CYG=`expr $OS : "[Cc]ygwin"`; if [ $CYG != 0 ]; then $(CC) -print-libgcc-file-name | tr '/' '\' 2>/dev/null | tr -d '\r'; else $(CC) -print-libgcc-file-name; fi)
check_gcc = $(shell if $(CC) $(1) -S -o /dev/null -xc /dev/null > /dev/null 2>&1; then echo "$(1)"; else echo "$(2)"; fi)

# Use C99 standard
CFLAGS_ARCH=-std=gnu99
CFLAGS = -Wall -O2 -nostdlib -nostdinc -Dppc -fno-strict-aliasing
CFLAGS += --include conf86xx.h -Iinclude
# disable pointer signedness warnings in gcc 4.0
CFLAGS += $(call check_gcc,-Wno-pointer-sign,)
# disable stack protector in gcc 4.1
CFLAGS += $(call check_gcc,-fno-stack-protector,)
CFLAGS += $(CFLAGS_ARCH)
# always enable debugging
CFLAGS += -g3 -D_DEBUG_

ASFLAGS_ARCH=
ASFLAGS = -Wall -O2 -D__ASSEMBLY__ -fno-builtin -Dppc -gstabs -D_DEBUG_ 
ASFLAGS += -nostdlib -nostdinc --include conf86xx.h -Iinclude
ASFLAGS += $(ASFLAGS_ARCH)

# Do not align output sections to page boundaries
LDFLAGS_ARCH="-n"
LDFLAGS = $(LDFLAGS_ARCH)

.PHONY: $(clean-targets) $(config-targets)
dep.mk: $(SRCS)
# don't generate deps  when cleaning
ifeq ($(findstring $(MAKECMDGOALS), $(clean-targets) $(config-targets) ),)
	@for file in $(SRCS) ; do \
		$(CC) $(CFLAGS) -M $$file | sed -e "s/.*:/`dirname $$file`\/&/" ; \
	done > dep.mk
endif

-include dep.mk

BARE_METAL_APP_SRC=src/irqs.c src/start.S src/main.c src/stdc.c 

BARE_METAL_APP := $(patsubst %.S,%.o, $(patsubst %.c,%.o,$(BARE_METAL_APP_SRC)))

SRCS=$(BARE_METAL_APP_SRC)

.PHONY: bare-metal-app

# For PowerPC, reserve r29 for global data structure from U-Boot
CFLAGS_ARCH+=--fixed-r29

bare-metal-app.lds: src/bare-metal-app.lds.in include/conf86xx.h
	$(CC) $(ASFLAGS) -x assembler-with-cpp -E -P src/bare-metal-app.lds.in -o bare-metal-app.lds

bare-metal-app: dep.mk bare-metal-app.lds $(BARE_METAL_APP)
	$(LD) -n $(LDFLAGS_ARCH) -o bare-metal-app $(BARE_METAL_APP) -Tbare-metal-app.lds "$(LIBGCC)"
	chmod -x bare-metal-app

clean:
	$(RM) *.o src/*.o *~ bare-metal-app bare-metal-app.lds *.mk src/*.mk
