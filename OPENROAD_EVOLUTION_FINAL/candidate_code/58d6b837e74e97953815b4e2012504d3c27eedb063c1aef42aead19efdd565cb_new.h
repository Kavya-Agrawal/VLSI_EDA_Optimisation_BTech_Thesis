// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92966232;
  double density_weight = 0.52601619;
  double prefix_weight = 0.00460636;
  double neighborhood_weight = 0.13029275;
  double late_weight = 0.23416354;
  double critical_weight = 0.10613039;
  unsigned budget = 18;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
