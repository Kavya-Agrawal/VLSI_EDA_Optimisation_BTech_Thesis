// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98109504;
  double density_weight = 0.01982967;
  double prefix_weight = 0.06408172;
  double neighborhood_weight = 0.12194405;
  double late_weight = 0.17971843;
  double critical_weight = 0.01259050;
  unsigned budget = 36;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
