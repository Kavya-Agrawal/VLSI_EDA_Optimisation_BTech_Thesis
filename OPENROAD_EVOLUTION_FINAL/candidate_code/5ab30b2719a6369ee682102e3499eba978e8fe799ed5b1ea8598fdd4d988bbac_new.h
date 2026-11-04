// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25673379;
  double density_weight = 0.19303563;
  double prefix_weight = 0.29015305;
  double neighborhood_weight = 0.29547678;
  double late_weight = 0.29608015;
  double critical_weight = 0.31316843;
  unsigned budget = 25;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
