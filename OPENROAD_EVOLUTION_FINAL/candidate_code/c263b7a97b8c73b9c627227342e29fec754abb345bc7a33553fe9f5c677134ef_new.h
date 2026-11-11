// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04877347;
  double density_weight = 0.08109219;
  double prefix_weight = 0.00074722;
  double neighborhood_weight = 0.06296085;
  double late_weight = 0.18493170;
  double critical_weight = 0.33500553;
  unsigned budget = 21;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
