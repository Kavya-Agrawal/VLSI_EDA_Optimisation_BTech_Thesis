// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90954680;
  double density_weight = 0.59065703;
  double prefix_weight = 0.40762691;
  double neighborhood_weight = 0.35546738;
  double late_weight = 0.06477339;
  double critical_weight = 0.30248223;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
