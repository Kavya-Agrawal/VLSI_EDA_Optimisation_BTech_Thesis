// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30873559;
  double density_weight = 0.14495302;
  double prefix_weight = 0.44254211;
  double neighborhood_weight = 0.00997904;
  double late_weight = 0.14920613;
  double critical_weight = 0.41290826;
  unsigned budget = 35;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
