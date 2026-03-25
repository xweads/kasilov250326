CXXFLAGS+= -Wall -Wextra -Weffc++ -std=c++14

UNIT_TESTS= pe-vector-tests
OBJS = main.o

$(UNIT_TESTS): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	
	$(RM) $(UNIT_TESTS) $(OBJS) 