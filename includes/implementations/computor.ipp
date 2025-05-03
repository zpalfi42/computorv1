#ifndef COMPUTOR_IPP
# define    COMPUTOR_IPP

# include "computor.hpp"

double absoluteDifference(double a, double b) {
    return (a > b) ? (a - b) : (b - a);
}

double squareRoot(double x, double precision = 0.00001) {
    if (x < 0) {
        return -1;
    }
    if (x == 0) {
        return 0;
    }

    double guess = x / 2.0;
    double previousGuess;

    do {
        previousGuess = guess;
        guess = (guess + x / guess) / 2.0;
    } while (absoluteDifference(guess, previousGuess) > precision);

    return guess;
}

void Polynomial::parsePolynomial(void) {
    bool rhs = false;
    std::string tempGroup;

    for (size_t i = 0; i < _rawStr.length(); ++i) {
        std::string temp = _rawStr.substr(i, 3);
        tempGroup += _rawStr[i];
        if (temp == " + " || temp == " - " || temp == " = " || i == _rawStr.length() - 1) {
            int pow = 0;
            float num = 1.0;
            int sign = 1;

            if (tempGroup.find('X') != std::string::npos) {
                std::string powStr;
                if (tempGroup.find('X')+2 < tempGroup.length())
                    powStr = tempGroup.substr(tempGroup.find('X')+2, 3);
                else
                    powStr = "1";
                if (powStr == "")
                    powStr = "1";
                pow = std::stoi(powStr);
            }

            if ((tempGroup.find('*') != std::string::npos) || (tempGroup.find('X') == std::string::npos))
                num = std::stof(tempGroup.substr(tempGroup.find_first_of("0123456789"), tempGroup.substr(tempGroup.find_first_of("0123456789")).find_first_of(" ")));

            if (tempGroup.find('-') != std::string::npos)
                    sign = -1;

            if (rhs)
                sign = -sign;

            _polynomial[pow] += sign * num;

            if (temp == " = ")
            {
                i += 2;
                rhs = true;
            }

            tempGroup.clear();
        }
    }

    for (const auto &pair : _polynomial) {
        if (pair.first > _degree && pair.second != 0)
            _degree = pair.first;
    }
}

void Polynomial::printPolynomialDegree(void) const {
    std::cout << "Polynomial degree: " << _degree << std::endl;
}

void Polynomial::printPolynomialReduced(void) const {
    std::cout << "Reduced Polynomial: ";
    for (const auto &pair : _polynomial) {
        if (pair.second > 0 && pair.first != 0)
            std::cout << "+ ";
        if (pair.second > 1 || pair.second < -1)
        {
            if (pair.first == 0)
                std::cout << pair.second << " ";
            else if (pair.first == 1)
                std::cout << pair.second << " * X ";
            else if (pair.first > 1)
                std::cout << pair.second << " * X^" << pair.first << " ";
        }
        else if (pair.second == 1 || pair.second == -1)
        {
            if (pair.first == 0)
                std::cout << pair.second << " ";
            else if (pair.first == 1)
                if (pair.second == 1)
                    std::cout << "X ";
                else
                    std::cout << "- X ";
            else
                if (pair.second == 1)
                    std::cout << "X^" << pair.first << " ";
                else
                    std::cout << "- X^" << pair.first << " ";
        }
        else if (_polynomial.size() == 1)
            std::cout << "0 ";
    }
    std::cout << "= 0" << std::endl;
}

void Polynomial::solvePolynomial(void) {
    if (_degree == 0) {
        if (_polynomial[0] == 0) {
            std::cout << "All real numbers are solutions" << std::endl;
        } else {
            std::cout << "No solution" << std::endl;
        }
        return;
    }
    else if (_degree == 1) {
        auto it = _polynomial.begin();
        float a = it->second;
        ++it;
        float b = it->second;
        std::cout << "The solution is: " << -a / b << std::endl;
        return;
    }
    else if (_degree == 2) {
        float a = _polynomial[2];
        float b = _polynomial[1];
        float c = _polynomial[0];
        float discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            std::cout << "Discriminant is strictly positive, the two solutions are: " << std::endl;
            float x1 = (-b - squareRoot(discriminant)) / (2 * a);
            float x2 = (-b + squareRoot(discriminant)) / (2 * a);
            std::cout << x1 << std::endl << x2 << std::endl;
        } else if (discriminant == 0) {
            float x = -b / (2 * a);
            std::cout << "Discriminant is equal to 0, the solution is: " << x << std::endl;
        } else {
            std::cout << "Discriminant is strictly negative, the two complex solutions are: " << std::endl;
            float realPart = -b / (2 * a);
            float imaginaryPart = squareRoot(-discriminant) / (2 * a);
            if (imaginaryPart > 0)
            {
                std::cout << realPart << " +" << imaginaryPart << "i" << std::endl;
                std::cout << realPart << " -" << imaginaryPart << "i" << std::endl;
            }
            else
            {
                std::cout << realPart << " " << imaginaryPart << "i" << std::endl;
                std::cout << realPart << " +" << -imaginaryPart << "i" << std::endl;
            }
        }
    }
    else {
        std::cout << "Polynomial degree is strictly greater than 2, I can't solve." << std::endl;
    }
}

std::string Polynomial::getRawStr(void) const {
    return _rawStr;
}

std::map<int, float> Polynomial::getPolynomial(void) const {
    return _polynomial;
}

int Polynomial::getDegree(void) const {
    return _degree;
}

void Polynomial::setRawStr(const std::string &rawStr) {
    _rawStr = rawStr;
}

void Polynomial::setPolynomial(const std::map<int, float> &polynomial) {
    _polynomial = polynomial;
}

void Polynomial::setDegree(int degree) {
    _degree = degree;
}

#endif