CXX = g++
OBJDIR = ./obj
INCLUDE = -I./include
NAME = Mainapp
CFLAGS = -Wall -O2 -std=c++11
SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
EXTENSION = .txt
DEMODIR = ./demo
DEMO = $(wildcard $(DEMODIR)/*$(EXTENSION))
$(NAME): $(OBJECTS)
	$(CXX) -o $@ $^
$(OBJDIR)/%.o: %.cpp
	@[ -d $(OBJDIR) ]
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<
.PHONY: check
check:
	cppcheck --enable=all ./
.PHONY: clean
clean:
	rm -rf obj/*.o
.PHONY:assembly
assembly:$(SOURCES)
	$(CXX) $(INCLUDE) $(CFLAGS) -S
define F
	./$(NAME) ./$(1)

endef
.PHONY:demo
demo: $(DEMO)
	make
	$(foreach p,$^,$(call F,$(p)))