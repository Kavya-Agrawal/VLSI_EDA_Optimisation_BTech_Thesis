// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14265082;
  double density_weight = 0.13793089;
  double prefix_weight = 0.01756648;
  double neighborhood_weight = 0.00687730;
  double late_weight = 0.10797743;
  double critical_weight = 0.30048394;
  unsigned budget = 11;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
