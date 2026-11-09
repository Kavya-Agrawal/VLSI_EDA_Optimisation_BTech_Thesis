// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82602595;
  double density_weight = 0.23190071;
  double prefix_weight = 0.30797623;
  double neighborhood_weight = 0.14762352;
  double late_weight = 0.28506980;
  double critical_weight = 0.07046814;
  unsigned budget = 34;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
