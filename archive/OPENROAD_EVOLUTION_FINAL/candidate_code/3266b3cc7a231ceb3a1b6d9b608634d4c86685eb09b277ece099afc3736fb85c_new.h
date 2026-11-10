// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30775724;
  double density_weight = 0.06176893;
  double prefix_weight = 0.07398040;
  double neighborhood_weight = 0.19719399;
  double late_weight = 0.18124933;
  double critical_weight = 0.26362497;
  unsigned budget = 26;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
