// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34911143;
  double density_weight = 0.46806562;
  double prefix_weight = 0.49158358;
  double neighborhood_weight = 0.21188770;
  double late_weight = 0.18548548;
  double critical_weight = 0.06925101;
  unsigned budget = 6;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
