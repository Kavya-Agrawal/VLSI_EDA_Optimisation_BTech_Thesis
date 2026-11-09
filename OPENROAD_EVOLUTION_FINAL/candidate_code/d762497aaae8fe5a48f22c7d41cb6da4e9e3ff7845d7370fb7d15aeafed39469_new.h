// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38781734;
  double density_weight = 0.12993185;
  double prefix_weight = 0.25702223;
  double neighborhood_weight = 0.20918759;
  double late_weight = 0.27433939;
  double critical_weight = 0.02448956;
  unsigned budget = 19;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
