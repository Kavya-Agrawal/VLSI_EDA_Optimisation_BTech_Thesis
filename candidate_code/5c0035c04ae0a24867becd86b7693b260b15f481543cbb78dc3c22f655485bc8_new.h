// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64463064;
  double density_weight = 0.29674094;
  double prefix_weight = 0.44045328;
  double neighborhood_weight = 0.16228087;
  double late_weight = 0.04808465;
  double critical_weight = 0.45266358;
  unsigned budget = 21;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
