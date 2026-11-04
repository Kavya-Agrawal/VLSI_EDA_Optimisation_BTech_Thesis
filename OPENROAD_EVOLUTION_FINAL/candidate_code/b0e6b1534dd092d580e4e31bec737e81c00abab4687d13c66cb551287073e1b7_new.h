// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74853462;
  double density_weight = 0.49024657;
  double prefix_weight = 0.13035418;
  double neighborhood_weight = 0.12365628;
  double late_weight = 0.15408404;
  double critical_weight = 0.31758666;
  unsigned budget = 40;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
