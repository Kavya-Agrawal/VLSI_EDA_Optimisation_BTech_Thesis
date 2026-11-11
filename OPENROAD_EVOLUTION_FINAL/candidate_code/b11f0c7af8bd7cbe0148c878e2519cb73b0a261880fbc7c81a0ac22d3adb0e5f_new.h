// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94046518;
  double density_weight = 0.12137411;
  double prefix_weight = 0.16688295;
  double neighborhood_weight = 0.06816721;
  double late_weight = 0.03267124;
  double critical_weight = 0.01230509;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
