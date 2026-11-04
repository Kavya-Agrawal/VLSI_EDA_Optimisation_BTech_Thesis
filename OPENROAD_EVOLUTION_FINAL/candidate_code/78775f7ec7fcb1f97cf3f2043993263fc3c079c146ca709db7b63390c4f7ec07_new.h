// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26332657;
  double density_weight = 0.20382081;
  double prefix_weight = 0.16099557;
  double neighborhood_weight = 0.11137715;
  double late_weight = 0.22061509;
  double critical_weight = 0.28959937;
  unsigned budget = 19;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
