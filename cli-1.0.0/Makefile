# Compile using C++11
cli.o:
	g++ -std=c++11 -fPIC -c src/cli.cpp -o src/cli.o
# The -fPIC argument stands for Position Independent Code and is necessary when creating a shared library
# It tells the OS to use the Global Offset Table, or GOT
# When address references are relative to GOT, it allows the code to be shared across multiple processes

# Create shared library
cli.so: 
	g++ -shared -o src/cli.so src/cli.o

# Create executable
cli:
	g++ -std=c++11 -o src/cli src/cli.o

# Runs unit tests on exec
test: cli cli.o cli.so
	@./run_tests.sh

# Installs the CLI Tool
install: 
	install -D src/cli $(DESTDIR)/usr/bin/cli