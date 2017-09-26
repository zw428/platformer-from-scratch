FLAGS = -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

BASE_SRCS=$(wildcard *.cpp)
BASE_OBJS=$(patsubst %.cpp,build/%.o,$(BASE_SRCS))
BASE_DEPS=$(BASE_OBJS:.o=.d_src)

TEST_SRCS=$(wildcard test/*.cpp)
TEST_OBJS=$(patsubst %.cpp,build/%.o,$(TEST_SRCS))
TEST_OBJS:=$(patsubst build/test/%,build/%,$(TEST_OBJS))
TEST_DEPS=$(TEST_OBJS:.o=.d_test)

unknown: $(BASE_OBJS)
	g++ $^ $(LIBS) -o build/unknown

test: $(TEST_OBJS) $(filter-out build/main.o,$(BASE_OBJS))
	g++ $^ $(LIBS) -o build/test

build/%.d_src: %.cpp
	./get_dependencies.sh $< > build/$*.d_src

build/%.d_test: test/%.cpp
	./get_dependencies.sh $< > build/$*.d_test

include $(BASE_DEPS)
include $(TEST_DEPS)

clean:
	rm build/*
