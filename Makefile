# Makefile for Project Timeline
#
# Your compiler
CXX = g++

# Compilation flags
# '-g' turns debugging flags on.
# Not Using O2 flag for optimisation.
CXXFLAGS = -g -I./include -I/usr/local/include/opencv -I/usr/local/include  -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_adas -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_datasets -lopencv_face -lopencv_latentsvm -lopencv_objdetect -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_surface_matching -lopencv_text -lopencv_tracking -lopencv_xfeatures2d -lopencv_calib3d -lopencv_features2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_flann -lopencv_ximgproc -lopencv_xobjdetect -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core -lopencv_hal

# Linker flags
# When you need to add a library
LDFLAGS = -I/usr/local/include/opencv -I/usr/local/include  -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_adas -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_datasets -lopencv_face -lopencv_latentsvm -lopencv_objdetect -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_surface_matching -lopencv_text -lopencv_tracking -lopencv_xfeatures2d -lopencv_calib3d -lopencv_features2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_flann -lopencv_ximgproc -lopencv_xobjdetect -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core -lopencv_hal

# all is a target
# $(VAR) gives value of the variable.
# $@ stores the target
# $^ stores the dependency
all: bin/demo

bin/demo: obj/imquantize.o obj/stdfilt.o obj/main.o
	$(CXX) -o $@ $^ $(LDFLAGS)

bin/test: obj/test.o obj/deconvwnr.o
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/imquantize.o: src/imquantize.cpp
	mkdir -p obj bin
	$(CXX) -c $(CXXFLAGS) -o $@ $<

obj/stdfilt.o: src/stdfilt.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

obj/bwpack.o: src/bwpack.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

obj/deconvwnr.o: src/deconvwnr.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

obj/main.o: src/main.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

obj/test.o: src/test.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# .PHONY tells make that 'all' or 'clean' aren't _actually_ files, and always
# execute the compilation action when 'make all' or 'make clean' are used
.PHONY: all

# Delete all the temporary files we've created so far
clean:
	rm -rf obj/*.o
	rm -rf bin/*
