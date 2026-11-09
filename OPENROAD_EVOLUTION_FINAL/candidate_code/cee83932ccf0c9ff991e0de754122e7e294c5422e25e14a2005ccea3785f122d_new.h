// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68096259;
  double density_weight = 0.06321870;
  double prefix_weight = 0.06495647;
  double neighborhood_weight = 0.14157306;
  double late_weight = 0.06801041;
  double critical_weight = 0.38229792;
  unsigned budget = 8;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
