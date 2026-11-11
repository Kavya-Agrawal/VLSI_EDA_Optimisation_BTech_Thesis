// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60344481;
  double density_weight = 0.29048266;
  double prefix_weight = 0.06295339;
  double neighborhood_weight = 0.30742635;
  double late_weight = 0.07745879;
  double critical_weight = 0.06210802;
  unsigned budget = 16;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
