// Copyright 2020 Maria

#include <gtest/gtest.h>

#include <polynomial.hpp>

TEST(Polynomial, Init){
    Polynomial<int> P({ 2, 4, 3, 0, 7});
    EXPECT_EQ(P[0], 2);
    EXPECT_EQ(P[1], 4);
    EXPECT_EQ(P[2], 3);
    EXPECT_EQ(P[3], 0);
    EXPECT_EQ(P[4], 7);
}
TEST(Polynomial, Addit){
    Polynomial<int> P({ 2, 4, 3, 0, 7});
    Polynomial<int> F({ 3, 0, 6, 1, 2});
    Polynomial<int> M = P + F;
    EXPECT_EQ(M[0], 5);
    EXPECT_EQ(M[1], 4);
    EXPECT_EQ(M[2], 9);
    EXPECT_EQ(M[3], 1);
    EXPECT_EQ(M[4], 9);
    P += F;
    EXPECT_EQ(M, P);
    M -= F;
    EXPECT_EQ(M[0], 2);
    EXPECT_EQ(M[1], 4);
    EXPECT_EQ(M[2], 3);
    EXPECT_EQ(M[3], 0);
    EXPECT_EQ(M[4], 7);
}
TEST(Polynomial, Multip){
    Polynomial<int> R, Q, H;
    R = { 2, 4, 2, 8, 0};
    Q = { 3, 8, 5, 0, 7};
    H = R * Q;
    EXPECT_EQ(H[0], 6);
    EXPECT_EQ(H[1], 28);
    EXPECT_EQ(H[2], 48);
    EXPECT_EQ(H[3], 60);
    EXPECT_EQ(H[4], 88);
    EXPECT_EQ(H[5], 68);
    EXPECT_EQ(H[6], 14);
    EXPECT_EQ(H[7], 56);
    EXPECT_EQ(H[8], 0);
    Polynomial<double> P;
    P = { 2.8, 4.5, 2.4, 8, 0};
    Polynomial<double> F;
    F = { 3, 8.4, 5, 0.5, 7};
    auto M = P * F;
    auto L = F * P;
    ASSERT_EQ(M.degree(), 8);
    ASSERT_EQ(L.degree(), 8);
    EXPECT_EQ(M, L);
}
TEST(Polynomial, Division){
    Polynomial<int> P({ 3, 6, 1, 28, 19, 7, 38, 15});
    Polynomial<int> F({ 3, 0, 1, 5});
    auto M = P / F;
    ASSERT_EQ(M.degree(), 4);
    EXPECT_EQ(M[0], 1);
    EXPECT_EQ(M[1], 2);
    EXPECT_EQ(M[2], 0);
    EXPECT_EQ(M[3], 7);
    EXPECT_EQ(M[4], 3);
    Polynomial<int> L;
    L = M * F;
    EXPECT_EQ(P, L);
}
TEST(Polynomial, Remainder){
    Polynomial<double> M({3, 8, 3, 9, 0, 7});
    Polynomial<double> m({2, 2, 5});
    Polynomial<double> D, J;
    D = M / m;
    J = M % m;
    EXPECT_EQ(J[0], 17.75);
    EXPECT_EQ(J[1], -8);
    auto F = D * m + J;
    EXPECT_EQ(F, M);
    M /= m;
    EXPECT_EQ(D, M);
    int f = m.value(5);
    EXPECT_EQ(f, 65);
}
TEST(Polynomial, Multconst){
    Polynomial<float> P({3, 4.6, 8.3});
    int m = 0;
    auto F = P * m;
    EXPECT_EQ(F.degree(), 0);
    EXPECT_EQ(F[0], 0);
}
TEST(Polynomial, DegreeInit){
    Polynomial<int> P(4, 3);
    EXPECT_EQ(P[0], 4);
    EXPECT_EQ(P[1], 0);
    EXPECT_EQ(P[2], 0);
    EXPECT_EQ(P[3], 0);
}
TEST(Polynomial, Forchar){
    Polynomial<char> P(4);
    P = {2, 5, 7, 12};
    auto F = P;
    auto D = P + F;
    EXPECT_EQ(D[0], 4);
    EXPECT_EQ(D[1], 10);
    EXPECT_EQ(D[2], 14);
    EXPECT_EQ(D[3], 24);
}
