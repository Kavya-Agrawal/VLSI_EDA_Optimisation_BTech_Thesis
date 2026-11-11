// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23756262;
  double density_weight = 0.35630954;
  double prefix_weight = 0.12532409;
  double neighborhood_weight = 0.39159766;
  double late_weight = 0.16062342;
  double critical_weight = 0.24030315;
  unsigned budget = 8;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
