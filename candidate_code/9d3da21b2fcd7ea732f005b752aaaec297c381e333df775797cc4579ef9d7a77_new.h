// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13247166;
  double density_weight = 0.24145051;
  double prefix_weight = 0.18799841;
  double neighborhood_weight = 0.10223358;
  double late_weight = 0.25694179;
  double critical_weight = 0.47512277;
  unsigned budget = 25;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
