// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54222635;
  double density_weight = 0.29194413;
  double prefix_weight = 0.47806997;
  double neighborhood_weight = 0.05964453;
  double late_weight = 0.20603477;
  double critical_weight = 0.46432548;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
