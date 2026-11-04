// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47764557;
  double density_weight = 0.11598806;
  double prefix_weight = 0.10461411;
  double neighborhood_weight = 0.37923672;
  double late_weight = 0.28424166;
  double critical_weight = 0.26665204;
  unsigned budget = 13;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
