// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23468443;
  double density_weight = 0.18935864;
  double prefix_weight = 0.28294658;
  double neighborhood_weight = 0.12418463;
  double late_weight = 0.06130328;
  double critical_weight = 0.05126060;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
