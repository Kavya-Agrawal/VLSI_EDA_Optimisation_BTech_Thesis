// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52044120;
  double density_weight = 0.44916246;
  double prefix_weight = 0.30191153;
  double neighborhood_weight = 0.11049317;
  double late_weight = 0.01230598;
  double critical_weight = 0.32132294;
  unsigned budget = 12;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
