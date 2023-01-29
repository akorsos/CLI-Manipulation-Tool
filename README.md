# CLI Manipulation Tool #
A project that demonstrates knowledge of C++, Linux, and CI/CD concepts

### Kickoff CI/CD Pipeline ###
From the base directory:
```
$ debian_package.sh
```

### Steps In Pipeline ###
1. debmake runs Makefile and generates necessary Debian files
2. Makefile compiles C++ code, creates shared library, and executable
3. Makefile runs tests on executable
4. debuild creates the .deb package

### TODO ###
- Add more information to debmake files
- Account for double quotes, unicode, etc. in 'create' functionality
- Refine tests to make them more robust, check expected failures, etc.
- Make the logging prettier, trim nonessential lines, written to a file, etc.
