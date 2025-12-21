CC := gcc

CFLAGS := -Wall -Wextra -std=c99
CFLAGS += -Isrc -Itests -Iunity/src
TEST_CFLAGS := $(CFLAGS) -DUNITY_OUTPUT_COLOR


LDFLAGS := -lncurses

# Production files
APP := main
APP_MAIN := src/main.c
APP_SRC := $(filter-out $(APP_MAIN), $(wildcard src/*.c))

# Test files
TEST_APP := test_runner
TEST_SRC := $(wildcard tests/test_*.c)
UNITY_SRC := unity/src/unity.c

# Default target
all: $(APP)

# Build production executable
$(APP): $(APP_MAIN) $(APP_SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Build test executable
$(TEST_APP): $(TEST_SRC) $(APP_SRC) $(UNITY_SRC)
	$(CC) $(TEST_CFLAGS) $^ -o $@

# Build + run tests
test: $(TEST_APP)
	./$(TEST_APP)

clean:
	rm -f $(APP) $(TEST_APP)
