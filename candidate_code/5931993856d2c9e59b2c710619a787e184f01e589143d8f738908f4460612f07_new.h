// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76712958;
  double density_weight = 0.36553132;
  double prefix_weight = 0.20279300;
  double neighborhood_weight = 0.32109132;
  double late_weight = 0.24073551;
  double critical_weight = 0.43116947;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
