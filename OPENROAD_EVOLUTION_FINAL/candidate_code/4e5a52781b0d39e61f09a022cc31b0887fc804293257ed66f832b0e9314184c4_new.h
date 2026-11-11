// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35726697;
  double density_weight = 0.27166547;
  double prefix_weight = 0.22542429;
  double neighborhood_weight = 0.04658455;
  double late_weight = 0.29132591;
  double critical_weight = 0.26787160;
  unsigned budget = 33;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
