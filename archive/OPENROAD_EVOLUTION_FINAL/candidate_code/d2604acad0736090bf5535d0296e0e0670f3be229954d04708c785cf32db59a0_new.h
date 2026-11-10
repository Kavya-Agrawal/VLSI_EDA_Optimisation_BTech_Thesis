// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37288956;
  double density_weight = 0.05263080;
  double prefix_weight = 0.11506274;
  double neighborhood_weight = 0.04395158;
  double late_weight = 0.04663059;
  double critical_weight = 0.40551471;
  unsigned budget = 16;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
