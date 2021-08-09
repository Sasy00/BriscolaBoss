_DEPS = Card.h Deck.h GameState.h GameManager.h Networking.h
_OBJ = main.o Card.o Deck.o GameState.o GameManager.o Networking.o
TARGET = BriscolaBoss

IDIR = ./include
SDIR = ./src
ODIR = ./out

CXX = g++
CXX_FLAGS = -Wall -I$(IDIR) -g

ifeq ($(OS), Windows_NT)
	CXX_FLAGS += -lWs2_32
endif

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXX_FLAGS)

$(TARGET) : $(OBJ)
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o