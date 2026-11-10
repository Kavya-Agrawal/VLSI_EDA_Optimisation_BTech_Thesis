// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83518943;
  double density_weight = 0.48886723;
  double prefix_weight = 0.14551397;
  double neighborhood_weight = 0.15507053;
  double late_weight = 0.12308570;
  double critical_weight = 0.14481026;
  unsigned budget = 8;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
