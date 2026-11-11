// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44382874;
  double density_weight = 0.13316865;
  double prefix_weight = 0.47172280;
  double neighborhood_weight = 0.27330763;
  double late_weight = 0.12904988;
  double critical_weight = 0.34189022;
  unsigned budget = 16;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
