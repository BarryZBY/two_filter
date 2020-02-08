#include "Blp.h"

Blp::Blp() {}
Blp::~Blp() {}

void Blp::array_left_move(double* array, const double& data)
{
    //std::cout << "-------now is function array_left_move------" << std::endl;
    for (int i = 0; i < Order_N; i++)
    {
        array[i] = array[i+1];
        //std::cout << array[i] << ", ";
    }
    array[Order_N] = data;
    //std::cout << array[Order_N] << std::endl;
    //std::cout << "-------now leave function array_left_move------" << std::endl;
}

//4-butterworth low pass filter
//a(0)*y(n) = b(0)*x(n) + b(1)*x(n-1) + b(2)*x(n-2) + b(3)*x(n-3) + b(4)*x(n-4) -(a(1)*y(n-1) + a(2)*y(n-2) + a(3)*y(n-3) + a(4)*y(n-4))
double Blp::blp_filter(const double& data)
{

    double yn = 0;
    //std::cout << "-------now is function blp_filter------" << std::endl;
    array_left_move(x, data); //origin data array x

    if (x[0] == 0)
        yn = data;
    else
    {
        yn = b[0] * x[Order_N];

        for (int i=1; i<= Order_N; i++)
        {
            yn += b[i] * x[Order_N-i] - a[i] * y[Order_N-i];
        }
    }
    array_left_move(y, yn); // data after filter array y
    //std::cout << "-------now leave function blp_filter------" << std::endl;
    return yn;
}


void Blp::array_left_move(double* array, const int& j, const double& data)
{
    //std::cout << "-------now is function array_left_move------" << std::endl;
    int i = 0;
    for(i = 1; i < j; i++)
    {
        array[i-1] = array[i];
        // std::cout << "array[" << i-1 << "] = " << array[i-1] << ", ";
    }
    array[i-1] = data;
    //std::cout << "array[" << i-1 << "] = " << array[i-1] << std::endl;
    //std::cout << "-------now leave function array_left_move------" << std::endl;
}

double Blp::smooth_averpara_filter(const double& data)
{
//    std::cout << "-------now is function smooth_averpara_filter------" << std::endl;
//    for(int i=0; i<num_count; i++)
//    {
//        std::cout << "butter[" << i << "] = " << butter[i] << ", ";
//    }
//    std::cout << std::endl;
    array_left_move(butter, num_count, data);
//    for(int i=0; i<num_count; i++)
//    {
//        std::cout << "butter[" << i << "] = " << butter[i] << ", ";
//    }
//    std::cout << std::endl;
    double sum=0;
    for(int i=0; i<num_count; i++)
    {
        if (i >= 0 && i <= num_count/2-1)
            sum += butter[i] * (0.8 / num_count);
        else if (i >= num_count/2 && i <= num_count-2)
            sum += butter[i]*(0.8 / (num_count - 2));
        else if (i == num_count-1)
            sum += butter[i] * 0.2;
        //std::cout << "i = " << i << ", sum = " << sum << ", ";
    }
//    std::cout << std::endl;
//    std::cout << "-------now leave function smooth_averpara_filter------" << std::endl;
    return sum;
}

double Blp::smooth_aver_filter(const double& data)
{
    array_left_move(butter, num_count, data);
    double sum2 = 0;
    double min = 0;
    double max = 0;
    for(int i = 0; i < num_count; i++)
    {
        sum2 += butter[i];
        if (min > butter[i]){
            min = butter[i];
        }

        if (max < butter[i]){
            max = butter[i];}
    }
    return (sum2 - min - max) / (num_count-2);
}
