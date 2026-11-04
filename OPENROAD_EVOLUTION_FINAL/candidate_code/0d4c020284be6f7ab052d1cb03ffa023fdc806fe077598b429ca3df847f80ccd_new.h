// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50388876;
  double density_weight = 0.57428791;
  double prefix_weight = 0.29413198;
  double neighborhood_weight = 0.39752978;
  double late_weight = 0.23644951;
  double critical_weight = 0.37770948;
  unsigned budget = 18;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
