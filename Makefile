CC             = g++
INCLUDES       = -I./include -I./external/endless_errors/include
CFLAGS         = $(INCLUDES) -c -Wall -pedantic -std=c++14 -fexec-charset=UTF-8 -finput-charset=UTF-8 -ggdb

LIB_PATHS      = -L./lib
LIBS           = 
LDFLAGS        = ${LIB_PATHS} ${LIBS}
MAKE           = mingw32-make


find = $(foreach dir,$(1),$(foreach d,$(wildcard $(dir)/*),$(call find,$(d),$(2))) $(wildcard $(dir)/$(strip $(2))))

SOURCES_LIB       = $(call find, ./src, *.cpp)
SOURCES_LIB      += $(call find, ./external/endless_errors/src, *.cpp)
SOURCES           = main.cpp
OBJECTS           = $(SOURCES:.cpp=.o)
OBJECTS_LIB       = $(SOURCES_LIB:.cpp=.o)
STATIC_TARGET     = lib/libendless_meta.a
EXECUTABLE_TARGET = endless_meta.exe


.PHONY: all check example clean


all: $(SOURCES) $(STATIC_TARGET) $(EXECUTABLE_TARGET) check
#	./$(EXECUTABLE_TARGET)


$(EXECUTABLE_TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) -lendless_meta -ggdb


$(STATIC_TARGET): $(OBJECTS_LIB)
	ar rcs $@ $(OBJECTS_LIB)


check: $(STATIC_TARGET)
	+$(MAKE) -C ./tests check


.cpp.o:
	$(CC) ${CFLAGS} $< -o $@


clean:
	$(MAKE) -C ./tests clean
	rm -f $(OBJECTS_LIB)
	rm -f $(OBJECTS)
	rm -f $(STATIC_TARGET)
	rm -f $(EXECUTABLE_TARGET)
	rm -f gmon.out

