// Copyright 2020 Maria

#ifndef INCLUDE_POLYNOMIAL_HPP_
#define INCLUDE_POLYNOMIAL_HPP_

#include <iostream>
#include <type_traits>
#include <vector>
#include <limits>
#include <cmath>

template<class T>
class Polynomial{
    static_assert(std::is_arithmetic<T>::value, "Not arithmetic type");
    std::vector<T> pol;

public:
    Polynomial(){
        this->pol.resize(0);
    }
    explicit Polynomial(int n){
        this->pol.resize(n);
    }
    explicit Polynomial(const std::vector<T>& M){
        this->pol.resize(M.size());
        for (int i = 0; i < static_cast<int>(M.size()); i++){
            pol[i] = M[i];
        }
    }
    Polynomial(const T f, int i){
        this->pol.resize(i+1);
        pol[0] = f;
        for (int j = 1; j <= i ; j++) pol[j] = 0;
    }
    int degree(){
        return (pol.size() - 1);
    }
    //std::vector<T> operator[](int index) const{
    T operator[](int index) const{
        return pol[index];
    }
    Polynomial operator+(const Polynomial& H) const{
        Polynomial<T> F(0);
        if (pol.size() <= H.pol.size()){
            int m = static_cast<int>(H.pol.size()-pol.size());
            F.pol.resize(H.pol.size());
            for (int i = static_cast<int>(H.pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i - m] + H.pol[i];
            }
            for (int j = m - 1; j >= 0; j--){
                F.pol[j] = H.pol[j];
            }
        }
        if (pol.size() > H.pol.size()){
            int m = static_cast<int>(pol.size() - H.pol.size());
            F.pol.resize(pol.size());
            for (int i = static_cast<int>(pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i] + H.pol[i - m];
            }
            for (int j = m - 1 ; j >= 0; j--){
                F.pol[j] = pol[j];
            }
        }
        return F;
    }
    Polynomial operator+=(const Polynomial& H){
        Polynomial<T> F(0);
        if (pol.size() <= H.pol.size()){
            int m = static_cast<int>(H.pol.size()-pol.size());
            F.pol.resize(H.pol.size());
            for (int i = static_cast<int>(H.pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i - m] + H.pol[i];
            }
            for (int j = m - 1; j >= 0; j--){
                F.pol[j] = H.pol[j];
            }
        }
        if (pol.size() > H.pol.size()){
            int m = static_cast<int>(pol.size() - H.pol.size());
            F.pol.resize(pol.size());
            for (int i = static_cast<int>(pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i] + H.pol[i - m];
            }
            for (int j = m - 1 ; j >= 0; j--){
                F.pol[j] = pol[j];
            }
        }
        pol.clear();
        pol.resize(F.pol.size());
        for (int i = 0; i < static_cast<int>(pol.size()); i++){
            pol[i] = F.pol[i];
        }
        return *this;
    }
    Polynomial operator-(const Polynomial& H) const{
        Polynomial<T> F(0);
        if (pol.size() <= H.pol.size()){
            int m = static_cast<int>(H.pol.size()-pol.size());
            F.pol.resize(H.pol.size());
            for (int i = static_cast<int>(H.pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i-m] - H.pol[i];
            }
            for (int j = m - 1; j >= 0; j--){
                F.pol[j] = -H.pol[j];
            }
            while (F.pol[0] == 0) {
                auto iter = F.pol.cbegin();
                F.pol.erase(iter);
            }
        }
        if (pol.size() > H.pol.size()){
            int m = static_cast<int>(pol.size() - H.pol.size());
            F.pol.resize(pol.size());
            for (int i = static_cast<int>(pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i] - H.pol[i-(pol.size() - H.pol.size())];
            }
            for (int j = m - 1; j >= 0; j--){
                F.pol[j] = pol[j];
            }
        }
        return F;
    }
    Polynomial operator-=(const Polynomial& H){
        Polynomial<T> F(0);
        if (pol.size() <= H.pol.size()){
            int m = static_cast<int>(H.pol.size()-pol.size());
            F.pol.resize(H.pol.size());
            for (int i = static_cast<int>(H.pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i-m] - H.pol[i];
            }
            for (int j = m - 1; j >= 0; j--){
                F.pol[j] = -H.pol[j];
            }
            while (F.pol[0] == 0) {
                auto iter = F.pol.cbegin();
                F.pol.erase(iter);
            }
        }
        if (pol.size() > H.pol.size()){
            int m = static_cast<int>(pol.size() - H.pol.size());
            F.pol.resize(pol.size());
            for (int i = static_cast<int>(pol.size()) - 1; i >= m; i--){
                F.pol[i] = pol[i] - H.pol[i-(pol.size() - H.pol.size())];
            }
            for (int j = m - 1; j >= 0; j--){
                F.pol[j] = pol[j];
            }
        }
        pol.clear();
        pol.resize(F.pol.size());
        for (int i = 0; i < static_cast<int>(pol.size()); i++){
            pol[i] = F.pol[i];
        }
        return *this;
    }
    Polynomial operator*(const Polynomial& G) const{
        int m = static_cast<int>(pol.size() + G.pol.size()) - 1;
        Polynomial<T> F(m);
        for (int i = 0; i < m; i++) F.pol[i] = 0;
        for (int i = 0; i < static_cast<int>(pol.size()); i++){
            for (int j = 0; j < static_cast<int>(G.pol.size()); j++){
                double h = pol[i]*G.pol[j];
                F.pol[i+j]+=h;
            }
        }
        return F;
    }
    Polynomial operator*=(const Polynomial& G){
        int m = static_cast<int>(pol.size() + G.pol.size()) - 1;
        Polynomial<T> F(m);
        for (int i = 0; i < m; i++) F.pol[i] = 0;
        for (int i = 0; i < static_cast<int>(pol.size()); i++){
            for (int j = 0; j < static_cast<int>(G.pol.size()); j++){
                double h = pol[i]*G.pol[j];
                F.pol[i+j]+=h;
            }
        }
        pol.clear();
        pol.resize(F.pol.size());
        for (int i = 0; i < pol.size(); i++){
            pol[i] = F.pol[i];
        }
        return *this;
    }
    Polynomial operator*(const T f) const{
        Polynomial<T> F(pol.size());
        if (f == 0) {
            Polynomial<T> nul(1);
            nul.pol[0] = 0;
            return nul;
        }
        for (int i = 0; i < static_cast<int>(pol.size()); i++){
            F.pol[i] = pol[i] * f;
        }
        return F;
    }
    Polynomial operator/(const Polynomial& H) const{
        if (pol.size() < H.pol.size()) {
            Polynomial<T> R(1);
            R.pol[0] = 0;
            return R;
        } else {
            if (pol.size() == H.pol.size()) {
                double f = pol[0] / H.pol[0];
                Polynomial<T> R(1);
                R.pol[0] = f;
                return R;
            } else {
                Polynomial<T> ost(static_cast<int>(pol.size()));
                int h = static_cast<int>(pol.size()-H.pol.size())+1;
                Polynomial<T> chast(h);
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    ost.pol[i] = pol[i];
                }
                for (int i = 0; i < static_cast<int>(chast.pol.size()); i++){
                    double m = ost.pol[0] / H.pol[0];
                    for (int j = 0; j < static_cast<int>(H.pol.size()); j++){
                        ost.pol[j] -= m * H.pol[j];
                    }
                    chast.pol[i] = m;
                    auto iter = ost.pol.cbegin();
                    ost.pol.erase(iter);
                }
                return chast;
            }
        }
    }
    Polynomial operator/=(const Polynomial& H){
        if (pol.size() < H.pol.size()) {
            pol.resize(1);
            pol[0] = 0;
            return *this;
        } else {
            if (pol.size() == H.pol.size()) {
                double f = pol[0] / H.pol[0];
                Polynomial<T> R(1);
                R.pol[0] = f;
                return R;
            } else {
                Polynomial<T> ost(static_cast<int>(pol.size()));
                int h = static_cast<int>(pol.size()-H.pol.size())+1;
                Polynomial<T> chast(h);
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    ost.pol[i] = pol[i];
                }
                for (int i = 0; i < static_cast<int>(chast.pol.size()); i++){
                    double m = ost.pol[0] / H.pol[0];
                    for (int j = 0; j < static_cast<int>(H.pol.size()); j++){
                        ost.pol[j] -= m * H.pol[j];
                    }
                    chast.pol[i] = m;
                    auto iter = ost.pol.cbegin();
                    ost.pol.erase(iter);
                }
                pol.clear();
                pol.resize(chast.pol.size());
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    pol[i] = chast.pol[i];
                }
                return *this;
            }
        }
    }
    Polynomial operator%(const Polynomial& H) const{
        if (pol.size() < H.pol.size()) {
            return *this;
        } else {
            if (pol.size() == H.pol.size()) {
                double f = pol[0] / H.pol[0];
                Polynomial<T> R(static_cast<int>(pol.size()));
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    R.pol[i] = pol[i] - f * H.pol[i];
                }
                while (R.pol[0] < std::numeric_limits<double>::epsilon()) {
                    auto iter = R.pol.cbegin();
                    R.pol.erase(iter);
                }
                return R;
            } else {
                Polynomial<T> ost(static_cast<int>(pol.size()));
                int h = static_cast<int>(pol.size()-H.pol.size())+1;
                Polynomial<T> chast(h);
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    ost.pol[i] = pol[i];
                }
                for (int i = 0; i < static_cast<int>(chast.pol.size()); i++){
                    double m = ost.pol[0] / H.pol[0];
                    for (int j = 0; j < static_cast<int>(H.pol.size()); j++) {
                        ost.pol[j] -= m * H.pol[j];
                    }
                    chast.pol[i] = m;
                    auto iter = ost.pol.cbegin();
                    ost.pol.erase(iter);
                }
                return ost;
            }
        }
    }
    Polynomial operator%=(const Polynomial& H){
        if (pol.size() < H.pol.size()) {
            return *this;
        } else {
            if (pol.size() == H.pol.size()) {
                double f = pol[0] / H.pol[0];
                Polynomial<T> R(static_cast<int>(pol.size()));
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    R.pol[i] = pol[i] - f * H.pol[i];
                }
                while (R.pol[0] < std::numeric_limits<double>::epsilon()) {
                    auto iter = R.pol.cbegin();
                    R.pol.erase(iter);
                }
                return R;
            } else {
                Polynomial<T> ost(static_cast<int>(pol.size()));
                int h = static_cast<int>(pol.size()-H.pol.size())+1;
                Polynomial<T> chast(h);
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    ost.pol[i] = pol[i];
                }
                for (int i = 0; i < static_cast<int>(chast.pol.size()); i++){
                    double m = ost.pol[0] / H.pol[0];
                    for (int j = 0; j < static_cast<int>(H.pol.size()); j++) {
                        ost.pol[j] -= m * H.pol[j];
                    }
                    chast.pol[i] = m;
                    auto iter = ost.pol.cbegin();
                    ost.pol.erase(iter);
                }
                pol.clear();
                pol.resize(ost.pol.size());
                for (int i = 0; i < static_cast<int>(pol.size()); i++){
                    pol[i] = ost.pol[i];
                }
                return *this;
            }
        }
    }
    double value(const T x) const{
        double result = 0;
        double per = 1;
        for (int i = static_cast<int>(pol.size())-1 ; i >= 0; i--){
            result+=per*pol[i];
            per*=x;
        }
        return result;
    }
    Polynomial operator=(const std::vector<T>& M){
        pol.resize(M.size());
        for (int i = 0; i < static_cast<int>(M.size()); i++){
            pol[i] = M[i];
        }
        return *this;
    }
    ~Polynomial(){
        pol.clear();
    }
    template<class R>
    friend bool operator==(const Polynomial<R>& P, const Polynomial<R>& Q);
};
template<class T>
bool operator==(const Polynomial<T> &P, const Polynomial<T> &Q){ //double?
    if (std::is_floating_point<T>::value){
        if (P.pol.size() == Q.pol.size()){
    for (int i = 0; i < static_cast<int>(P.pol.size()); i++){
if (std::abs(P.pol[i] - Q.pol[i])>1000*std::numeric_limits<double>::epsilon()){
            return false;
        }
            }
            return true;
        }
    } else {
        if (P.pol.size() == Q.pol.size()){
            for (int i = 0; i < static_cast<int>(P.pol.size()); i++){
                if (P.pol[i] != Q.pol[i]) return false;
            }
            return true;
        } else {
            return false;
        }
    }
    return false;
}

#endif // INCLUDE_POLYNOMIAL_HPP_
