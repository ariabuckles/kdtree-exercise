ifeq ($(strip $(MP_PART)),1)
TESTOBJS=easypng.o coloredout.o
else
#no maptiles.o because it is inlined in unit_tests.cpp for partial compilation advantages
TESTOBJS=easypng.o coloredout.o mosaiccanvas.o sourceimage.o tileimage.o
endif

include Makefile.proxy
