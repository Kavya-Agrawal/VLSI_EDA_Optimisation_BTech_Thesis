// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99636428;
  double density_weight = 0.10105810;
  double prefix_weight = 0.16005242;
  double neighborhood_weight = 0.00803215;
  double late_weight = 0.00103077;
  double critical_weight = 0.34661547;
  unsigned budget = 17;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
