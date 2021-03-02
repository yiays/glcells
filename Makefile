build/glcells: *.cpp *.h
	gcc main.cpp -o build/glcells -std=c++20 -fno-builtin -lftgl -lstdc++ -lm -lglut -lGLU -lGL -I/usr/include/freetype2
clean: build
	rm -r build; mkdir build
run: build/glcells
	build/glcells