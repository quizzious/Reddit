#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}   BUBBLE SORT TEST SUITE RUNNER       ${NC}"
echo -e "${BLUE}========================================${NC}"

# Check if test file exists
if [ ! -f "area51rb.c" ]; then
    echo -e "${RED}Error: area51rb.c not found!${NC}"
    echo "Please make sure the test file is in the current directory."
    exit 1
fi

echo -e "${YELLOW}Compiling test suite...${NC}"

# Compile with appropriate flags
gcc -o area51rb area51rb.c -std=c99 -Wall -Wextra

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Compilation successful!${NC}"
    echo -e "${YELLOW}Running tests...${NC}"
    echo ""
    
    # Run the tests
    ./area51rb
    
    # Clean up executable
    rm -f area51rb
    
else
    echo -e "${RED}Compilation failed!${NC}"
    echo "Please check for syntax errors in the code."
    exit 1
fi

echo ""
echo -e "${BLUE}Test suite completed.${NC}"
