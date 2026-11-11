// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60008927;
  double density_weight = 0.39507953;
  double prefix_weight = 0.14971523;
  double neighborhood_weight = 0.34415444;
  double late_weight = 0.08990019;
  double critical_weight = 0.37700482;
  unsigned budget = 7;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
