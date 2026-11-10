// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18769441;
  double density_weight = 0.12465166;
  double prefix_weight = 0.46829277;
  double neighborhood_weight = 0.29704685;
  double late_weight = 0.04916958;
  double critical_weight = 0.31869150;
  unsigned budget = 5;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
