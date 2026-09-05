EE_BIN = oyun.elf
EE_OBJS = main.o
EE_LIBS = -laudsrv

all: $(EE_BIN)

clean:
	rm -f *.elf *.o

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
