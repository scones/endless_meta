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
SOURCES           = 
OBJECTS           = $(SOURCES:.cpp=.o)
OBJECTS_LIB       = $(SOURCES_LIB:.cpp=.o)
STATIC_TARGET     = lib/libendless_meta.a
EXECUTABLE_TARGET =


.PHONY: all check example clean


all: $(SOURCES) $(STATIC_TARGET) check example


$(EXECUTABLE_TARGET): $(OBJECTS)


$(STATIC_TARGET): $(OBJECTS_LIB)
	ar rcs $@ $(OBJECTS_LIB)


check: $(STATIC_TARGET)
	+$(MAKE) -C ./tests check


example: $(STATIC_TARGET)
	+$(MAKE) -C ./example all


.cpp.o:
	$(CC) ${CFLAGS} $< -o $@


clean:
	$(MAKE) -C ./tests clean
	$(MAKE) -C ./example clean
	rm -f $(OBJECTS_LIB)
	rm -f $(OBJECTS)
	rm -f $(STATIC_TARGET)
	rm -f gmon.out

