// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82685808;
  double density_weight = 0.25559685;
  double prefix_weight = 0.31571293;
  double neighborhood_weight = 0.36763922;
  double late_weight = 0.20844311;
  double critical_weight = 0.09509868;
  unsigned budget = 22;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
