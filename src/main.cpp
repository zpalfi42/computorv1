#include <computor.hpp>

bool is_valid_polynomial_input(const std::string &input) {
    if (input.empty())
        return false;
    int count = 0;
    for (char c : input)
    {
        if (c == '=')
            count++;
        else if (!isdigit(c) && c!=' ' && c!='X' && c!='^' && c!='*' && c!='-' && c!='+')
            return false;
    }
    if (count != 1)
        return false;
    
    if (input.size() < 5)
        return false;

    std::string tempGroup;
    size_t  groupCount = 0;

    for (size_t i = 0; i < input.length(); ++i)
    {
        if (input[i] == '=')
        {
            if (i == 0 || i == input.length()-1)
                return false;
            if (input[i-1] != ' ' && input[i+1] != ' ')
                return false;
            if (groupCount == 0)
                return false;
        }
        if (input[i] == '+' || input[i] == '-' || input[i] == '=' || i == input.length() - 1)
        {
            // CHECK EMPTPY GROUP (MEANS DOUBLE SIGN OR SIGN FOLLOWED BY NOTHING)
            if (tempGroup.size() < 1 && groupCount != 0)
                return false;
            if (tempGroup == "=" && i == input.length() - 1)
                return false;
            // ADD LAST CHAR
            if (i == input.length() - 1 && input[i] != ' ')
            {
                if (input[i] == '-' || input[i] == '+')
                    return false;
                tempGroup += input[i];
            }

            // CHECK ONLY OPERATOR ERROR
            if ((tempGroup.find('-') != std::string::npos || tempGroup.find('+') != std::string::npos) && tempGroup.length() == 1)
                return false;
            // CHECK X ERRORS
            if (tempGroup.find('X') != std::string::npos)
            {
                if (tempGroup.find('X') + 1 != tempGroup.size())
                {
                    if (tempGroup.size() < 3)
                        return false;
                    else if (tempGroup[tempGroup.find('X')+1] != '^' || !isdigit(tempGroup[tempGroup.find('X')+2]))
                        return false;
                }
                if (tempGroup.find('X') != 0)
                    if (tempGroup[tempGroup.find('X')-1] != '-' && tempGroup[tempGroup.find('X')-1] != '+' && tempGroup[tempGroup.find('X')-1] != '*')
                        return false;
            }

            // CHECK * ERRORS
            if (tempGroup.find('*') != std::string::npos)
            {
                if (tempGroup[0] == '*' || tempGroup[tempGroup.size()-1] == '*')
                    return false;
                else if (!isdigit(tempGroup[0]) && !isdigit(tempGroup[1]))
                    return false;
                else if (tempGroup[tempGroup.find('*')+1] != 'X')
                    return false;
            }
            tempGroup.clear();
            groupCount++;
        }
        if (input[i] != ' ')
            tempGroup += input[i];
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
