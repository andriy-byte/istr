#ifndef ISTR_H
#define ISTR_H

#include <map>
#include <concepts>
#include <sstream>
#include <cassert>
#include <source_location>
#include <iostream>

namespace istr {

    template<typename Type>
    concept StringTypes = std::is_same<Type, std::string>::value || std::is_same<Type, std::u8string>::value ||
                          std::is_same<Type, std::u16string>::value || std::is_same<Type, std::u32string>::value ||
                          std::is_same<Type, std::wstring>::value;

    enum class substitution_preparation_modes {
        WITH_REPLACEMENT_VALIDATION,
        WITHOUT_REPLACEMENT_VALIDATION
    };

    template<StringTypes STR>
    class string_interpolation {
    public:
        string_interpolation(const STR &pattern, substitution_preparation_modes mode) noexcept;

        explicit string_interpolation(const STR &pattern) noexcept;

        void reset() const noexcept;

        const STR &substitution() const noexcept;

        void prepare_substitution() const noexcept;

        void put_pattern_arguments(const std::map<STR, STR> &arguments) const noexcept;

        STR get_pattern() const;

        void set_pattern(const STR &pattern);

        substitution_preparation_modes get_mode() const;

        void set_mode(substitution_preparation_modes mode);


    private:
        [[maybe_unused]] void try_prepare_substitution() const noexcept(false);

        mutable bool is_already_substituted;
        STR pattern;
        mutable STR temp_substitution;
        mutable std::map<STR, STR> pattern_arguments;
        mutable substitution_preparation_modes mode;

    };


    template<StringTypes STR>
    void string_interpolation<STR>::put_pattern_arguments(const std::map<STR, STR> &arguments) const noexcept {
        pattern_arguments.insert(arguments.begin(),arguments.end());
    }

    template<StringTypes STR>
    STR string_interpolation<STR>::get_pattern() const {
        return pattern;
    }

    template<StringTypes STR>
    void string_interpolation<STR>::set_pattern(const STR &pattern) {
        this->pattern = pattern;
    }

    template<StringTypes STR>
    substitution_preparation_modes string_interpolation<STR>::get_mode() const {
        return mode;
    }

    template<StringTypes STR>
    void string_interpolation<STR>::set_mode(substitution_preparation_modes mode) {
        this->mode = mode;
    }

    template<StringTypes STR>
    string_interpolation<STR>::string_interpolation(const STR &pattern) noexcept {
        this->pattern = pattern;
        is_already_substituted = false;
    }

    template<StringTypes STR>
    string_interpolation<STR>::string_interpolation(const STR &pattern, substitution_preparation_modes mode) noexcept {
        this->pattern = pattern;
        this->mode = mode;
        is_already_substituted = false;
    }


    template<StringTypes STR>
    [[maybe_unused]] void string_interpolation<STR>::try_prepare_substitution() const noexcept(false) {
        [[maybe_unused]] std::stringstream string_stream;
        [[maybe_unused]] std::source_location current_location;
        string_stream << "\n";
        string_stream << "exception in file : " << current_location.file_name() << "\n"
                      << "inside function : " << current_location.function_name() << "\n"
                      << "at line : " << current_location.line() << "\n";
        try {
            if (pattern.empty()) {
                string_stream << "exception message : "
                              << "it is impossible to build a string template, there is no template"
                              << "\n";
                throw std::runtime_error(string_stream.str());
            }
            if (pattern_arguments.empty()) {
                string_stream << "exception message : "
                              << "has no arguments to replace in pattern , cannot do substitution string"
                              << "\n";
                throw std::runtime_error(string_stream.str());
            }
            for (const auto &[key, value]: pattern_arguments) {
                if (pattern.find(key) == STR::npos) {
                    string_stream << "exception message : "
                                  << "the string template's pattern \" " +
                                     static_cast<STR>(pattern) +
                                     " \" does not contain a argument " +
                                     static_cast<STR>(key) + "."
                                  << "\n";
                    throw std::runtime_error(string_stream.str());
                }
            }
        } catch (std::exception const &substitution_prepare_exception) {
            std::cerr << substitution_prepare_exception.what();
        } catch (...) {
            std::cerr << string_stream.str();
        }
    }

    template<StringTypes STR>
    void string_interpolation<STR>::prepare_substitution() const noexcept {
        if (mode == substitution_preparation_modes::WITH_REPLACEMENT_VALIDATION) {
            try_prepare_substitution();
        }
        temp_substitution = pattern;
        for (const auto &[replaceable, replacement]: pattern_arguments) {
            std::size_t start_position = 0;
            while ((start_position = temp_substitution.find(replaceable, start_position)) != STR::npos) {
                temp_substitution.replace(start_position, replaceable.length(), replacement);
                start_position += replacement.length();
            }
        }
        is_already_substituted = true;
    }

    template<StringTypes STR>
    const STR &string_interpolation<STR>::substitution() const noexcept {
        if (!is_already_substituted) {
            prepare_substitution();
        }
        return temp_substitution;
    }

    template<StringTypes STR>
    void string_interpolation<STR>::reset() const noexcept {
        pattern_arguments.clear();
        is_already_substituted = false;
        mode = substitution_preparation_modes::WITH_REPLACEMENT_VALIDATION;

    }

}
#endif // !ISTR_H

