// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91992478;
  double density_weight = 0.37815901;
  double prefix_weight = 0.28964859;
  double neighborhood_weight = 0.39065937;
  double late_weight = 0.19981503;
  double critical_weight = 0.23251476;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
