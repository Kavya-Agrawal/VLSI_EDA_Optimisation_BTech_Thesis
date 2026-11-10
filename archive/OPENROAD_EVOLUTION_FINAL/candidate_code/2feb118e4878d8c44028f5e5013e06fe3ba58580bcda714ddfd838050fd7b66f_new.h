// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93967972;
  double density_weight = 0.43007893;
  double prefix_weight = 0.03394553;
  double neighborhood_weight = 0.08901719;
  double late_weight = 0.08964619;
  double critical_weight = 0.03790651;
  unsigned budget = 20;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
