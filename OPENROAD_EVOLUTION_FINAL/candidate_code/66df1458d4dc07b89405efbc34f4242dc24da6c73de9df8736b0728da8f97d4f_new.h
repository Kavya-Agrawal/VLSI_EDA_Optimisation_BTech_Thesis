// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30662706;
  double density_weight = 0.52158289;
  double prefix_weight = 0.41656762;
  double neighborhood_weight = 0.11747019;
  double late_weight = 0.21630338;
  double critical_weight = 0.46473395;
  unsigned budget = 5;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
