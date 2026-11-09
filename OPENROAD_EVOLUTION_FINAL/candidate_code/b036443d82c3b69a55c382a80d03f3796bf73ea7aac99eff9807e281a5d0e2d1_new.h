// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00093048;
  double density_weight = 0.30155216;
  double prefix_weight = 0.03724452;
  double neighborhood_weight = 0.08368833;
  double late_weight = 0.22890111;
  double critical_weight = 0.34057740;
  unsigned budget = 8;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
