// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79872977;
  double density_weight = 0.16018294;
  double prefix_weight = 0.44235786;
  double neighborhood_weight = 0.09559094;
  double late_weight = 0.06620222;
  double critical_weight = 0.20773464;
  unsigned budget = 12;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
