// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76207695;
  double density_weight = 0.24799872;
  double prefix_weight = 0.12111806;
  double neighborhood_weight = 0.03770044;
  double late_weight = 0.12860764;
  double critical_weight = 0.41258279;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
