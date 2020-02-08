#ifndef BLP_H
#define BLP_H

#include <iostream>

#define Order_N 4 //blp filter order
class Blp
{
public:
    Blp();
    ~Blp();

    double blp_filter(const double& data);


    double smooth_averpara_filter(const double& data);
    double smooth_aver_filter(const double& data);

private:
    double a[Order_N+1] = {1, -0.2687, 0.5089, -0.0571, 0.0191}; // need a matlab scripts
    double b[Order_N+1] = {0.0751, 0.3005, 0.4508, 0.3005,0.0751}; // need a matlab scripts
    double x[Order_N+1] = {0};
    double y[Order_N+1] = {0};

    int num_count = 5;
    double butter[5] = {0};

    void array_left_move(double* array, const double& data);
    void array_left_move(double* array, const int& j, const double& data);
};
#endif // BLP_H
