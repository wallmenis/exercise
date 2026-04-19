echo "Building project..."
mkdir -p bin
g++ src/main.cpp src/database.cpp src/control_classes.cpp -I$ORACLE_HOME/sdk/include -L$ORACLE_HOME -Wl,-rpath,$ORACLE_HOME -locci -lclntsh -o bin/main
echo "Main program built"
g++ src/random_data_generator/*.cpp -o bin/random_data_generator
echo "Generator built"
echo "Build complete"
