#include <iostream>
#include <eigen3/Eigen/Eigen>

int main()
{
    Eigen::VectorXd sensor(10);
    sensor << 0., 0.11111111, 0.22222222, 0.33333333, 0.44444444, 0.55555556, 0.66666667, 0.77777778, 0.88888889, 1.0;
    
    Eigen::VectorXd distance(10);
    distance << 0.48147829, 0.70278627, 0.94916103, 1.1409607, 1.38118014, 1.62292857, 1.81760639, 2.04022307, 2.27369675, 2.495571;

    // create A using sensor
    Eigen::MatrixXd A(10, 2);
    A.col(0) = Eigen::VectorXd::Ones(10);  // 第一列全为1（对应x1）
    A.col(1) = sensor;                     // 第二列为传感器读数（对应x2）

    // create b using distance
    Eigen::VectorXd b = distance;

    // solve for x using QR method
    Eigen::Vector2d x = A.colPivHouseholderQr().solve(b);

    // write down the values for x1 and x2
    std::cout << "Range Sensor Calibration Results:" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "Calibration parameters:" << std::endl;
    std::cout << "x1 (offset/bias) = " << x(0) << std::endl;
    std::cout << "x2 (scale/gain)  = " << x(1) << std::endl;
    std::cout << std::endl;

    // 验证结果：计算预测值和残差
    std::cout << "Verification:" << std::endl;
    std::cout << "Sensor\tActual\tPredicted\tResidual" << std::endl;
    std::cout << "------\t------\t--------\t--------" << std::endl;
    
    double total_error = 0.0;
    for (int i = 0; i < 10; ++i) {
        double predicted = x(0) + x(1) * sensor(i);
        double residual = distance(i) - predicted;
        total_error += residual * residual;
        
        std::cout << sensor(i) << "\t" << distance(i) << "\t" << predicted 
                  << "\t" << residual << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Total squared error: " << total_error << std::endl;

    // 最终校准方程
    std::cout << std::endl;
    std::cout << "Calibration equation:" << std::endl;
    std::cout << "distance = " << x(0) << " + " << x(1) << " * sensor_reading" << std::endl;

    return 0;
}