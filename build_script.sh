echo "Building project..."
mkdir -p bin
echo $ORACLE_LIBS
echo $ORACLE_INCLUDES
g++ src/*.cpp -I$ORACLE_INCLUDES -L$ORACLE_LIBS -locci -lclntsh -std=c++17 -o bin/main
echo "Main program built"
# g++ src/random_data_generator/*.cpp -o bin/random_data_generator
# echo "Generator built"
echo "Build complete"
