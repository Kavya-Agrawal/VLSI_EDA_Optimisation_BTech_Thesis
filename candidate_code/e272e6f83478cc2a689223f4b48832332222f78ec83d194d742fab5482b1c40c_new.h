// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11872447;
  double density_weight = 0.10237602;
  double prefix_weight = 0.12497065;
  double neighborhood_weight = 0.06868557;
  double late_weight = 0.02740117;
  double critical_weight = 0.04476280;
  unsigned budget = 33;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
