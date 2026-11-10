// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38214578;
  double density_weight = 0.41657214;
  double prefix_weight = 0.44317148;
  double neighborhood_weight = 0.21390210;
  double late_weight = 0.10471995;
  double critical_weight = 0.08093249;
  unsigned budget = 39;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
