// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99448111;
  double density_weight = 0.11430110;
  double prefix_weight = 0.19300059;
  double neighborhood_weight = 0.08461398;
  double late_weight = 0.10238618;
  double critical_weight = 0.33261906;
  unsigned budget = 7;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
