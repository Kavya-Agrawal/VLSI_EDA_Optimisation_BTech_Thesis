// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87933073;
  double density_weight = 0.19811623;
  double prefix_weight = 0.29681319;
  double neighborhood_weight = 0.06972545;
  double late_weight = 0.12331794;
  double critical_weight = 0.48699010;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
