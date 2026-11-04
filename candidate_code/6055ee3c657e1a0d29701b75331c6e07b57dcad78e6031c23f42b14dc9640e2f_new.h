// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21122825;
  double density_weight = 0.00825533;
  double prefix_weight = 0.36238077;
  double neighborhood_weight = 0.24890513;
  double late_weight = 0.28199112;
  double critical_weight = 0.04019782;
  unsigned budget = 33;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
