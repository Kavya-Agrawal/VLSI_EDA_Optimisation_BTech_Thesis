// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23554145;
  double density_weight = 0.25773985;
  double prefix_weight = 0.12184355;
  double neighborhood_weight = 0.27737652;
  double late_weight = 0.01475000;
  double critical_weight = 0.40138629;
  unsigned budget = 36;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
