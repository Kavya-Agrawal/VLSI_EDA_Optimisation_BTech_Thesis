// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44379008;
  double density_weight = 0.22640699;
  double prefix_weight = 0.16358353;
  double neighborhood_weight = 0.14444114;
  double late_weight = 0.27302882;
  double critical_weight = 0.05953861;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
