// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10741516;
  double density_weight = 0.30793174;
  double prefix_weight = 0.28869895;
  double neighborhood_weight = 0.24400381;
  double late_weight = 0.14130714;
  double critical_weight = 0.32610726;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
