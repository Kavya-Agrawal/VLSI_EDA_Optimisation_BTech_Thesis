// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78423841;
  double density_weight = 0.12015949;
  double prefix_weight = 0.13095106;
  double neighborhood_weight = 0.29957421;
  double late_weight = 0.26172603;
  double critical_weight = 0.32851340;
  unsigned budget = 9;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
