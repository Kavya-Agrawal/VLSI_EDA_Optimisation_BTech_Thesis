// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93035349;
  double density_weight = 0.35417843;
  double prefix_weight = 0.21630657;
  double neighborhood_weight = 0.18875916;
  double late_weight = 0.25407632;
  double critical_weight = 0.20851024;
  unsigned budget = 39;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
