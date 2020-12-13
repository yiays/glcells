build/glcells: main.cpp
	gcc main.cpp -o build/glcells -fno-builtin -lftgl -lstdc++ -lglut -lGLU -lGL -I/usr/include/freetype2
clean: build
	rm -r build; mkdir build
run: build/glcells
	build/glcells