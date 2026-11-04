// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35884873;
  double density_weight = 0.25665502;
  double prefix_weight = 0.00483684;
  double neighborhood_weight = 0.39104340;
  double late_weight = 0.26145059;
  double critical_weight = 0.03985880;
  unsigned budget = 12;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
