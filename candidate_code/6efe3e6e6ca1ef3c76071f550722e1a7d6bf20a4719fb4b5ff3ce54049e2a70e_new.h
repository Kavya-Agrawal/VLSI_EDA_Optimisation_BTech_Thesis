// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37868060;
  double density_weight = 0.13859386;
  double prefix_weight = 0.31887865;
  double neighborhood_weight = 0.32772908;
  double late_weight = 0.19660023;
  double critical_weight = 0.18648985;
  unsigned budget = 39;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
