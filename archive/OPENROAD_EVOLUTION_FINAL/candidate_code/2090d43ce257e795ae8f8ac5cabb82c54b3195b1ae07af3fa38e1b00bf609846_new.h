// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49587699;
  double density_weight = 0.10086102;
  double prefix_weight = 0.47329059;
  double neighborhood_weight = 0.33779481;
  double late_weight = 0.03081973;
  double critical_weight = 0.35776793;
  unsigned budget = 18;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
