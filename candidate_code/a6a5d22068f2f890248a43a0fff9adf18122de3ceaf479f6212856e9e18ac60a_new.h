// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67171401;
  double density_weight = 0.58987817;
  double prefix_weight = 0.35727251;
  double neighborhood_weight = 0.36170479;
  double late_weight = 0.20814651;
  double critical_weight = 0.40538511;
  unsigned budget = 24;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
