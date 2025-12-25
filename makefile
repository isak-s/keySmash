CC := gcc

# ---------- Flags ----------
COMMON_CFLAGS := -Wall -Wextra -std=c99 -Isrc -Itests -Iunity/src
TEST_CFLAGS := $(COMMON_CFLAGS) -DUNITY_OUTPUT_COLOR
LDFLAGS := -lncurses

# ---------- Output dirs ----------
BIN_DIR := build/bin
TEST_BIN_DIR := build/tests

# ---------- App ----------
SRC := $(wildcard src/*.c)
APP := $(BIN_DIR)/main
APP_MAIN := src/main.c
APP_SRC := $(filter-out $(APP_MAIN), $(SRC))

# ---------- Unity ----------
UNITY_SRC := unity/src/unity.c

# ---------- Tests ----------
TEST_DIR := tests
TEST_FILES := $(wildcard $(TEST_DIR)/test_*.c)

# One executable per test file
TEST_BINS := $(TEST_FILES:$(TEST_DIR)/%.c=$(TEST_BIN_DIR)/%)

# Sources used by tests (shared)
TEST_SUPPORT_SRC := \
	$(filter-out $(APP_MAIN) src/ui.c, $(SRC)) \
	tests/ui_fake.c \
	$(UNITY_SRC)

# ---------- Targets ----------
.PHONY: all run test clean dirs

all: dirs $(APP)

dirs:
	mkdir -p $(BIN_DIR) $(TEST_BIN_DIR)

run: $(APP)
	./$(APP)

# ---------- App ----------
$(APP): $(APP_MAIN) $(APP_SRC)
	$(CC) $(COMMON_CFLAGS) $^ -o $@ $(LDFLAGS)

# ---------- Build each test ----------
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(TEST_SUPPORT_SRC)
	@echo "Building $@"
	$(CC) $(TEST_CFLAGS) $^ -o $@ $(LDFLAGS)

# ---------- Run all tests ----------
test: dirs $(TEST_BINS)
	@set -e; \
	for t in $(TEST_BINS); do \
		echo "Running $$t"; \
		./$$t; \
	done

clean:
	rm -rf build
