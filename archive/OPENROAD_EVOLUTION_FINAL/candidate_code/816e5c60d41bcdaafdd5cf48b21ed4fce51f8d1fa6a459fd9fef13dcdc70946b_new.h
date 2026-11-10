// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31715302;
  double density_weight = 0.57279477;
  double prefix_weight = 0.41834664;
  double neighborhood_weight = 0.33823351;
  double late_weight = 0.13614057;
  double critical_weight = 0.25981518;
  unsigned budget = 13;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
