// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17179421;
  double density_weight = 0.07216792;
  double prefix_weight = 0.06167493;
  double neighborhood_weight = 0.20646496;
  double late_weight = 0.26788814;
  double critical_weight = 0.17021178;
  unsigned budget = 27;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
