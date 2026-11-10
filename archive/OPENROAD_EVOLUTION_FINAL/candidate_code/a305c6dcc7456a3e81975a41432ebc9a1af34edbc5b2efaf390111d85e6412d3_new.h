// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06468108;
  double density_weight = 0.27334510;
  double prefix_weight = 0.44461289;
  double neighborhood_weight = 0.00988411;
  double late_weight = 0.13161234;
  double critical_weight = 0.45912188;
  unsigned budget = 19;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
