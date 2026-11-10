// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14646547;
  double density_weight = 0.54172286;
  double prefix_weight = 0.34868529;
  double neighborhood_weight = 0.01836749;
  double late_weight = 0.16160490;
  double critical_weight = 0.24702493;
  unsigned budget = 36;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
