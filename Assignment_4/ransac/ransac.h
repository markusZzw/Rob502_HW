#include <random>
#include <iomanip>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <vector>
#include <set>


struct Plane
{
    double a;
    double b;
    double c;
    double d;
};

struct FitResult
{
    Plane plane;
    int n_inliers = -1;
};

void pretty_print(std::string const &input_filename, Plane const &plane)
{
    std::cout << std::setprecision(3) << "--infile " << input_filename << " -a " << plane.a << " -b " << plane.b << " -c " << plane.c << " -d " << plane.d << '\n';
}

std::ostream &operator<<(std::ostream &os, Plane const &plane)
{
    os << std::setprecision(3) << plane.a << " " << plane.b << " " << plane.c << " " << plane.d;
    return os;
}

Plane compute_plane_from_points(Eigen::Vector3d const &p0,Eigen::Vector3d const &p1,Eigen::Vector3d const &p2)
{
    // 1. given p0, p1, and p2 form two vectors v1 and v2 which lie on the plane
    // 2. use v1 and v2 to find the normal vector of the plane `n`
    // 3. set a,b,c from the normal vector `n`
    // 4. set `d = -n.dot(p0)`
    // --- Your code here
    Eigen::Vector3d v1= p1-p0;
    Eigen::Vector3d v2= p2-p0;
    Eigen::Vector3d n= v1.cross(v2);
    double norm = n.norm();
    if (norm < 1e-8){
        return Plane{0,0,0,0};
    }
    double a=n.x();
    double b=n.y();
    double c=n.z();
    double d=-n.dot(p0);
    return Plane{a,b,c,d};
    // ---
}

class BaseFitter
{
public:
    BaseFitter(int num_points) : mt(rd()), dist(0, num_points - 1)
    {
        mt.seed(0);
    }
    /**
     * Given all of the data `points`, select a random subset and fit a plane to that subset.
     * the parameter points is all of the points
     * the return value is the FitResult which contains the parameters of the plane (a,b,c,d) and the number of inliers
     */
    virtual FitResult fit(Eigen::MatrixXd const &points) = 0;

    int get_random_point_idx()
    {
        return dist(mt);
    };

    double const inlier_threshold_{0.02};

private:
    // These are for generating random indices, you don't need to know how they work.
    // Just use `get_random_point_idx()` and `points.row(rand_idx)`
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};

class AnalyticFitter : public BaseFitter
{
public:
    AnalyticFitter(int num_points) : BaseFitter(num_points) {}

    // by writing `override`, the compiler will check that this function actually overrides something 
    // in the base class. Always use this to prevent mistakes in the function signature!
    FitResult fit(Eigen::MatrixXd const &points) override
    {
        // 1. select 3 points from `points` randomly 
        // 2. compute the equation of the plane (HINT: use compute_plane_from_points)
        // 3. compute the `n_inliers` given that plane equation
        // (HINT: multiply the points matrix by the normal vector)
        // --- Your code here
        std::set<int> indices;
        while(indices.size()<3){
            indices.insert(get_random_point_idx());
        }
        std::vector<int> index_vec(indices.begin(), indices.end());
        Eigen::Vector3d p0 = points.row(index_vec[0]);
        Eigen::Vector3d p1 = points.row(index_vec[1]);
        Eigen::Vector3d p2 = points.row(index_vec[2]);
        Plane analytic_plane = compute_plane_from_points(p0, p1, p2);

        if (analytic_plane.a == 0 && analytic_plane.b == 0 && analytic_plane.c == 0 && analytic_plane.d == 0) {
            return {analytic_plane, 0}; 
        }
        Eigen::Vector3d normal(analytic_plane.a, analytic_plane.b, analytic_plane.c);
        double norm = normal.norm();

        Eigen::VectorXd plane_values = points * normal;
        plane_values = plane_values.array() + analytic_plane.d;
        Eigen::VectorXd distances = plane_values.array().abs() / norm;
        int n_inliers = (distances.array() < inlier_threshold_).count();
        double norm1 = sqrt(analytic_plane.a*analytic_plane.a + analytic_plane.b*analytic_plane.b + analytic_plane.c*analytic_plane.c);
        if (norm1 > 1e-8) {
            analytic_plane.a /= norm1;
            analytic_plane.b /= norm1;
            analytic_plane.c /= norm1;
            analytic_plane.d /= norm1;
        }
        // ---
        return {analytic_plane, n_inliers};
    }
};

class LeastSquaresFitter : public BaseFitter
{
public:
    LeastSquaresFitter(int num_points, int n_sample_points) : BaseFitter(num_points), n_sample_points_(n_sample_points) {}

    // You should override the `fit` method here
    // --- Your code here
    FitResult fit(Eigen::MatrixXd const &points) override{
        std::set<int> indices;
        while(indices.size()<n_sample_points_){
            indices.insert(get_random_point_idx());
        }
        Eigen::MatrixXd sample_points(n_sample_points_, 3);
        int i=0;
        std::set<int>::iterator it;
        for (it = indices.begin(); it != indices.end(); ++it) {
            sample_points.row(i++) = points.row(*it);
        }
        Eigen::Vector3d centroid = sample_points.colwise().mean();
        Eigen::MatrixXd centered = sample_points.rowwise() - centroid.transpose();
        Eigen::Matrix3d cov = (centered.adjoint() * centered) / (n_sample_points_ - 1);
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver(cov);
        if (solver.info() != Eigen::Success) {
            return {Plane{0,0,0,0}, 0};
        }
        Eigen::Vector3d normal = solver.eigenvectors().col(0);
        normal.normalized();
        double d = -normal.dot(centroid);
        Plane plane{normal.x(), normal.y(), normal.z(), d};
        double norm = normal.norm();
        if (norm < 1e-8) {
            return {Plane{0,0,0,0}, 0}; 
        }
        
        Eigen::VectorXd plane_values = points * normal;
        plane_values = plane_values.array() + d;  // ax + by + cz + d
        Eigen::VectorXd distances = plane_values.array().abs() / norm;
        int n_inliers = (distances.array() < inlier_threshold_).count();

        double norm1 = sqrt(plane.a*plane.a + plane.b*plane.b + plane.c*plane.c);
        if (norm1 > 1e-8) {
            plane.a /= norm1;
            plane.b /= norm1;
            plane.c /= norm1;
            plane.d /= norm1;
        }
        return {plane, n_inliers};

    // ---
    }
    int const n_sample_points_;
};

Plane ransac(BaseFitter &fitter, Eigen::MatrixXd const &points)
{
    // --- Your code here
    FitResult best_result{Plane{0,0,0,0}, 0};
    int iterations = 1000;
    for (int i = 0; i < iterations; i++) {
        FitResult current = fitter.fit(points);
        if (current.n_inliers > best_result.n_inliers) {
            best_result = current;
            if (best_result.n_inliers > points.rows() * 0.8) {
                break;
            }
        }
    }
    // ---
    // HINT: the number of inliers should be between 20 and 80 if you did everything correctly
    std::cout << best_result.n_inliers << std::endl;
    return best_result.plane;
}