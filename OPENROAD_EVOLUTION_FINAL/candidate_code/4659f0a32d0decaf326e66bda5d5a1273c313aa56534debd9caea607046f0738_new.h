// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41256395;
  double density_weight = 0.25726211;
  double prefix_weight = 0.16488302;
  double neighborhood_weight = 0.06902750;
  double late_weight = 0.09292773;
  double critical_weight = 0.29631230;
  unsigned budget = 25;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
