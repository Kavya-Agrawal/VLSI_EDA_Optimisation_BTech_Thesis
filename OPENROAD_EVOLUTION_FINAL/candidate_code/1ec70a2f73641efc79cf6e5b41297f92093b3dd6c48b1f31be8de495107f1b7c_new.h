// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19299848;
  double density_weight = 0.51715759;
  double prefix_weight = 0.41700096;
  double neighborhood_weight = 0.13082648;
  double late_weight = 0.01514025;
  double critical_weight = 0.45060847;
  unsigned budget = 7;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
