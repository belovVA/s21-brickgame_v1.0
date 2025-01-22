TETRIS_DIR := brick_game/tetris
TESTS_DIR := tests
GUI_DIR := gui/cli
BUILD_DIR := build
LCOVFLAGS = --ignore-errors inconsistent --ignore-errors mismatch

ifeq ($(shell uname -s), Linux)
	TEST_FLAGS = -lcheck -lpthread -pthread -lm  -lrt -lsubunit
else
	TEST_FLAGS = -lcheck -lpthread -pthread -lm  
endif

CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11
LDFLAGS := -lncurses
MKDIR_P := mkdir -p

SOURCES := $(TETRIS_DIR)/tetris_backend.c $(GUI_DIR)/tetris_frontend.c main.c
OBJECTS := $(TETRIS_DIR)/*.o $(GUI_DIR)/*.o

.PHONY: all clean install uninstall dvi dist test gcov_report

all: clean $(BUILD_DIR)/tetris

install:
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/tetris $(LDFLAGS)  

uninstall:
	rm -rf $(BUILD_DIR) $(OBJECTS)

$(BUILD_DIR)/tetris:
	@$(MKDIR_P) $(@D)
	$(CC) $(SOURCES) -o $@ $(LDFLAGS) $(CFLAGS)
	./$(BUILD_DIR)/tetris

clean:
	rm -rf $(BUILD_DIR) $(OBJECTS) *.info gcov_report score.txt tetris.tar.gz report doxygen_report

dvi: clean
	doxygen doc/Doxyfile
	open doxygen_report/html/index.html

dist: clean
	tar -czvf tetris.tar.gz . makefile

test:
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -g $(TETRIS_DIR)/tetris_backend.c $(TESTS_DIR)/*.c -o $(BUILD_DIR)/tetris $(LDFLAGS)  $(TEST_FLAGS)
	./$(BUILD_DIR)/tetris


gcov_report: clean
	@$(MKDIR_P) $(BUILD_DIR)  
	$(CC) $(TETRIS_DIR)/tetris_backend.c $(TESTS_DIR)/*.c -o $(BUILD_DIR)/tetris $(LDFLAGS) $(CFLAGS) $(TEST_FLAGS) -fprofile-arcs -ftest-coverage 
	./$(BUILD_DIR)/tetris
	lcov -t "$(TETRIS_DIR)/tetris.c" -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcno *.gcda



style_fix:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -style=Google -i */*/*.c */*/*.h */*.c *.c
	rm .clang-format

style:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -style=Google -n */*/*.c */*/*.h */*.c *.c
	rm .clang-format

leaks: test
ifeq ($(shell uname -s), Linux)
	valgrind  --tool=memcheck --leak-check=yes  --show-leak-kinds=all ./$(BUILD_DIR)/tetris   2>&1 | awk '/ERROR SUMMARY:/ { print }'
else
	leaks --atExit -- 	./$(BUILD_DIR)/tetris
endif