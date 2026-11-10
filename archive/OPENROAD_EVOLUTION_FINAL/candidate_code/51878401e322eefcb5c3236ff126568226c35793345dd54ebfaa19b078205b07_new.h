// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05809962;
  double density_weight = 0.22322814;
  double prefix_weight = 0.14270975;
  double neighborhood_weight = 0.02724308;
  double late_weight = 0.14035104;
  double critical_weight = 0.33511133;
  unsigned budget = 36;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
