// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96153123;
  double density_weight = 0.20433305;
  double prefix_weight = 0.35425631;
  double neighborhood_weight = 0.31420165;
  double late_weight = 0.17730857;
  double critical_weight = 0.27817614;
  unsigned budget = 18;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
