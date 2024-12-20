
CC = gcc
AR = ar
CP = cp

CFLAGS = -O3 -DPB_ENABLE_MALLOC -Wall -Wextra -I.

HEADERS = protocol.pb.h model.pb.h pb_encode.h pb_decode.h pb_common.h protocol.h pb.h
OBJECTS = protocol.pb.o model.pb.o pb_encode.o pb_decode.o pb_common.o protocol.o

NANOPB_HOME = ../nanopb
NANOPB_FILES = $(notdir $(wildcard $(NANOPB_HOME)/*.[ch]))

all: $(HEADERS) protocol.a

$(NANOPB_FILES):
	$(CP) $(addprefix $(NANOPB_HOME)/,$@) .

%.pb.h %.pb.c: %.proto %.options
	python3 $(NANOPB_HOME)/generator/nanopb_generator.py $*.proto -f $*.options

protocol.a: $(OBJECTS)
	$(AR) rcs $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

nanopb:
	git clone https://github.com/nanopb/nanopb.git $(NANOPB_HOME);
 
clean:
	rm -rf protocol.a *.pb.c *.pb.h obj bin $(OBJECTS) $(NANOPB_FILES)
	
distclean: clean
	rm -rf $(NANOPB_HOME)
	
.PHONY: all cleandist clean nanopb
