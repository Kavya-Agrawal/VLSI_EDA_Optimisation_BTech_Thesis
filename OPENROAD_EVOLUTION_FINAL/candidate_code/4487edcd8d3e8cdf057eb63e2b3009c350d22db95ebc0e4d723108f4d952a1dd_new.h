// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45515276;
  double density_weight = 0.44182741;
  double prefix_weight = 0.29277666;
  double neighborhood_weight = 0.27241766;
  double late_weight = 0.14253047;
  double critical_weight = 0.00952966;
  unsigned budget = 35;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
