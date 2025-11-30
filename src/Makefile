CC = gcc
CFLAGS = -Wall
LIBS = -lcurl -lcjson
OBJ = main.o network.o search.o stats.o download.o logs.o
TARGET = grabb
PREFIX = /usr/local

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

install: $(TARGET)
	@echo "Installing to $(PREFIX)/bin/..."
	cp $(TARGET) $(PREFIX)/bin/$(TARGET)
	chmod 755 $(PREFIX)/bin/$(TARGET)
	@echo "Installation complete."

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
	@echo "Uninstalled."
