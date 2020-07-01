TARGETS =  $(patsubst %.cc,%,$(wildcard *.cc))
CPPFLAGS += -std=c++20 -Wall -g

program_INCLUDE_DIRS :=
program_LIBRARY_DIRS :=
program_LIBRARIES :=

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

.PHONY: all clean distclean

all: $(TARGETS)

$(TARGETS): %: %.cc
	    $(LINK.cc) -o $@ $< -lpthread 

clean:
	$(RM) $(TARGETS) *.o *.pcm math

modules:
	clang++ -std=c++20 -fmodules-ts --precompile math.cppm -o math.pcm                   
	clang++ -std=c++20 -fmodules-ts -c math.pcm -o math.o                                
	clang++ -std=c++20 -fmodules-ts -fprebuilt-module-path=. math.o t_math.cc -o math    
