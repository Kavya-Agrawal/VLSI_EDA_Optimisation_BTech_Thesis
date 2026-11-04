// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91937811;
  double density_weight = 0.22544210;
  double prefix_weight = 0.23715796;
  double neighborhood_weight = 0.31132928;
  double late_weight = 0.04006443;
  double critical_weight = 0.38469087;
  unsigned budget = 32;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
