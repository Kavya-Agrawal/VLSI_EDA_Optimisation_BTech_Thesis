// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81931693;
  double density_weight = 0.26516100;
  double prefix_weight = 0.13883238;
  double neighborhood_weight = 0.03734131;
  double late_weight = 0.10208987;
  double critical_weight = 0.31437155;
  unsigned budget = 31;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
