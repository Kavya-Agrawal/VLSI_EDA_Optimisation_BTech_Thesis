// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03379184;
  double density_weight = 0.00287045;
  double prefix_weight = 0.48234513;
  double neighborhood_weight = 0.00651996;
  double late_weight = 0.11191034;
  double critical_weight = 0.29620658;
  unsigned budget = 10;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
