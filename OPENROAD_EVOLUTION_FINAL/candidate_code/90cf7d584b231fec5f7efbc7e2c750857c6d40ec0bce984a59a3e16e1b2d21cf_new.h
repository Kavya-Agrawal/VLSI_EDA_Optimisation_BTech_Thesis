// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35692241;
  double density_weight = 0.00027685;
  double prefix_weight = 0.45575586;
  double neighborhood_weight = 0.22947999;
  double late_weight = 0.00530937;
  double critical_weight = 0.37066558;
  unsigned budget = 25;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
