#!/bin/bash

# TODO: Make tests more robust
# Check if unicode/special chars used for optional text
# Check failure if file exists
# Check failure if not enough args
# Check success with large, multiline optional text
# Make combine test more robust to support testing large files

# Create random number indentifier for files
ID=$(echo $RANDOM)
CREATE_TEXT="This is test text from the create command"
CREATE_FILE=$ID-create-test.txt
COPY_FILE=$ID-copy-test.txt
COMBINE_FILE=$ID-combine-test.txt

# Test create functionality
src/cli create $CREATE_FILE "$CREATE_TEXT" > /dev/null

# Checks the file create has been made
if test -f "$CREATE_FILE"; then
    echo "Create Test 1: Pass"
else
    echo "Create Test 1: Fail - File expected was not created"
    exit 1;
fi

# Checks create file contains the expected string
if grep -q "$CREATE_TEXT" "$CREATE_FILE"; then
    echo "Create Test 2: Pass"
else
    echo "Create Test 2: Fail - Expected string not in file"
    exit 1;
fi

# Test copy functionality
src/cli copy $CREATE_FILE $COPY_FILE > /dev/null

# Checks the copy file has been made
if test -f "$COPY_FILE"; then
    echo "Copy Test 1: Pass"
else
    echo "Copy Test 1: Fail - File expected was not created"
    exit 1;
fi

# Checks copy file contains the expected string
if grep -q "$CREATE_TEXT" "$COPY_FILE"; then
    echo "Copy Test 2: Pass"
else
    echo "Copy Test 2: Fail - Expected string not in file"
    exit 1;
fi

# Test combine functionality
src/cli combine $CREATE_FILE $COPY_FILE $COMBINE_FILE > /dev/null

# Checks the combine file has been made
if test -f "$COMBINE_FILE"; then
    echo "Combine Test 1: Pass"
else
    echo "Combine Test 1: Fail - File expected was not created"
    exit 1;
fi

# Gets test text
line1=$(sed -n '1p' "$COMBINE_FILE")
line2=$(sed -n '2p' "$COMBINE_FILE")

# Checks combine file contains the first expected string
if [ "$line1" = "$CREATE_TEXT" ]; then
    echo "Combine Test 2: Pass"
else
    echo "Combine Test 2: Fail - Expected string not in file"
    exit 1;
fi

# Checks combine file contains the second expected string
if [ "$line2" = "$CREATE_TEXT" ]; then
    echo "Combine Test 3: Pass"
else
    echo "Combine Test 3: Fail - Expected string not in file"
    exit 1;
fi

# Test remove functionality on create file
src/cli remove $CREATE_FILE > /dev/null

# Checks the create file has been deleted
if test -f "$CREATE_FILE"; then
    echo "Remove Test 1: Fail - File expected was not deleted"
    exit 1;
else
    echo "Remove Test 1: Pass"
fi

# Test remove functionality on copy file
src/cli remove $COPY_FILE > /dev/null

# Checks the copy file has been deleted
if test -f "$COPY_FILE"; then
    echo "Remove Test 2: Fail - File expected was not deleted"
    exit 1;
else
    echo "Remove Test 2: Pass"
fi

# Test remove functionality on combine file
src/cli remove $COMBINE_FILE > /dev/null

# Checks the combine file has been made deleted
if test -f "$COMBINE_FILE"; then
    echo "Remove Test 3: Fail - File expected was not deleted"
    exit 1;
else
    echo "Remove Test 3: Pass"
fi