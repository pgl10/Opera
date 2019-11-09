include Makefile.rules

SRC=	integer.cpp	\
	aout.cpp	\
	bigRa.cpp	\
	eval.cpp	\
	factor.cpp	\
	listera.cpp	\
	utils.cpp	\
	main.cpp

HEADER=$(SRC:.cpp=.hpp)

EXTRAHEADER=

TARGET=$(EXE)

OBJ=$(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ) Makefile.deps
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET) -lgmp

Makefile.deps: $(SRC) $(HEADER) #$(EXTRAHEADER)
	$(CXX) -MM $(SRC) > Makefile.deps

clean:
	rm -f *.o *.~ *.core *.Dstore *.log *.ml *.err *\#*

distclean:
	rm -f $(EXE)
	rm -f Makefile.deps Makefile.rules

-include Makefile.deps
