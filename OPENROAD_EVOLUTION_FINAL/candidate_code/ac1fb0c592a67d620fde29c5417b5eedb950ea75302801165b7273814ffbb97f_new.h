// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94240647;
  double density_weight = 0.37322138;
  double prefix_weight = 0.36471574;
  double neighborhood_weight = 0.30254993;
  double late_weight = 0.14697094;
  double critical_weight = 0.25158669;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
