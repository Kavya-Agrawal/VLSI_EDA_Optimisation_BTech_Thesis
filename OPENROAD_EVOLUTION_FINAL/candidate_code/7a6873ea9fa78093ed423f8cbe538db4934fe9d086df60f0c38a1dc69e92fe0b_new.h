// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24798215;
  double density_weight = 0.43558594;
  double prefix_weight = 0.13368618;
  double neighborhood_weight = 0.29835287;
  double late_weight = 0.19829934;
  double critical_weight = 0.32962303;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
