# ISTR - Simple String Interpolation Library

ISTR (Interpolation String Template Replace) is a lightweight C++ library that provides a simple string interpolation mechanism for C++ strings. It allows you to define string templates with placeholders and replace those placeholders with actual values dynamically.

## Features

- Supports different string types: `std::string`, `std::u8string`, `std::u16string`, `std::u32string`, `std::wstring`.
- Provides custom delimiters for placeholders to avoid conflicts with other template engines.
- Allows both replacement validation and non-validation modes.
- Easy-to-use interface.

## Usage

To use the ISTR library, include the `istr.hpp` header file in your C++ project. The library provides a `string_interpolation` class template that you can use for string interpolation.

### Basic Usage

```cpp
#include <iostream>
#include <map>
#include "istr.hpp"

int main() {
    istr::string_interpolation<std::string> some("Hello, <%name%>!");
    some.put_pattern_arguments({{"<%name%>", "John"}});

    std::cout << "Pattern: " << some.get_pattern() << std::endl;
    std::cout << "Substitution: " << some.substitution() << std::endl;

    istr::string_interpolation<std::string> some1("The value of !some! is {value}.");
    some1.put_pattern_arguments({{"!some!", "variable"}, {"{value}", "42"}});
    some1.prepare_substitution();

    std::cout << "Pattern: " << some1.get_pattern() << std::endl;
    std::cout << "Substitution: " << some1.substitution() << std::endl;
    
    
    istr::string_interpolation<std::string> custom("Hello, {{name}}!");
    custom.put_pattern_arguments({{"{{name}}", "John"}});

    std::cout << "Pattern: " << custom.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom.substitution() << std::endl;

    // Reset the object to its initial state
    custom_delimiters.reset();

    std::cout << "Pattern after reset: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution after reset: " << custom_delimiters.substitution() << std::endl;


    istr::string_interpolation<std::string> custom_delimiters("The value of {{{some}}} is {value}.");
    custom_delimiters.put_pattern_arguments({{"{{{some}}}", "variable"}});
    custom_delimiters.set_mode(istr::substitution_preparation_modes::WITHOUT_REPLACEMENT_VALIDATION);

    std::cout << "Pattern: " << custom_delimiters.get_pattern() << std::endl;
    std::cout << "Substitution: " << custom_delimiters.substitution() << std::endl;

    return 0;
}
