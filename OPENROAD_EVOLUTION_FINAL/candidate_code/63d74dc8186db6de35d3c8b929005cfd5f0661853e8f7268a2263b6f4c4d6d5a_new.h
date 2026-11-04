// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88572100;
  double density_weight = 0.06365310;
  double prefix_weight = 0.26767693;
  double neighborhood_weight = 0.38022929;
  double late_weight = 0.01727519;
  double critical_weight = 0.07463755;
  unsigned budget = 28;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
