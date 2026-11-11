// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79120717;
  double density_weight = 0.52099191;
  double prefix_weight = 0.45907402;
  double neighborhood_weight = 0.00323541;
  double late_weight = 0.28760187;
  double critical_weight = 0.01896803;
  unsigned budget = 11;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
