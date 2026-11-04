// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45175826;
  double density_weight = 0.44559498;
  double prefix_weight = 0.43667877;
  double neighborhood_weight = 0.36152372;
  double late_weight = 0.09351994;
  double critical_weight = 0.27304273;
  unsigned budget = 37;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
