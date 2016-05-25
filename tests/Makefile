
# TESTS_DIR := .
# SRC_DIR := ../src
TESTS = $(TESTS_DIR)/*.cpp
HEADERS = $(SRC_DIR)/*.hpp

CPPFLAGS += -Isrc

.PHONY all:

clean-tests:
	rm -rf all-tests all-tests.o
	echo "Cleaned tests"

$(BUILD_DIR)/all-tests.o:  $(TESTS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TESTS) -o $@

$(BUILD_DIR)/all-tests : $(OBJECTS) $(BUILD_DIR)/all-tests.o $(BUILD_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -lpthread $^ -o $@
