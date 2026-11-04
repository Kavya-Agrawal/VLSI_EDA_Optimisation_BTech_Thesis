// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34416281;
  double density_weight = 0.39318110;
  double prefix_weight = 0.11981495;
  double neighborhood_weight = 0.25267466;
  double late_weight = 0.23817292;
  double critical_weight = 0.45772770;
  unsigned budget = 24;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
