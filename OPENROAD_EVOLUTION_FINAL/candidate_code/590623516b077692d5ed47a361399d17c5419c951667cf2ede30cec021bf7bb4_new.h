// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31014125;
  double density_weight = 0.14630388;
  double prefix_weight = 0.07202053;
  double neighborhood_weight = 0.17772394;
  double late_weight = 0.07433380;
  double critical_weight = 0.26334404;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
