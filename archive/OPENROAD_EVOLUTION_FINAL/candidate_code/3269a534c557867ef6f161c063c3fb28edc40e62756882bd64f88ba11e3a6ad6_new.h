// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66811019;
  double density_weight = 0.02081380;
  double prefix_weight = 0.28680010;
  double neighborhood_weight = 0.21496160;
  double late_weight = 0.23045032;
  double critical_weight = 0.14721738;
  unsigned budget = 29;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
