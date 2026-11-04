// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78289726;
  double density_weight = 0.36507780;
  double prefix_weight = 0.16837639;
  double neighborhood_weight = 0.28222865;
  double late_weight = 0.02385635;
  double critical_weight = 0.04801671;
  unsigned budget = 38;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
