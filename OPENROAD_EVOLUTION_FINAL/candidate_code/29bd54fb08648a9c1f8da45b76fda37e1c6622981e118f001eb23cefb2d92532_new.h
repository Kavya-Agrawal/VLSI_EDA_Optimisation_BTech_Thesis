// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31829557;
  double density_weight = 0.36526911;
  double prefix_weight = 0.04271376;
  double neighborhood_weight = 0.03063979;
  double late_weight = 0.12536270;
  double critical_weight = 0.29544398;
  unsigned budget = 10;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
