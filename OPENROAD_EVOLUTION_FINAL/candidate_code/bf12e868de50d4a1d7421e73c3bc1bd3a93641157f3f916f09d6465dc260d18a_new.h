// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86166694;
  double density_weight = 0.51817693;
  double prefix_weight = 0.39639996;
  double neighborhood_weight = 0.36675170;
  double late_weight = 0.10351815;
  double critical_weight = 0.00407328;
  unsigned budget = 25;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
