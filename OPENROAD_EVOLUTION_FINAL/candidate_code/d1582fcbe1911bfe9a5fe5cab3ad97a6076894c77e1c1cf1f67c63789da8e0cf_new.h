// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16560881;
  double density_weight = 0.49317810;
  double prefix_weight = 0.32203557;
  double neighborhood_weight = 0.17430254;
  double late_weight = 0.16866755;
  double critical_weight = 0.10708774;
  unsigned budget = 40;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
