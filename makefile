CC := gcc

# ---------- Flags ----------
COMMON_CFLAGS := -Wall -Wextra -std=c99 -Isrc
APP_CFLAGS := $(COMMON_CFLAGS)
TEST_CFLAGS := $(COMMON_CFLAGS) -Itests -Iunity/src -DUNITY_OUTPUT_COLOR

LDFLAGS := -lncurses

# ---------- Sources ----------
SRC := $(wildcard src/*.c)

APP := main
APP_MAIN := src/main.c
APP_SRC := $(filter-out $(APP_MAIN), $(SRC))

UI_REAL := src/ui.c
UI_FAKE := tests/ui_fake.c

UNITY_SRC := unity/src/unity.c
TEST_APP := test_runner

# ---------- Paths ----------
TEST_DIR := tests
TEST_RUNNER := $(TEST_DIR)/test_runner.c
UNITY_AUTO := unity/auto/generate_test_runner.rb
TEST_FILES := $(wildcard $(TEST_DIR)/test_*.c)

TEST_SRC := \
	$(filter-out $(APP_MAIN) $(UI_REAL), $(SRC)) \
	$(UI_FAKE) \
	$(TEST_FILES) \
	$(UNITY_SRC)

# ---------- Test files ----------
TEST_FILES := $(wildcard $(TEST_DIR)/test_*.c)

# ---------- Targets ----------
.PHONY: all run test clean

all: $(APP)

run: $(APP)
	./$(APP)

$(APP): $(APP_MAIN) $(APP_SRC)
	$(CC) $(APP_CFLAGS) $^ -o $@ $(LDFLAGS)

# Generate test_runner.c from all test_*.c files
$(TEST_RUNNER): $(TEST_FILES)
	@echo "Generating Unity test runner..."
	ruby $(UNITY_AUTO) $(TEST_FILES) $@

$(TEST_APP): $(TEST_SRC) $(TEST_RUNNER)
	$(CC) $(TEST_CFLAGS) $^ -o $@

test: $(TEST_APP)
	./$(TEST_APP)

clean:
	rm -f $(APP) $(TEST_APP)
