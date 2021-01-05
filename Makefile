LIB_DIR=lib
WEBP_DIR=$(LIB_DIR)/libwebp
CC=gcc
BUILD_DIR=build
CFLAGS+=-c -Wall -D_REENTRANT $(ADDITIONALFLAGS) $(CPPFLAGS)
LIBS=-L../$(WEBP_DIR)/build -lc -lwebp
CFILES=app.c
OFILES=app.o
INCLUDE=-I../lib/libwebp/src/

all: app

clean:
	rm -r build
	rm -f *.o app
	rm -r $(WEBP_DIR)/build

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: app

libwebp.a:
	cd $(WEBP_DIR) && mkdir -p build && cd build && cmake ../ && make

#Fixme: Create build system and use /libname/xxx.h name pattern
app.o: src/app.c
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CC) -I../include $(INCLUDE) $(CFLAGS) $(foreach file,$(CFILES),../src/$(file)) -DDEBUG -g -O0

app: libwebp.a app.o
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CC) -o app $(OFILES) $(LIBS) -I libs

test: app
	LD_LIBRARY_PATH=$(ULFIUS_DIR):${LD_LIBRARY_PATH} ./$(BUILD_DIR)/app

#Fixme: Add static librarys. Copy them into build and link them. Basiclly: simple build system
#Fixme: Fix -lgnutls
static: app.o
	cd $(BUILD_DIR) && $(CC) -o app $(OFILES) $(LIBS)