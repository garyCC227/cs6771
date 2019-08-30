#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <cassert>
#include <cmath>
#include <exception>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // constructor
  explicit EuclideanVector(int i = 1) noexcept;
  EuclideanVector(int, double) noexcept;
  EuclideanVector(std::vector<double>::const_iterator,
                  std::vector<double>::const_iterator) noexcept;

  // copy and move constructor and assignment
  EuclideanVector(const EuclideanVector&) noexcept;
  EuclideanVector(EuclideanVector&&) noexcept;
  EuclideanVector& operator=(const EuclideanVector&) noexcept;
  EuclideanVector& operator=(EuclideanVector&&) noexcept;

  // destructor
  ~EuclideanVector() = default;

  // member operator functions
  double operator[](int i) const noexcept;  // [] getter
  double& operator[](int i) noexcept;       // [] modifier
  EuclideanVector& operator+=(const EuclideanVector&);
  EuclideanVector& operator-=(const EuclideanVector&);
  EuclideanVector& operator*=(double);
  EuclideanVector& operator/=(double);

  // type conversion operator
  explicit operator std::vector<double>() const noexcept;
  explicit operator std::list<double>() const noexcept;

  // methods
  int GetNumDimensions() const noexcept;
  double at(int) const;
  double& at(int);
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector() const;

  // friend operator functions
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept {
    os << '[';

    for (int i = 0; i < v.dimension_; ++i) {
      os << v.magnitudes_[i];
      if (i != (v.dimension_ - 1)) {
        os << ' ';
      }
    }

    os << ']';

    return os;
  }

  //== operator
  friend bool operator==(const EuclideanVector& v1, const EuclideanVector& v2) noexcept {
    if (v1.dimension_ != v2.dimension_) {
      return false;
    }

    for (int i = 0; i < v1.dimension_; ++i) {
      if (v1.magnitudes_[i] != v2.magnitudes_[i])
        return false;
    }

    return true;
  }

  // != operator
  friend bool operator!=(const EuclideanVector& v1, const EuclideanVector& v2) noexcept {
    return !(v1 == v2);
  }

  //+ operator
  friend EuclideanVector operator+(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (v1.dimension_ != v2.dimension_) {
      std::stringstream err;
      err << "Dimensions of LHS(" << v1.GetNumDimensions() << ") and RHS(" << v2.GetNumDimensions()
          << ") do not match";
      throw EuclideanVectorError{err.str()};
    }

    EuclideanVector result{v1};
    result += v2;

    return result;
  }

  // - operator
  friend EuclideanVector operator-(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (v1.dimension_ != v2.dimension_) {
      std::stringstream err;
      err << "Dimensions of LHS(" << v1.GetNumDimensions() << ") and RHS(" << v2.GetNumDimensions()
          << ") do not match";
      throw EuclideanVectorError{err.str()};
    }

    EuclideanVector result{v1};
    result -= v2;

    return result;
  }

  // * operator dot product
  friend double operator*(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (v1.dimension_ != v2.dimension_) {
      std::stringstream err;
      err << "Dimensions of LHS(" << v1.GetNumDimensions() << ") and RHS(" << v2.GetNumDimensions()
          << ") do not match";
      throw EuclideanVectorError{err.str()};
    }

    double dot_product = 0;
    for (int i = 0; i < v1.dimension_; ++i) {
      dot_product += (v1.magnitudes_[i] * v2.magnitudes_[i]);
    }
    return dot_product;
  }

  // operator *, scalar multiplication
  friend EuclideanVector operator*(const EuclideanVector& v1, double i) noexcept {
    EuclideanVector result{v1};
    return (result *= i);
  }

  // operator / : scalar division
  friend EuclideanVector operator/(const EuclideanVector& v1, double i) {
    if (i == 0) {
      throw EuclideanVectorError{"Invalid vector division by 0"};
    }

    EuclideanVector result{v1};
    return (result /= i);
  }

 private:
  int dimension_;
  std::unique_ptr<double[]> magnitudes_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
