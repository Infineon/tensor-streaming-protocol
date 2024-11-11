CC = gcc
AR = ar
CFLAGS = -DPB_ENABLE_MALLOC -O3 -Wall -Wextra


HEADERS += devices/camera/camera.h devices/mic/mic.h devices/model/model.h devices/model/keyword_spotter.h 
CFILES = main.c devices/camera/camera.c devices/mic/mic.c devices/model/model.c devices/model/keyword_spotter.c
LIBS = ../protocol/protocol.a -lm

# To monitor malloc, realloc and free
# CFILES += memory_monito.c
# CFLAGS += -Dprotocol_realloc=__protocol_realloc -Dprotocol_free=__protocol_free

all: main

protocol:
	make -C ../protocol

../protocol/protocol.a: protocol

main: $(CFILES) $(HEADERS) $(LIBS) protocol
	gcc $(CFLAGS) $(CFILES) $(LIBS) -I../protocol -o $@

clean:
	make clean -C ../protocol
	rm -rf *.o main bin obj
	
	
.PHONY: all clean protocol
