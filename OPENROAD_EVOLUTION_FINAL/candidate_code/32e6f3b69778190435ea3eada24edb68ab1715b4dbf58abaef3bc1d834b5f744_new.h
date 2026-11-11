// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15924689;
  double density_weight = 0.34294377;
  double prefix_weight = 0.41198169;
  double neighborhood_weight = 0.02391257;
  double late_weight = 0.14969390;
  double critical_weight = 0.28144595;
  unsigned budget = 21;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
