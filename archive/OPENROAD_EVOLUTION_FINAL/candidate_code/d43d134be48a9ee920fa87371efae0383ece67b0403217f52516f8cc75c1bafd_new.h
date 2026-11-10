// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94309135;
  double density_weight = 0.13435763;
  double prefix_weight = 0.20100991;
  double neighborhood_weight = 0.22876291;
  double late_weight = 0.23264299;
  double critical_weight = 0.07409262;
  unsigned budget = 11;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
