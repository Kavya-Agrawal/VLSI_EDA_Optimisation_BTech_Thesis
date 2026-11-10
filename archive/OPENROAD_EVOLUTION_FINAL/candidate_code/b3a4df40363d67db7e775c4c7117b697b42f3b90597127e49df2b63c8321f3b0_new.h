// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49228200;
  double density_weight = 0.01624168;
  double prefix_weight = 0.16031256;
  double neighborhood_weight = 0.39067174;
  double late_weight = 0.07072912;
  double critical_weight = 0.03713628;
  unsigned budget = 13;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
