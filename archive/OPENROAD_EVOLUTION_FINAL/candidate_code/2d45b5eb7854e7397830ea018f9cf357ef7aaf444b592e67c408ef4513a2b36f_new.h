// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49842671;
  double density_weight = 0.10039801;
  double prefix_weight = 0.17525847;
  double neighborhood_weight = 0.34037506;
  double late_weight = 0.06254255;
  double critical_weight = 0.27962511;
  unsigned budget = 39;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
