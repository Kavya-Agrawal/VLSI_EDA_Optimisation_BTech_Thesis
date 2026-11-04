// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73254279;
  double density_weight = 0.51462586;
  double prefix_weight = 0.34752519;
  double neighborhood_weight = 0.31753780;
  double late_weight = 0.26577598;
  double critical_weight = 0.17147274;
  unsigned budget = 23;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
