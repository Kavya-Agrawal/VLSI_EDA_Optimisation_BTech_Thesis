// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04982983;
  double density_weight = 0.26476190;
  double prefix_weight = 0.43547056;
  double neighborhood_weight = 0.03329810;
  double late_weight = 0.13900895;
  double critical_weight = 0.37023442;
  unsigned budget = 12;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
