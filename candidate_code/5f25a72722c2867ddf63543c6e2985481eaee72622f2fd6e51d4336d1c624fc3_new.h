// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02835933;
  double density_weight = 0.54073479;
  double prefix_weight = 0.34732053;
  double neighborhood_weight = 0.01957602;
  double late_weight = 0.15319952;
  double critical_weight = 0.34424916;
  unsigned budget = 33;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
