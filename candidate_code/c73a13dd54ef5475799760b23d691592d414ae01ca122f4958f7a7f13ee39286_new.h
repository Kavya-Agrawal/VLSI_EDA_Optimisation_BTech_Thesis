// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50045458;
  double density_weight = 0.07891512;
  double prefix_weight = 0.08879733;
  double neighborhood_weight = 0.27441796;
  double late_weight = 0.21896686;
  double critical_weight = 0.40324312;
  unsigned budget = 30;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
