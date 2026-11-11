// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71338191;
  double density_weight = 0.17110577;
  double prefix_weight = 0.22207326;
  double neighborhood_weight = 0.30881936;
  double late_weight = 0.06312123;
  double critical_weight = 0.20604868;
  unsigned budget = 39;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
