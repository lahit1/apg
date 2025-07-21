#!/bin/bash

mkdir -p ./bin
mkdir -p ./build

srcs=$(find ./src ./glad/src -type f \( -name "*.c*" \))

includes=(-I./include -I./glad/include -I./stb)
compile_flags=(-O0 -g -c -pipe -march=native)
link_flags=(-lglfw -ldl)
std=-std=c++17

objs=()

# Compile source files to object files
for src in $srcs; do
    obj="./build/$(basename "$src").o"
    g++ "${compile_flags[@]}" "$src" "${includes[@]}" $std -o "$obj"
    if [ $? -ne 0 ]; then
        echo "Compilation failed on $src"
        exit 1
    fi
    objs+=("$obj")
done

# Link all object files
g++ "${objs[@]}" -o ./bin/program "${link_flags[@]}" $std

cp -r res/ bin/

if [ $? -eq 0 ]; then
    echo "Compilation success: ./bin/program"
else
    echo "Linking failed!"
    exit 1
fi
