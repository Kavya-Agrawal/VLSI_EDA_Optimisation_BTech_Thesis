// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74100159;
  double density_weight = 0.02600333;
  double prefix_weight = 0.43260757;
  double neighborhood_weight = 0.06076555;
  double late_weight = 0.14686134;
  double critical_weight = 0.47516649;
  unsigned budget = 23;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
