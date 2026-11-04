// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91823819;
  double density_weight = 0.51740398;
  double prefix_weight = 0.27821338;
  double neighborhood_weight = 0.31059966;
  double late_weight = 0.01890550;
  double critical_weight = 0.21372048;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
