// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56216417;
  double density_weight = 0.40540297;
  double prefix_weight = 0.07648921;
  double neighborhood_weight = 0.29616693;
  double late_weight = 0.18149861;
  double critical_weight = 0.49146936;
  unsigned budget = 9;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
