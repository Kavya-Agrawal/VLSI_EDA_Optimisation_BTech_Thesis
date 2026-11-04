// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42805137;
  double density_weight = 0.28352990;
  double prefix_weight = 0.17212939;
  double neighborhood_weight = 0.25905072;
  double late_weight = 0.18964903;
  double critical_weight = 0.19566497;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
