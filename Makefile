#!/usr/bin/make -f
# SPDX-License-Identifier: GPL-2.0
# -*- makefile -*-

BINARY_NAME = phy_patch

obj-y += rtl8261n_rtl8264b.o
obj-y += phy_patch.o

fw += rtl8261n.bin
fw += rtl8261n_lp.bin
fw += rtl8264b.bin

# standard build tools
CC ?= gcc
RM ?= rm -f
COMPILE.c = $(Q_CC)$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
LINK.o = $(Q_LD)$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET_ARCH)

# default target
all: $(BINARY_NAME) $(fw)

# standard build rules
.SUFFIXES: .o .c
.c.o:
	$(COMPILE.c) -o $@ $<

$(BINARY_NAME): $(obj-y)
	$(LINK.o) $^ $(LDLIBS) -o $@

$(fw): $(BINARY_NAME)
	./$(BINARY_NAME)

clean:
	$(RM) $(BINARY_NAME) $(obj-y) $(fw) $(DEP)

# load dependencies
DEP = $(obj-y:.o=.d) $(obj-n:.o=.d)
-include $(DEP)

.PHONY: all clean install
