
PLUGIN_EXT	?= .so

CXX	?= g++
CC	?= gcc

CFLAGS := $(CFLAGS) 
CXXFLAGS := -I. $(CXXFLAGS)

# LDFLAGS := $(LDFLAGS) -lvamp-sdk
# PLUGIN_LDFLAGS := $(LDFLAGS) $(PLUGIN_LDFLAGS)
# TEST_LDFLAGS := $(TEST_LDFLAGS) $(LDFLAGS) -lboost_unit_test_framework

PLUGIN := yintony$(PLUGIN_EXT)

SOURCES := PYIN.cpp \
           VampYin.cpp \
           Yin.cpp \
           YinUtil.cpp \
           MonoNote.cpp \
           MonoPitch.cpp \
           MonoNoteParameters.cpp \
           SparseHMM.cpp \
           MonoNoteHMM.cpp \
           MonoPitchHMM.cpp \

PLUGIN_MAIN := libmain.cpp

TESTS := test/test-meanfilter \
         test/test-fft \
         test/test-yin \
         test/test-mononote
         
OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

PLUGIN_OBJECTS := $(OBJECTS) $(PLUGIN_MAIN:.cpp=.o)

all: $(PLUGIN) $(TESTS)
	for t in $(TESTS); do echo "Running $$t"; ./"$$t" || exit 1; done

plugin: $(PLUGIN)

$(PLUGIN): $(PLUGIN_OBJECTS)
	$(CXX) -o $@ $^ $(PLUGIN_LDFLAGS)

test/test-meanfilter: test/TestMeanFilter.o $(OBJECTS)
	$(CXX) -o $@ $^ $(TEST_LDFLAGS)

test/test-fft: test/TestFFT.o $(OBJECTS)
	$(CXX) -o $@ $^ $(TEST_LDFLAGS)
	
test/test-yin: test/TestYin.o $(OBJECTS)
	$(CXX) -o $@ $^ $(TEST_LDFLAGS)
	
test/test-mononote: test/TestMonoNote.o $(OBJECTS)
	$(CXX) -o $@ $^ $(TEST_LDFLAGS)

clean:		
		rm -f $(PLUGIN_OBJECTS) test/*.o

distclean:	clean
		rm -f $(PLUGIN) $(TESTS)

depend:
		makedepend -Y -fMakefile.inc *.cpp test/*.cpp *.h test/*.h

# DO NOT DELETE

PYIN.o: PYIN.h
VampYin.o: VampYin.h
Yin.o: Yin.h
MonoNoteParameters.o: MonoNoteParameters.h
MonoNote.o: MonoNote.h
MonoPitch.o: MonoPitch.h
MonoPitchHMM.o: MonoPitchHMM.h
SparseHMM.o: SparseHMM.h
MonoNoteHMM.o: MonoNoteHMM.h
libmain.o: PYIN.h VampYin.h
test/TestMeanFilter.o: MeanFilter.h
test/TestYin.o: Yin.h

