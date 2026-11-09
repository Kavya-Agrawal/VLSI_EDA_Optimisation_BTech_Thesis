// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95306379;
  double density_weight = 0.53216867;
  double prefix_weight = 0.47731088;
  double neighborhood_weight = 0.03570187;
  double late_weight = 0.20070651;
  double critical_weight = 0.46847706;
  unsigned budget = 15;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
