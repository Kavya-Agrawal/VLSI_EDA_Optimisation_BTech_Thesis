// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81337301;
  double density_weight = 0.23862733;
  double prefix_weight = 0.18701613;
  double neighborhood_weight = 0.22127675;
  double late_weight = 0.13190698;
  double critical_weight = 0.34424470;
  unsigned budget = 31;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
