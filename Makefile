_DEPS = Card.h Deck.h GameState.h GameManager.h
_OBJ = main.o Card.o Deck.o GameState.o GameManager.o
TARGET = BriscolaBoss

IDIR = ./include
SDIR = ./src
ODIR = ./out

CXX = g++
CXX_FLAGS = -Wall -I$(IDIR)

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXX_FLAGS)

$(TARGET) : $(OBJ)
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o