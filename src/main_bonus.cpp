#include <computor_bonus.hpp>
#include <regex>

bool is_valid_polynomial_input(const std::string& input_string) {
    size_t equals_pos = input_string.find('=');
    if (equals_pos == std::string::npos || equals_pos == input_string.length() - 1) {
        return false;
    }
    std::string after_equals = input_string.substr(equals_pos + 1);
    after_equals.erase(0, after_equals.find_first_not_of(" "));
    after_equals.erase(after_equals.find_last_not_of(" ") + 1);
    if (after_equals.empty()) {
        return false;
    }

    std::regex allowed_chars_regex("^[0-9+\\-*^=X\\s]+$");
    if (!std::regex_match(input_string, allowed_chars_regex)) {
        return false;
    }

    std::regex power_term_regex("X\\^(\\S+)");
    std::smatch match;
    std::string::const_iterator search_start(input_string.cbegin());
    while (std::regex_search(search_start, input_string.cend(), match, power_term_regex)) {
        if (match.size() > 1) {
            std::regex digit_regex("^[0-9]+$");
            if (!std::regex_match(match[1].str(), digit_regex)) {
                return false;
            }
        }
        search_start = match.suffix().first;
    }

    std::regex no_space_before_x("([+\\-*=])X");
    if (std::regex_search(input_string, no_space_before_x)) {
        return false;
    }

    std::regex consecutive_operators_regex("([+\\-*^])\\1+");
    if (std::regex_search(input_string, consecutive_operators_regex)) {
        return false;
    }

    std::regex spaced_operators_regex("[+\\-*^]\\s*[+\\-*^]");
    if (std::regex_search(input_string, spaced_operators_regex)) {
        return false;
    }

    std::regex trailing_operators_regex("([+\\-*])\\s*$");
    if (std::regex_search(input_string, trailing_operators_regex)) {
        return false;
    }

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"<polynomial>\"" << std::endl;
        return 1;
    }

    if (!is_valid_polynomial_input(argv[1])) {
        std::cerr << "Error: Invalid polynomial input." << std::endl;
        return 1;
    }

    Polynomial polynomial(argv[1]);
    polynomial.solvePolynomial();

    return 0;
}