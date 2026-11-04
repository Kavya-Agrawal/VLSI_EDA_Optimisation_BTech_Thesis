// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72259245;
  double density_weight = 0.10225356;
  double prefix_weight = 0.35410563;
  double neighborhood_weight = 0.12704486;
  double late_weight = 0.09669634;
  double critical_weight = 0.25677765;
  unsigned budget = 13;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
