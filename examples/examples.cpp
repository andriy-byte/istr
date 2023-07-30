#include <iostream>
#include <map>
#include "istr.hpp"

void test_example_1() {
    std::cout << "--------------------------------TEST_START------------------------------" << std::endl;

    istr::string_interpolation <std::string> custom_delimiters("Hello, <%name%>!");
    custom_delimiters.put_pattern_arguments({{"<%name%>", "John"}});
    custom_delimiters.prepare_substitution();

    std::cout << "Pattern: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom_delimiters.substitution() << std::endl;

    std::cout << "--------------------------------TEST_END--------------------------------" << std::endl;
}

void test_example_2() {
    std::cout << "--------------------------------TEST_START------------------------------" << std::endl;

    istr::string_interpolation <std::string> custom_delimiters("Hello, {name}!");
    custom_delimiters.put_pattern_arguments({{"{name}", "John"}});
    custom_delimiters.prepare_substitution();

    std::cout << "Pattern: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom_delimiters.substitution() << std::endl;

    std::cout << "--------------------------------TEST_END--------------------------------" << std::endl;
}

void test_example_3() {
    std::cout << "--------------------------------TEST_START------------------------------" << std::endl;

    istr::string_interpolation <std::string> custom_delimiters("The value of !some! is {value}.");
    custom_delimiters.put_pattern_arguments({{"!some!",  "variable"},
                                             {"{value}", "42"}});
    custom_delimiters.prepare_substitution();

    std::cout << "Pattern: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom_delimiters.substitution() << std::endl;

    std::cout << "--------------------------------TEST_END--------------------------------" << std::endl;
}

void test_example_4() {
    std::cout << "--------------------------------TEST_START------------------------------" << std::endl;

    istr::string_interpolation <std::string> custom_delimiters("The value of !some! is {value}.");
    custom_delimiters.put_pattern_arguments({{"!some!",  "variable"},
                                             {"{value}", "42"}});
    custom_delimiters.prepare_substitution();

    std::cout << "Pattern: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom_delimiters.substitution() << std::endl;

    std::cout << "--------------------------------TEST_END--------------------------------" << std::endl;
}


void test_example_5() {
    std::cout << "--------------------------------TEST_START------------------------------" << std::endl;

    istr::string_interpolation <std::string> custom_delimiters("Hello, {{name}}!");
    custom_delimiters.put_pattern_arguments({{"{{name}}", "John"}});
    custom_delimiters.prepare_substitution();

    std::cout << "Pattern: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom_delimiters.substitution() << std::endl;

    // Reset the object to its initial state
    custom_delimiters.reset();

    std::cout << "Pattern after reset: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution after reset: " << custom_delimiters.substitution() << std::endl;


    std::cout << "--------------------------------TEST_END--------------------------------" << std::endl;
}

void test_example_6() {
    std::cout << "--------------------------------TEST_START------------------------------" << std::endl;

    istr::string_interpolation <std::string> custom_delimiters("The value of {{{some}}} is {value}.");
    custom_delimiters.put_pattern_arguments({{"{{{some}}}", "variable"}});
    custom_delimiters.set_mode(istr::substitution_preparation_modes::WITHOUT_REPLACEMENT_VALIDATION);

    std::cout << "Pattern: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom_delimiters.substitution() << std::endl;


    std::cout << "--------------------------------TEST_END--------------------------------" << std::endl;
}

int main() {
    test_example_1();
    test_example_2();
    test_example_3();
    test_example_4();
    test_example_5();
    test_example_6();

    return 0;
}
