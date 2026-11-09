// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00919597;
  double density_weight = 0.45638633;
  double prefix_weight = 0.39277434;
  double neighborhood_weight = 0.32518230;
  double late_weight = 0.29726429;
  double critical_weight = 0.07032055;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
