#include <iostream>

template <typename T> class EuclideanVector {
public:
  EuclideanVector() : EuclideanVector(10) {}
  EuclideanVector(int size) : vec_{new T[size]}, size_{size} {
    for (int i = 0; i < size_; ++i) {
      vec_[i] = 0;
    }
  }

  EuclideanVector(const EuclideanVector<T> &old)
      : vec_{new T[old.size_]}, size_{old.size_} {
    std::cout << "copy constuctor\n";
    for (int i = 0; i < old.size_; ++i) {
      this->vec_[i] = old.vec_[i];
    }
  }

  EuclideanVector(EuclideanVector<T> &&old) noexcept {
    std::cout << "move constuctor\n";
    size_ = std::move(old.size_);
    vec_ = new T[size_];
    for (int i = 0; i < size_; ++i) {
      vec_[i] = old.vec_[i];
    }
    delete[] old.vec_;
  }

  EuclideanVector &operator=(const EuclideanVector &old) {
    if (this != &old) {
      std::cout << "copy ass\n";
      delete[] this->vec_;
      this->vec_ = new T[old.size_];
      this->size_ = old.size_;
      for (int i = 0; i < old.size_; ++i) {
        this->vec_[i] = old.vec_[i];
      }
    }

    return *this;
  }

  EuclideanVector &operator=(EuclideanVector &&old) noexcept {
        std::cout << "move ass\n";
    if (this != &old) {
      size_ = std::move(old.size_);
      this->vec_ = new T[size_];
      for (int i = 0; i < old.size_; ++i) {
        this->vec_[i] = old.vec_[i];
      }
      delete[] old.vec_;
    }

    return *this;
  }

  ~EuclideanVector() { delete[] vec_; }

  T *getVec() { return vec_; }

  int getSize() { return size_; }

private:
  T *vec_;
  int size_;
};

int main() {
  EuclideanVector<int> v1(5);
  EuclideanVector<int> v2 = v1;
  v1 = std::move(v2);

  std::cout << (v1.getVec() == nullptr) << '\n';
  std::cout << (v2.getVec() == nullptr) << '\n';

  return 0;
}