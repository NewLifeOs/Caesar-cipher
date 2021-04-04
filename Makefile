CC = gcc

TARGET = cesar crack
CFLAGS = -o

FOLD = src
PREFIX = /usr/local/bin

vpath %.c src
vpath %.h include

all: $(TARGET)

$(TARGET):
	@echo "Installing files..."
	$(CC) $(FOLD)/main.c $(CFLAGS) cesar
	$(CC) $(FOLD)/crack.c $(CFLAGS) crack
	@echo "Done."

.PHONY: all install uninstall clean

install: 
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)

clean:
	rm -rf $(TARGET) *.o
