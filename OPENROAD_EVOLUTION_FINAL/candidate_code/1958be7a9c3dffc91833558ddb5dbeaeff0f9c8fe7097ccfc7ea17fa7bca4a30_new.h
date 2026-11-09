// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87879323;
  double density_weight = 0.54494390;
  double prefix_weight = 0.28135880;
  double neighborhood_weight = 0.34417443;
  double late_weight = 0.12577674;
  double critical_weight = 0.17472289;
  unsigned budget = 21;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
