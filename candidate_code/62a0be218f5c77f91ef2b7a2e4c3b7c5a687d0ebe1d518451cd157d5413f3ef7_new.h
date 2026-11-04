// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65958889;
  double density_weight = 0.43362855;
  double prefix_weight = 0.10410073;
  double neighborhood_weight = 0.12975556;
  double late_weight = 0.19177880;
  double critical_weight = 0.38918525;
  unsigned budget = 36;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
