// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73733069;
  double density_weight = 0.17698086;
  double prefix_weight = 0.28994915;
  double neighborhood_weight = 0.07982296;
  double late_weight = 0.13677553;
  double critical_weight = 0.24252770;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
