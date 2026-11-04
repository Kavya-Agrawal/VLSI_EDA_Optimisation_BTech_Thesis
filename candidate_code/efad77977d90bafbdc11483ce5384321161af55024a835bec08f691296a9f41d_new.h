// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58444533;
  double density_weight = 0.44023938;
  double prefix_weight = 0.44774204;
  double neighborhood_weight = 0.35626609;
  double late_weight = 0.04586622;
  double critical_weight = 0.15345093;
  unsigned budget = 24;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
