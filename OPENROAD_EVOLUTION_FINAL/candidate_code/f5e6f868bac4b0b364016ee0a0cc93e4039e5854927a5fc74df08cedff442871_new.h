// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73041554;
  double density_weight = 0.23282623;
  double prefix_weight = 0.41888202;
  double neighborhood_weight = 0.13157317;
  double late_weight = 0.27293251;
  double critical_weight = 0.49503004;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
