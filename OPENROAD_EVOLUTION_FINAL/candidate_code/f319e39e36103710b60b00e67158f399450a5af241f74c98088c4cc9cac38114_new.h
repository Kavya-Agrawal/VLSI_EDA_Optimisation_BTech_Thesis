// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98741471;
  double density_weight = 0.16143652;
  double prefix_weight = 0.21109993;
  double neighborhood_weight = 0.24715350;
  double late_weight = 0.27448295;
  double critical_weight = 0.21592022;
  unsigned budget = 9;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
