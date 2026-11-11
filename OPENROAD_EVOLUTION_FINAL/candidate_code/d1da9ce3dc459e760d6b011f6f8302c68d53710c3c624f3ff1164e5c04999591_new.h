// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84308140;
  double density_weight = 0.57171889;
  double prefix_weight = 0.16904702;
  double neighborhood_weight = 0.23746578;
  double late_weight = 0.01703076;
  double critical_weight = 0.26523062;
  unsigned budget = 25;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
