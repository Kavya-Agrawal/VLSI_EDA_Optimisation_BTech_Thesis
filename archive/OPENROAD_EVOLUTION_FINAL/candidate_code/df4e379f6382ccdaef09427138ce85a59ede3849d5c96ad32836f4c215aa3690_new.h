// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26757861;
  double density_weight = 0.10977224;
  double prefix_weight = 0.07849444;
  double neighborhood_weight = 0.05039322;
  double late_weight = 0.15281569;
  double critical_weight = 0.26428906;
  unsigned budget = 25;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
