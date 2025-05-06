#ifndef COMPUTOR_BONUS_HPP
# define COMPUTOR_BONUS_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>


class Polynomial {
public:
    Polynomial(const std::string &rawStr);
    ~Polynomial(void);

    void parsePolynomial(void);
    void solvePolynomial(void);
    
    void printPolynomialReduced(void) const;
    void printPolynomialDegree(void) const;

    std::string getRawStr(void) const;
    std::map<int, float> getPolynomial(void) const;
    int getDegree(void) const;

    void setRawStr(const std::string &rawStr);
    void setPolynomial(const std::map<int, float> &polynomial);
    void setDegree(int degree);

private:
    std::string             _rawStr;
    std::map<int, float>    _polynomial;
    int                     _degree;
};

# include "computor_bonus.ipp"

#endif