#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <cmath>

// 创建3x3齐次变换矩阵
Eigen::Matrix3d make_transform_mat(double theta, double dx, double dy) {
    Eigen::Matrix3d T = Eigen::Matrix3d::Identity();
    
    // 设置旋转部分
    T(0, 0) = cos(theta);   // cosθ
    T(0, 1) = -sin(theta);  // -sinθ
    T(1, 0) = sin(theta);   // sinθ
    T(1, 1) = cos(theta);   // cosθ
    
    // 设置平移部分
    T(0, 2) = dx;
    T(1, 2) = dy;
    
    return T;
}

// 使用齐次坐标变换点
Eigen::Vector2d transform_point(const Eigen::Matrix3d& T, double x, double y) {
    Eigen::Vector3d point_homogeneous(x, y, 1.0);  // 齐次坐标
    Eigen::Vector3d transformed_homogeneous = T * point_homogeneous;
    
    // 转换回笛卡尔坐标
    return Eigen::Vector2d(transformed_homogeneous(0), transformed_homogeneous(1));
}

int main() {
    // 测试用例
    struct TestCase {
        int example;
        double theta, dx, dy;
        double input_x, input_y;
        double expected_x, expected_y;  // 对于例子5和6，这里设为NAN
    };
    
    std::vector<TestCase> test_cases = {
        {1, 0, 1, 0, 0, 0, 1, 0},
        {2, 1.5707, 0, 0, 0, 1, -1, 0},
        {3, -1.5707, 1, -1, 0, 0, 1, -1},
        {4, -2, 0.56, 0.11, -1, 0.5, 1.43, 0.811},
        {5, 2, 0, -0.3, 1, 0.2, NAN, NAN},  // 例子5，预期结果未知
        {6, 3, 0.5, 0.5, 0.5, 0.5, NAN, NAN}  // 例子6，预期结果未知
    };
    
    std::cout << "Frame Transformations Test Results:\n";
    std::cout << "====================================\n";
    
    for (const auto& test : test_cases) {
        Eigen::Matrix3d T = make_transform_mat(test.theta, test.dx, test.dy);
        Eigen::Vector2d result = transform_point(T, test.input_x, test.input_y);
        
        std::cout << "Example " << test.example << ":\n";
        std::cout << "  Theta: " << test.theta << " rad, Translation: (" 
                  << test.dx << ", " << test.dy << ")\n";
        std::cout << "  Input point: (" << test.input_x << ", " << test.input_y << ")\n";
        std::cout << "  Output point: (" << result(0) << ", " << result(1) << ")\n";
        
        // 对于有预期结果的测试用例，进行验证
        if (!std::isnan(test.expected_x)) {
            double error_x = std::abs(result(0) - test.expected_x);
            double error_y = std::abs(result(1) - test.expected_y);
            std::cout << "  Expected: (" << test.expected_x << ", " << test.expected_y << ")\n";
            std::cout << "  Error: (" << error_x << ", " << error_y << ")\n";
            
            if (error_x < 1e-3 && error_y < 1e-3) {
                std::cout << "  ✓ PASS\n";
            } else {
                std::cout << "  ✗ FAIL\n";
            }
        }
        std::cout << std::endl;
    }
    
    // 单独显示变换矩阵的例子
    std::cout << "\n变换矩阵示例 (Example 1):\n";
    Eigen::Matrix3d T_example = make_transform_mat(0, 1, 0);
    std::cout << "T = \n" << T_example << std::endl;
    
    return 0;
}