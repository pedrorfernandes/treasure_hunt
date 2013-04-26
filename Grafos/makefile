BINDIR = .
CXXFLAGS = -Wall

DEPS= connection.h edgetype.h graphviewer.h graph.h treasureHunter.h city.h director.h graphBuilder.h interface.h road.h displayWithPages.h
OBJ = main.o connection.o graphviewer.o treasureHunter.o city.o director.o graphBuilder.o interface.o road.o

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

treasureHunt: $(OBJ)
	$(CXX) $(OBJ) -o $(BINDIR)/treasureHunt

.PHONY: clean

clean:
	rm -f *~ *.o *.a $(BINDIR)/treasureHunt
