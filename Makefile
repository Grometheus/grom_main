include ../NDK.mk

TARGET   := fb_test

# Automatically find source files
C_SRCS   := $(wildcard *.c)
CPP_SRCS := $(wildcard *.cpp)
SRCS     := $(C_SRCS) $(CPP_SRCS)

# Replace .c/.cpp extensions with .o
OBJS     := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

CFLAGS   := -I../libs/miniuitwrp/include/ -I../libs/miniuitwrp/
LDFLAGS  := -L../out/extracted_ramdisk/vendor/lib64/ \
             -L../out/extracted_ramdisk/system/lib64/ \
             -lcutils 

# Default target
all: $(TARGET)

# Link step
$(TARGET):  build/stubs.o  $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ 
	chmod +x $@

# Generic compile rules
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@


build/stubs.pre.c: libs.json
	python ../grom_maker/stubbify.py generate_prestub libs.json build/stubs.h build/stubs.pre.c 

	

build/stubs.c:  build/stubs.pre.o  $(OBJS)
	($(CXX) $(LDFLAGS) -o combined build/stubs.pre.o $(OBJS) || true) 2>&1 >/dev/null |\
		python ../grom_maker/stubbify.py generate libs.json build/stubs.h build/stubs.c $(OBJS)






# Clean target
clean:
	rm -f $(OBJS) $(TARGET)
	rm -r build/*
