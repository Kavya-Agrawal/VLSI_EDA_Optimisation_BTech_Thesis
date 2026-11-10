// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17852036;
  double density_weight = 0.47144282;
  double prefix_weight = 0.47069823;
  double neighborhood_weight = 0.31622475;
  double late_weight = 0.21636150;
  double critical_weight = 0.03961481;
  unsigned budget = 27;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
