#ifndef TUTORIALS_WEEK8_ROPE_H_
#define TUTORIALS_WEEK8_ROPE_H_

#include <string>
#include <utility>
#include <vector>

class Rope {
 public:
  explicit Rope(std::vector<std::string> rope): rope_{std::move(rope)} {}

  class iterator {
   public:
    // TODO(tutorial): fill this in.
    using iterator_category = std::input_iterator_tag;
    using value_type = char;
    using reference = char&;
    using pointer = char*;
    using difference_type = int;

    reference operator*() const;
    iterator& operator++();
    iterator operator++(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }
    // This one isn't strictly required, but it's nice to have.
    pointer operator->() const { return &(operator*()); }

     friend bool operator==(const iterator& lhs, const iterator& rhs) {
      // We need to check the sentinel because comparison of default constructed iterators is undefined.
      return lhs.outer_ == rhs.outer_ && (lhs.outer_ == lhs.sentinel_ || lhs.inner_ == rhs.inner_);
    }

    friend bool operator!=(const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }

   private:
    std::vector<std::string>::iterator outer_;
    const std::vector<std::string>::iterator sentinel_;
    std::string::iterator inner_;

    friend class Rope;
    iterator(const decltype(outer_)& outer, const decltype(sentinel_)& sentinel, const decltype(inner_)& inner): outer_{outer}, sentinel_{sentinel}, inner_{inner} {}
    };

    iterator begin();
    iterator end();
 private:
  std::vector<std::string> rope_;
};

#include <algorithm>

Rope::iterator::reference Rope::iterator::operator*() const {
  return *inner_;
}

Rope::iterator& Rope::iterator::operator++() {
  ++inner_;
  if (inner_ == outer_->end()) {
    do {
      ++outer_;
    } while (outer_ != sentinel_ && outer_->begin() == outer_->end());
    if (outer_ != sentinel_) {
      inner_ = outer_->begin();
    }
  }
  return *this;
}

Rope::iterator Rope::begin() {
  // What if the first element is empty?
  if (auto first = std::find_if(rope_.begin(), rope_.end(), [] (const std::string& s) { return !s.empty(); }); first != rope_.end()) {
    return {first, rope_.end(), first->begin()};
  }
  return end();
}

Rope::iterator Rope::end() {
  return {rope_.end(), rope_.end(), {}};
}

#endif  // TUTORIALS_WEEK8_ROPE_H_