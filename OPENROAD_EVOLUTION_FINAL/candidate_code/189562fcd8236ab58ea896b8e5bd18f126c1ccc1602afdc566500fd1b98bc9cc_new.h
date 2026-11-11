// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50525180;
  double density_weight = 0.17442076;
  double prefix_weight = 0.29046565;
  double neighborhood_weight = 0.25501954;
  double late_weight = 0.22246425;
  double critical_weight = 0.41922265;
  unsigned budget = 32;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
