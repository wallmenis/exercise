echo "Building project..."

mkdir -p bin

g++  src/*.cpp -o bin/main -lodbc

if [ $? -ne 0 ]; then
    echo "Main build failed"
    exit 1
fi

echo "Main program built"

g++ src/random_data_generator/*.cpp -o bin/random_data_generator

if [ $? -ne 0 ]; then
    echo "Generator build failed"
    exit 1
fi

echo "Generator built"

echo "Build complete"
