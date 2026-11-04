// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86590779;
  double density_weight = 0.12089923;
  double prefix_weight = 0.25577946;
  double neighborhood_weight = 0.08947755;
  double late_weight = 0.23498711;
  double critical_weight = 0.37162289;
  unsigned budget = 19;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
