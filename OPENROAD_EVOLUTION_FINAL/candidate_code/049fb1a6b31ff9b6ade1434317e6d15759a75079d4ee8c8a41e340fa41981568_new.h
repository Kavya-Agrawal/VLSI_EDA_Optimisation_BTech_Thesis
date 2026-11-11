// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01107936;
  double density_weight = 0.29818002;
  double prefix_weight = 0.25062569;
  double neighborhood_weight = 0.29028465;
  double late_weight = 0.28944297;
  double critical_weight = 0.00012459;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
