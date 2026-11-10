// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34016131;
  double density_weight = 0.38660459;
  double prefix_weight = 0.14697896;
  double neighborhood_weight = 0.09631970;
  double late_weight = 0.28538307;
  double critical_weight = 0.12846703;
  unsigned budget = 40;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
