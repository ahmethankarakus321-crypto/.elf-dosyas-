EE_BIN = oyun.elf
EE_OBJS = main.o
EE_CC = ee-gcc
EE_CFLAGS = -D_EE -O2 -G0 -Wall
EE_LDFLAGS = -L$(PS2DEV)/ee/ee/lib -s
EE_LIBS = -lpad -lkernel

all: $(EE_BIN)

$(EE_BIN): $(EE_OBJS)
	$(EE_CC) $(EE_CFLAGS) $(EE_LDFLAGS) -o $(EE_BIN) $(EE_OBJS) $(EE_LIBS)

%.o: %.c
	$(EE_CC) $(EE_CFLAGS) -c $< -o $@

clean:
	rm -f *.elf *.o
