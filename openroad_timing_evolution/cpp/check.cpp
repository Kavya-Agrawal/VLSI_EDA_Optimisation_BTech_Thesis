#include "EvolvedPathDriverPolicy.h"
#include <cassert>
#include <iostream>
#include <limits>

int main()
{
  if (rsz_evolve::enabled) {
    for (const double invalid : {std::numeric_limits<double>::quiet_NaN(),
                                 std::numeric_limits<double>::infinity()}) {
      bool rejected = false;
      try { (void) rsz_evolve::order({{invalid, 1, 1}}); }
      catch (const std::runtime_error&) { rejected = true; }
      assert(rejected);
    }
    bool rejected = false;
    try { (void) rsz_evolve::order({{1, -1, 1}}); }
    catch (const std::runtime_error&) { rejected = true; }
    assert(rejected);
  }
  std::size_t n;
  while (std::cin >> n) {
    if (n > 10000) { return 2; }
    std::vector<rsz_evolve::Features> features(n);
    for (auto& f : features) {
      if (!(std::cin >> f.load >> f.fanout >> f.position)) { return 3; }
    }
    const auto original = features;
    const auto order = rsz_evolve::order(features);
    assert(order == rsz_evolve::order(features));
    auto sorted = order;
    std::sort(sorted.begin(), sorted.end());
    for (std::size_t i = 0; i < n; ++i) {
      assert(sorted[i] == i);
      assert(features[i].load == original[i].load);
      assert(features[i].fanout == original[i].fanout);
      assert(features[i].position == original[i].position);
      std::cout << (i ? " " : "") << order[i];
    }
    std::cout << '\n';
  }
}
