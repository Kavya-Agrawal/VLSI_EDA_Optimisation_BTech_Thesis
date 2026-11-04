// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79171505;
  double density_weight = 0.36695959;
  double prefix_weight = 0.32375019;
  double neighborhood_weight = 0.35034555;
  double late_weight = 0.04395116;
  double critical_weight = 0.27459001;
  unsigned budget = 36;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
