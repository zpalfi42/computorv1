#include <computor.hpp>
#include <iostream>
#include <string>
#include <regex>
#include <cctype>
#include <algorithm>

// Function to check if a string is a valid number (including negative numbers)
// Function to check if a string is a valid number (including negative numbers)
bool is_valid_number(const std::string& str) {
    if (str.empty()) return false;
    std::string trimmedStr = str;
     size_t start = trimmedStr.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmedStr = trimmedStr.substr(start);
    }
    if (trimmedStr.empty()) return false;
    std::regex number_regex(R"(^[+-]?\d+(\.\d*)?$)"); // Corrected regex
    return std::regex_match(trimmedStr, number_regex);
}

// Function to check if a string is a valid variable (X)
bool is_valid_variable(const std::string& str) {
    return str == "X";
}

// Function to check if a string is a valid exponent
bool is_valid_exponent(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }
    try {
      if (!str.empty()) {
        int exponentValue = std::stoi(str);
        return exponentValue >= 0;
      }
      else
        return false;
    } catch (const std::invalid_argument& e) {
        return false;
    } catch (const std::out_of_range& e) {
        return false;
    }
}

// Function to check if a string is a valid operator (+, -, *)
bool is_valid_operator(const std::string& str) {
    return str == "+" || str == "-" || str == "*";
}

// Function to check if a string is a valid equal sign
bool is_valid_equal_sign(const std::string& str) {
    return str == "=";
}
// Function to remove extra spaces
std::string removeExtraSpaces(const std::string& str) {
    std::string result;
    bool previousSpace = false;
    for (char c : str) {
        if (std::isspace(c)) {
            if (!previousSpace) {
                result += ' ';
                previousSpace = true;
            }
        } else {
            result += c;
            previousSpace = false;
        }
    }
    // Remove leading and trailing spaces
    size_t firstNonSpace = result.find_first_not_of(' ');
    if (firstNonSpace != std::string::npos) {
        result = result.substr(firstNonSpace);
    } else {
        result = ""; // String was all spaces
    }
    size_t lastNonSpace = result.find_last_not_of(' ');
    if (lastNonSpace != std::string::npos) {
        result = result.substr(0, lastNonSpace + 1);
    } else {
        result = "";
    }
    return result;
}

// Function to validate the polynomial input string
bool is_valid_polynomial_input(const std::string& input) {
    std::string cleanedInput = removeExtraSpaces(input);
    if (cleanedInput.empty()) return false;

    std::vector<std::string> tokens;
    std::string currentToken;
    for (char c : cleanedInput) {
        if (c == '+' || c == '-' || c == '*' || c == '=') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
            }
            tokens.push_back(std::string(1, c));
            currentToken = "";
        } else {
            currentToken += c;
        }
    }
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }
    if (tokens.empty())
        return false;
    // Check for the basic structure: term operator term = term
    if (tokens.size() < 3 || std::find(tokens.begin(), tokens.end(), "=") == tokens.end()) {
        return false;
    }
    int equalSignCount = std::count(tokens.begin(), tokens.end(), "=");
    if (equalSignCount != 1) {
        return false;
    }

    size_t equalPos = std::find(tokens.begin(), tokens.end(), "=") - tokens.begin();
    //check that there are tokens before and after the =
    if (equalPos == 0 || equalPos == tokens.size() - 1)
        return false;
    // Validate tokens before the equal sign
    for (size_t i = 0; i < equalPos; ++i) {
        if (i % 2 == 0) {
            // Even positions: numbers or terms (X, X^n)
            if (!(is_valid_number(tokens[i]) || (is_valid_variable(tokens[i]))))
            {
                 //check for the X^n case
                std::string token = tokens[i];
                size_t expPos = token.find("^");
                if(expPos != std::string::npos){
                    std::string base = token.substr(0,expPos);
                    std::string exp = token.substr(expPos+1);
                    if(!(is_valid_variable(base) && is_valid_exponent(exp)))
                        return false;
                }
                else
                    return false;
            }
        } else {
            // Odd positions: operators (+, -, *)
            if (!is_valid_operator(tokens[i])) {
                return false;
            }
        }
    }

    // Validate tokens after the equal sign
     for (size_t i = equalPos + 1; i < tokens.size(); ++i) {
        if (i % 2 != equalPos % 2) {
            // Even positions: numbers or terms (X, X^n)
            if (!(is_valid_number(tokens[i]) || (is_valid_variable(tokens[i]))))
            {
                 //check for the X^n case
                std::string token = tokens[i];
                size_t expPos = token.find("^");
                if(expPos != std::string::npos){
                    std::string base = token.substr(0,expPos);
                    std::string exp = token.substr(expPos+1);
                    if(!(is_valid_variable(base) && is_valid_exponent(exp)))
                        return false;
                }
                else
                    return false;
            }
        } else {
            // Odd positions: operators (+, -, *)
            if (i > equalPos + 1 && !is_valid_operator(tokens[i])) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char **argv) {
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
