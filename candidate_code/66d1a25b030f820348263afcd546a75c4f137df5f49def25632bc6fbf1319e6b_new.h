// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52767415;
  double density_weight = 0.45631615;
  double prefix_weight = 0.43794448;
  double neighborhood_weight = 0.32670943;
  double late_weight = 0.06567501;
  double critical_weight = 0.17364592;
  unsigned budget = 13;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
