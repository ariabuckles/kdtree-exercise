##
# Makefile
#	 			
# Simple Makefile to build photomosaic program
# and tests
#
#  Authors:
#  Aria Buckles
#  Matt Sachtler
#  Scott Wegner
#
#  Developed for CS225 PhotoMosaic MP
#  Fall 2008-2011
#  
#  Updates:
#  	Spring 2009 - Matt Sachtler - removed KDElement
#   Spring 2011 - Aria Buckles - tons of changes to MP 6.1
#   Fall 2011 - Aria Buckles - MP 6.2 rewrite
##

EXENAME=photomosaic
KDTEXENAME=testkdtree
KDTMEXENAME=testmaptiles

OBJS = photomosaic.o util.o mosaiccanvas.o sourceimage.o maptiles.o easypng.o coloredout.o tileimage.o

KDTOBJS = testkdtree.o coloredout.o
KDTMOBJS = testmaptiles.o mosaiccanvas.o sourceimage.o maptiles.o easypng.o coloredout.o tileimage.o

COMPILER=g++
LINKER=g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
# -msse2 is to try to make floating point arithmetic as uniform as possible across different systems,
# so that output images can be diffed
COMPILER_OPTS=-c -g -Wfatal-errors -Werror $(WARNINGS) -msse2
PROVIDED_OPTS=-O2
STUDENT_OPTS=-O0

all : $(KDTEXENAME) $(KDTMEXENAME) $(EXENAME)
test : $(KDTMEXENAME) $(KDTMEXENAME)
check : $(KDTEXENAME) $(KDTMEXENAME)
	./$(KDTEXENAME)
	./$(KDTMEXENAME)

$(EXENAME) : $(OBJS)
	$(LINKER) $(OBJS) -lpng -o $(EXENAME)

$(KDTEXENAME) : $(KDTOBJS)
	$(LINKER) $(KDTOBJS) -o $(KDTEXENAME)

$(KDTMEXENAME) : $(KDTMOBJS)
	$(LINKER) $(KDTMOBJS) -lpng -o $(KDTMEXENAME)

photomosaic.o : util.h photomosaic.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) $(PROVIDED_OPTS) photomosaic.cpp

util.o : util.h util.cpp
	$(COMPILER) $(COMPILER_OPTS) $(PROVIDED_OPTS) util.cpp

mosaiccanvas.o : mosaiccanvas.h mosaiccanvas.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) $(PROVIDED_OPTS) mosaiccanvas.cpp

sourceimage.o : sourceimage.h sourceimage.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) $(PROVIDED_OPTS) sourceimage.cpp

tileimage.o : tileimage.h tileimage.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) $(PROVIDED_OPTS) tileimage.cpp

maptiles.o : mosaiccanvas.h sourceimage.h maptiles.h maptiles.cpp kdtree.h kdtree.cpp kdtree_extras.cpp point.h point.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) $(STUDENT_OPTS) maptiles.cpp

testmaptiles.o : testmaptiles.cpp maptiles.h easypng.h
	$(COMPILER) $(COMPILER_OPTS) $(STUDENT_OPTS) testmaptiles.cpp

testkdtree.o : testkdtree.cpp kdtree.h kdtree.cpp kdtree_extras.cpp point.h point.cpp
	$(COMPILER) $(COMPILER_OPTS) $(STUDENT_OPTS) testkdtree.cpp

easypng.o: easypng.h easypng.cpp
	$(COMPILER) $(COMPILER_OPTS) $(PROVIDED_OPTS) easypng.cpp

coloredout.o: coloredout.h coloredout.cpp
	$(COMPILER) $(COMPILER_OPTS) $(STUDENT_OPTS) coloredout.cpp

doc: $(wildcard *.cpp) $(wildcard *.h)
	-rm -rf doc
	-doxygen mp5.doxygen

clean:
	rm -f $(EXENAME) $(KDTEXENAME) $(KDTMEXENAME) *.o 2>/dev/null

