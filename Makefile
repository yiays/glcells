build/glcells: main.cpp
	gcc main.cpp -o build/glcells -fno-builtin -lGL -lGLU -lglut -lstdc++
clean: build
	rm -r build; mkdir build
run: build/glcells
	build/glcells