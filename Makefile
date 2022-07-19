CC = gcc
BUILD_LIBS = ar rc

COMMON_FLAGS = -std=c11
DEBUG_FLAGS = -Wall -O0 -g

LIBS = -ldl
SOURCES = leto-list/leto-list.c leto-so/leto-so.c leto-utsf/leto-utsf.c

TEST_PATH = test
TEST_NAME_LETO_LIST = $(TEST_PATH)/t-leto-list
TEST_NAME_LETO_SO = $(TEST_PATH)/t-leto-so
TEST_NAME_LETO_UTSF = $(TEST_PATH)/t-leto-utsf

build: compile-libs build-libs

compile-libs:
	$(CC) $(COMMON_FLAGS) -c $(SOURCES) $(LIBS)

build-libs:
	$(BUILD_LIBS) libleto.a *.o

test: create-test-path test-leto-list test-leto-so test-leto-utsf test-run

create-test-path:
	mkdir -p $(TEST_PATH)

test-leto-list:
	$(CC) $(COMMON_FLAGS) $(DEBUG_FLAGS) -o $(TEST_NAME_LETO_LIST) leto-list/test.c leto-list/leto-list.c

test-leto-so:
	$(CC) $(COMMON_FLAGS) $(DEBUG_FLAGS) -o $(TEST_NAME_LETO_SO) leto-so/test.c leto-so/leto-so.c $(LIBS)
	$(CC) -shared -o $(TEST_PATH)/t-leto-so-lib.so -fPIC leto-so/test-library.c

test-leto-utsf:
	$(CC) $(COMMON_FLAGS) $(DEBUG_FLAGS) -o $(TEST_NAME_LETO_UTSF) leto-utsf/test.c leto-utsf/leto-utsf.c

test-run:
	$(TEST_PATH)/t-leto-list
	$(TEST_PATH)/t-leto-so
	$(TEST_PATH)/t-leto-utsf
