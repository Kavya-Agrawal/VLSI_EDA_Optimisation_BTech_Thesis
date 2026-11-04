// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14409745;
  double density_weight = 0.37941686;
  double prefix_weight = 0.38500811;
  double neighborhood_weight = 0.01179245;
  double late_weight = 0.20179744;
  double critical_weight = 0.09627893;
  unsigned budget = 9;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
