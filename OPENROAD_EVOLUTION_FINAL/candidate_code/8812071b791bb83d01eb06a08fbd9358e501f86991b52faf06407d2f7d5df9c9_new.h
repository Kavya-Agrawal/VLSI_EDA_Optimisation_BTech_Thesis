// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71461676;
  double density_weight = 0.35692298;
  double prefix_weight = 0.04372402;
  double neighborhood_weight = 0.09325685;
  double late_weight = 0.21906755;
  double critical_weight = 0.36608981;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
