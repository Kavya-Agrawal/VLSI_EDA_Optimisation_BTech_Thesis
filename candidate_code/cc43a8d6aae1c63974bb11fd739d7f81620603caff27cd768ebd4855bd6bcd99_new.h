// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82992587;
  double density_weight = 0.47963646;
  double prefix_weight = 0.12211521;
  double neighborhood_weight = 0.21264481;
  double late_weight = 0.16883512;
  double critical_weight = 0.09697975;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
