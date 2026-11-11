// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38694578;
  double density_weight = 0.40223116;
  double prefix_weight = 0.14658137;
  double neighborhood_weight = 0.22477388;
  double late_weight = 0.06953235;
  double critical_weight = 0.41557102;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
