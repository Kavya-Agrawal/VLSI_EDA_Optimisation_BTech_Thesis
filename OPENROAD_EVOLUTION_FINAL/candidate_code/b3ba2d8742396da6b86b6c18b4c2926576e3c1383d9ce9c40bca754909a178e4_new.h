// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51536644;
  double density_weight = 0.30044882;
  double prefix_weight = 0.41171119;
  double neighborhood_weight = 0.22521110;
  double late_weight = 0.05860638;
  double critical_weight = 0.06600996;
  unsigned budget = 20;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
