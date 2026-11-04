// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36109265;
  double density_weight = 0.14324877;
  double prefix_weight = 0.10998922;
  double neighborhood_weight = 0.15733876;
  double late_weight = 0.29366411;
  double critical_weight = 0.03221728;
  unsigned budget = 16;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
