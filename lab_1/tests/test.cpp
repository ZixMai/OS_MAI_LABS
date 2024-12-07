#include <fstream>
#include <filesystem>
#include "../src/parent.h"
#include "../src/utils.h"
#include "gtest/gtest.h";

TEST(BASE_TEST, SHOULD_DONE_SUCCESFULLY) {
    const std::string file_input("test_input.txt");
    const std::string file_output("test_output.txt");

    const std::array<std::string, 1> testData {
        "test.txt\n",
    };

    const std::string test_file_name("test.txt");

    const std::array<std::string, 3> test_file {
        "6.0 3.0 2.0\n",
        "6.0 2.0 1.0\n",
        "12.0 2.0 3.0\n"
    };

    const std::vector<std::string> expected_output {
        "1",
        "3",
        "2"
    };

    {
        std::ofstream test_file_stream(test_file_name);
        for (auto & string : test_file) {
            test_file_stream << string;
        }

        std::ofstream file(file_input);

        for (auto & string : testData) {
            file << string;
        }
    }

    {
        std::ifstream file_cin(file_input);
        std::ofstream file_cout(file_output);

        parent_main(file_cin, file_cout);
    }

    std::ifstream file_cout(file_output);

    std::vector<std::string> output = read_file(file_cout);

    EXPECT_TRUE(check_equals_of_strings(output, expected_output));

    if (std::filesystem::exists(file_input)) {
        std::filesystem::remove(file_input);
    }

    if (std::filesystem::exists(test_file_name)) {
        std::filesystem::remove(test_file_name);
    }

    if (std::filesystem::exists(file_output)) {
        std::filesystem::remove(file_output);
    }
}

TEST(BASE_TEST, SHOULD_BREAK) {
    const std::string file_input("test_input.txt");
    const std::string file_output("test_output.txt");

    const std::array<std::string, 1> testData {
        "test.txt\n",
    };

    const std::string test_file_name("test.txt");

    const std::array<std::string, 3> test_file {
        "6.0 3.0 2.0\n",
        "6.0 0.0 2.0\n",
        "6.0 2.0 1.0\n"
    };

    const std::vector<std::string> expected_output {
        "1",
        "Division by zero",
    };

    {
        std::ofstream test_file_stream(test_file_name);
        for (auto & string : test_file) {
            test_file_stream << string;
        }

        std::ofstream file(file_input);

        for (auto & string : testData) {
            file << string;
        }
    }

    {
        std::ifstream file_cin(file_input);
        std::ofstream file_cout(file_output);

        parent_main(file_cin, file_cout);
    }

    std::ifstream file_cout(file_output);

    std::vector<std::string> output = read_file(file_cout);

    EXPECT_TRUE(check_equals_of_strings(output, expected_output));

    if (std::filesystem::exists(file_input)) {
        std::filesystem::remove(file_input);
    }

    if (std::filesystem::exists(test_file_name)) {
        std::filesystem::remove(test_file_name);
    }

    if (std::filesystem::exists(file_output)) {
        std::filesystem::remove(file_output);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}