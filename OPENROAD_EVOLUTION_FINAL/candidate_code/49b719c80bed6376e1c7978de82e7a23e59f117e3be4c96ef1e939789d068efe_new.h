// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14464394;
  double density_weight = 0.32252904;
  double prefix_weight = 0.10334458;
  double neighborhood_weight = 0.29961259;
  double late_weight = 0.11079526;
  double critical_weight = 0.38078556;
  unsigned budget = 17;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
