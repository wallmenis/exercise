echo "Building project..."

mkdir -p bin

g++ -std=c++17 \
-I./src \
src/main.cpp \
src/control_classes.cpp \
src/database.cpp \
-o bin/main \
-lodbc

if [ $? -ne 0 ]; then
    echo "Main build failed"
    exit 1
fi

echo "Main program built"

g++ -std=c++17 \
-I./src \
src/random_data_generator/main.cpp \
-o bin/random_data_generator

if [ $? -ne 0 ]; then
    echo "Generator build failed"
    exit 1
fi

echo "Generator built"

echo "Build complete"
