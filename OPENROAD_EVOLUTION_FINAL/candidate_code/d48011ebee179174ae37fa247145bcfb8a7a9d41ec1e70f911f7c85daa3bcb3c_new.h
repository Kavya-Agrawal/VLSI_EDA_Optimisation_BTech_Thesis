// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08301894;
  double density_weight = 0.21909889;
  double prefix_weight = 0.05531492;
  double neighborhood_weight = 0.14696638;
  double late_weight = 0.28794918;
  double critical_weight = 0.20902497;
  unsigned budget = 33;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
