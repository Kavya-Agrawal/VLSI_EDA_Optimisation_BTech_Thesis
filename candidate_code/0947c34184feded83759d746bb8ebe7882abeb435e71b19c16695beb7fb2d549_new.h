// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06565492;
  double density_weight = 0.12559523;
  double prefix_weight = 0.10372659;
  double neighborhood_weight = 0.35027387;
  double late_weight = 0.12644230;
  double critical_weight = 0.46625796;
  unsigned budget = 28;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
