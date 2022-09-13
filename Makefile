CC = gcc
BUILD_LIBS = ar rc

COMMON_FLAGS = -std=c11
DEBUG_FLAGS = -Wall -O0 -g

LIBS = -ldl
SOURCES = leto-list/leto-list.c leto-so/leto-so.c leto-utsf/leto-utsf.c leto-error/leto-error.c leto-test/leto-test.c
LETO_LIB_NAME = libleto.a

TEST_PATH = test
TEST_NAME_LETO_LIST = $(TEST_PATH)/t-leto-list
TEST_NAME_LETO_SO = $(TEST_PATH)/t-leto-so
TEST_NAME_LETO_UTSF = $(TEST_PATH)/t-leto-utsf

build: compile-libs build-libs

compile-libs:
	$(CC) $(COMMON_FLAGS) -c $(SOURCES) $(LIBS)

build-libs:
	$(BUILD_LIBS) $(LETO_LIB_NAME) *.o

test: create-test-path test-leto-list test-leto-so test-leto-utsf test-run

create-test-path:
	mkdir -p $(TEST_PATH)

test-leto-list:
	$(CC) $(COMMON_FLAGS) $(DEBUG_FLAGS) -o $(TEST_NAME_LETO_LIST) leto-list/test.c $(LETO_LIB_NAME)

test-leto-so:
	$(CC) $(COMMON_FLAGS) $(DEBUG_FLAGS) -o $(TEST_NAME_LETO_SO) leto-so/test.c $(LETO_LIB_NAME) $(LIBS)
	$(CC) -shared -o $(TEST_PATH)/t-leto-so-lib.so -fPIC leto-so/test-library.c

test-leto-utsf:
	$(CC) $(COMMON_FLAGS) $(DEBUG_FLAGS) -o $(TEST_NAME_LETO_UTSF) leto-utsf/test.c $(LETO_LIB_NAME)

test-run:
	$(TEST_PATH)/t-leto-list
	$(TEST_PATH)/t-leto-so
	$(TEST_PATH)/t-leto-utsf

docs:
	doxygen 2> doxyerrors
