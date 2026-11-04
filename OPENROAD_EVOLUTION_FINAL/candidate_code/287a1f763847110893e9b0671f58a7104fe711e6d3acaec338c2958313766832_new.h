// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88890744;
  double density_weight = 0.36825630;
  double prefix_weight = 0.38870533;
  double neighborhood_weight = 0.11263450;
  double late_weight = 0.03820095;
  double critical_weight = 0.19872304;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
