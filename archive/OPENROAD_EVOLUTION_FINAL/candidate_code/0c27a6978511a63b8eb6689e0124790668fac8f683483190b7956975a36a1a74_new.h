// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18044534;
  double density_weight = 0.22978478;
  double prefix_weight = 0.45119231;
  double neighborhood_weight = 0.02678835;
  double late_weight = 0.12191151;
  double critical_weight = 0.21808471;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
