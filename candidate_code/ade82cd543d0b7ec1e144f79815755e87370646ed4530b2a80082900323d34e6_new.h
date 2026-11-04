// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05669139;
  double density_weight = 0.13083658;
  double prefix_weight = 0.27959296;
  double neighborhood_weight = 0.30069678;
  double late_weight = 0.20830430;
  double critical_weight = 0.41776035;
  unsigned budget = 5;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
