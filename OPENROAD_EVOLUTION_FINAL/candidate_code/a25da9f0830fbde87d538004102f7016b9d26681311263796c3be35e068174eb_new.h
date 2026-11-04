// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82241545;
  double density_weight = 0.51417394;
  double prefix_weight = 0.19648865;
  double neighborhood_weight = 0.19166771;
  double late_weight = 0.04286005;
  double critical_weight = 0.47956814;
  unsigned budget = 34;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
